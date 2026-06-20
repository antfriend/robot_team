# Upload-K10-FS.ps1 — flash the K10's TTDB to its LittleFS partition.
#
# arduino-cli has no filesystem-upload command, so we build a LittleFS image
# with mklittlefs and write it with esptool. Targets the UNIHIKER K10's
# large_spiffs_16MB scheme: the "model" partition (subtype spiffs) at 0x510000,
# size 4563k. Tools are taken from the installed UNIHIKER core so the LittleFS
# on-flash format matches the 2.x core the firmware links against.
#
#   powershell -ExecutionPolicy Bypass -File scripts/Upload-K10-FS.ps1 -Port COM5
param(
  [string]$Port = "COM3",
  [int]$Baud = 921600
)
$ErrorActionPreference = "Stop"

$root    = Split-Path $PSScriptRoot -Parent
$dataDir = Join-Path $root "firmware\k10_percept\data"
$img     = Join-Path $root "firmware\k10_percept\littlefs.bin"

# large_spiffs_16MB.csv: model, data, spiffs, 0x510000, 4563k
$offset = "0x510000"
$size   = 4563 * 1024   # 4672512 bytes — MUST equal the partition size

$pkg = Join-Path $env:LOCALAPPDATA "Arduino15\packages"
function Find-Tool($name) {
  $hits = Get-ChildItem $pkg -Recurse -Filter $name -ErrorAction SilentlyContinue
  $u = $hits | Where-Object { $_.FullName -match "UNIHIKER" } | Select-Object -First 1
  if ($u) { return $u.FullName }
  if ($hits) { return ($hits | Select-Object -First 1).FullName }
  throw "$name not found under $pkg"
}
$mklittlefs = Find-Tool "mklittlefs.exe"
$esptool    = Find-Tool "esptool.exe"

Write-Host "mklittlefs: $mklittlefs"
Write-Host "esptool   : $esptool"
Write-Host "Building LittleFS image ($size bytes) from $dataDir ..."
& $mklittlefs -c $dataDir -p 256 -b 4096 -s $size $img
if ($LASTEXITCODE -ne 0) { throw "mklittlefs failed ($LASTEXITCODE)" }

Write-Host "Flashing $img to $Port at $offset ..."
& $esptool --chip esp32s3 --port $Port --baud $Baud write_flash $offset $img
if ($LASTEXITCODE -ne 0) { throw "esptool failed ($LASTEXITCODE)" }
Write-Host "OK: K10 TTDB flashed to the 'model' LittleFS partition."
