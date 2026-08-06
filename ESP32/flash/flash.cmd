@echo off

cls
echo ---------------------------------
echo FLASH FIRWARE
echo ---------------------------------
echo.
set COM_ESP=COM23

echo Port COM cible: %COM_ESP%
reg query HKLM\HARDWARE\DEVICEMAP\SERIALCOMM

pause

"C:\Users\FR22048\.platformio\penv\Scripts\python.exe" "C:\Users\FR22048\.platformio\packages\tool-esptoolpy\esptool.py"  ^
    --chip esp32s3 ^
    --port %COM_ESP% ^
    --baud 460800 ^
    --before default_reset ^
    --after hard_reset ^
    write_flash ^
    -z ^
    --flash_mode dio ^
    --flash_freq 80m ^
    --flash_size 16MB ^
    0x0000 bootloader.bin ^
    0x8000 partitions.bin ^
    0xe000 boot_app0.bin ^
    0x10000 firmware.bin

    pause