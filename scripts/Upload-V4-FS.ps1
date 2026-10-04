# Upload-V4-FS.ps1 — flash a Heltec V4 node's TTDB to its LittleFS partition.
#
# arduino-cli has no filesystem-upload command, so we build a LittleFS image with
# mklittlefs and write it with esptool. Targets the esp32 core's DEFAULT 4MB
# partition scheme: the "spiffs" partition at 0x290000, size 0x160000 (1.5MB).
# Tools are taken from the installed esp32 core (NOT UNIHIKER) so the LittleFS
# on-flash format matches the 3.x core the V4 firmware links against.
#
#   powershell -ExecutionPolicy Bypass -File scripts/Upload-V4-FS.ps1 -Node v4a_bridge -Port COM6
#
# ⚠ OBSOLETE FOR THE FLEET SINCE 2026-10-04: all three V4s are on huge_app, whose LittleFS
# is at 0x310000. Writing 0x290000 now lands in a V4's APP region. Use Upload-Tdeck-FS.ps1.
# Refuses to run without -LegacyDefaultTable (a V4 still on the default 4MB table).
param(
  [string]$Node = "v4a_bridge",
  [string]$Port = "COM6",
  [int]$Baud = 921600,
  [switch]$LegacyDefaultTable
)
$ErrorActionPreference = "Stop"
if (-not $LegacyDefaultTable) {
  throw "All V4s are on huge_app since 2026-10-04 (FS @0x310000): use scripts/Upload-Tdeck-FS.ps1. " +
        "This script writes 0x290000, inside the huge_app APP region. Pass -LegacyDefaultTable " +
        "only for a V4 you have verified is still on the default table."
}

$root    = Split-Path $PSScriptRoot -Parent
$dataDir = Join-Path $root "firmware\$Node\data"
$img     = Join-Path $root "firmware\$Node\littlefs.bin"

# esp32 core default.csv: spiffs, data, spiffs, 0x290000, 0x160000
$offset = "0x290000"
$size   = 0x160000      # 1474560 bytes — MUST equal the partition size

$pkg = Join-Path $env:LOCALAPPDATA "Arduino15\packages"
function Find-Tool($name) {
  $hits = Get-ChildItem $pkg -Recurse -Filter $name -ErrorAction SilentlyContinue
  # Prefer the esp32 core copy so the LittleFS format matches the firmware.
  $e = $hits | Where-Object { $_.FullName -match "\\esp32\\" } | Select-Object -First 1
  if ($e) { return $e.FullName }
  if ($hits) { return ($hits | Select-Object -First 1).FullName }
  throw "$name not found under $pkg"
}
$mklittlefs = Find-Tool "mklittlefs.exe"
$esptool    = Find-Tool "esptool.exe"

Write-Host "node      : $Node"
Write-Host "mklittlefs: $mklittlefs"
Write-Host "esptool   : $esptool"
Write-Host "Building LittleFS image ($size bytes) from $dataDir ..."
& $mklittlefs -c $dataDir -p 256 -b 4096 -s $size $img
if ($LASTEXITCODE -ne 0) { throw "mklittlefs failed ($LASTEXITCODE)" }

Write-Host "Flashing $img to $Port at $offset ..."
& $esptool --chip esp32s3 --port $Port --baud $Baud write_flash $offset $img
if ($LASTEXITCODE -ne 0) { throw "esptool failed ($LASTEXITCODE)" }
Write-Host "OK: $Node TTDB flashed to the 'spiffs' LittleFS partition (0x290000)."
