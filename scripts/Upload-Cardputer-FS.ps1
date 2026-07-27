# Upload-Cardputer-FS.ps1 — flash the Cardputer ADV console's TTDB globes to LittleFS.
#
# Identical in shape to Upload-Tdeck-FS.ps1, and for the same reason: the Cardputer
# build uses the esp32 core's **huge_app** partition scheme (3MB APP / ~900KB SPIFFS)
# so the screen UI + BLE fit. huge_app.csv puts spiffs at offset 0x310000, size
# 0xE0000 — NOT the default 0x290000/0x160000 that Upload-V4-FS.ps1 targets. Flashing
# the FS at the wrong offset for the scheme silently corrupts the mount (the node then
# boots to an empty globe with the app otherwise fine), so this stays a separate script
# rather than a flag on another one.
#
# The Cardputer ADV has 8MB of flash, but the huge_app layout only describes the first
# 4MB; the remaining 4MB is unallocated. That is deliberate for now — it keeps this
# node's offsets identical to the T-Deck's, which is one less thing to get wrong at the
# bench. Repartitioning is a separate, deliberate change (and would move this offset).
#
# The whole data/ dir is imaged, so all three globes go on: ttdb.md (the mesh fleet
# globe), rfc.ttdb.md (the RFC corpus), feelings.ttdb.md (the default power-up view).
#
#   powershell -ExecutionPolicy Bypass -File scripts/Upload-Cardputer-FS.ps1 -Port COM12
param(
  [string]$Node = "cardputer_console",
  [string]$Port = "COM12",
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
