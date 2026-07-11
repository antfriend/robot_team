# Upload-Tdeck-FS.ps1 — flash the T-Deck console's TTDB to its LittleFS partition.
#
# Same idea as Upload-V4-FS.ps1, but for the T-Deck's SP6-T build, which uses the
# esp32 core's **huge_app** partition scheme (3MB APP / ~900KB SPIFFS) so the richer
# TTCP screen (globe + record + console) fits — the default 4MB scheme left the app
# at 95% once BLE was enabled (see PLAN.md SP6-T / memory tdeck-flash-partition-ceiling).
#
# huge_app.csv puts spiffs at offset 0x310000, size 0xE0000 (917504 B) — NOT the
# default 0x290000/0x160000 that Upload-V4-FS.ps1 targets. Flashing the FS at the
# wrong offset for the partition scheme silently corrupts the mount, so this is a
# separate script rather than a flag on the V4 one.
#
#   powershell -ExecutionPolicy Bypass -File scripts/Upload-Tdeck-FS.ps1 -Port COM10
param(
  [string]$Node = "tdeck_console",
  [string]$Port = "COM10",
  [int]$Baud = 921600
)
$ErrorActionPreference = "Stop"

$root    = Split-Path $PSScriptRoot -Parent
$dataDir = Join-Path $root "firmware\$Node\data"
$img     = Join-Path $root "firmware\$Node\littlefs.bin"

# esp32 core huge_app.csv: spiffs, data, spiffs, 0x310000, 0xE0000
$offset = "0x310000"
$size   = 0xE0000       # 917504 bytes — MUST equal the huge_app spiffs partition size

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

Write-Host "node      : $Node (huge_app)"
Write-Host "mklittlefs: $mklittlefs"
Write-Host "esptool   : $esptool"
Write-Host "Building LittleFS image ($size bytes) from $dataDir ..."
& $mklittlefs -c $dataDir -p 256 -b 4096 -s $size $img
if ($LASTEXITCODE -ne 0) { throw "mklittlefs failed ($LASTEXITCODE)" }

Write-Host "Flashing $img to $Port at $offset ..."
& $esptool --chip esp32s3 --port $Port --baud $Baud write_flash $offset $img
if ($LASTEXITCODE -ne 0) { throw "esptool failed ($LASTEXITCODE)" }
Write-Host "OK: $Node TTDB flashed to the huge_app 'spiffs' LittleFS partition (0x310000)."
