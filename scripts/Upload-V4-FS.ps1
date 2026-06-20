# Upload-V4-FS.ps1 — flash a Heltec V4 node's TTDB to its LittleFS partition.
#
# arduino-cli has no filesystem-upload command, so we build a LittleFS image with
# mklittlefs and write it with esptool. Targets the esp32 core's DEFAULT 4MB
# partition scheme: the "spiffs" partition at 0x290000, size 0x160000 (1.5MB).
# Tools are taken from the installed esp32 core (NOT UNIHIKER) so the LittleFS
# on-flash format matches the 3.x core the V4 firmware links against.
#
#   powershell -ExecutionPolicy Bypass -File scripts/Upload-V4-FS.ps1 -Node v4a_bridge -Port COM6
param(
  [string]$Node = "v4a_bridge",
  [string]$Port = "COM6",
  [int]$Baud = 921600
)
$ErrorActionPreference = "Stop"

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
