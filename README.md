1. Edit  ~/.platformio/packages/framework-mbed/variant/NRF51_MICROBIT/mbed/TARGET_NRF51_MICROBIT/TOOLCHAIN_GCC_ARM/NRF51822.ld and changed the Flash origin to "0x0001C000"
2. Run "platformio run"
3. Make sure you've got [SRecord](http://srecord.sourceforge.net/) installed (`brew install srecord` works on a Mac)
4. `srec_cat lib/microbit-targets/bbc-microbit-classic-gcc-s130/bootloader/BLE_BOOTLOADER_RESERVED.hex -intel lib/microbit-targets/bbc-microbit-classic-gcc-s130/softdevice/s130_nrf51_1.0.0_softdevice.hex -intel .pioenvs/bbcmicrobit/firmware.hex -intel -o microbit-combined.hex -intel --line-length=44`
5. Copy `microbit-combined.hex` to the root of your Microbit
