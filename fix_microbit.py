from SCons.Script import DefaultEnvironment
from os.path import exists
import os



# This is needed because the ARM assembler version doesn't like any of these flags
# env = DefaultEnvironment()
# env["ASFLAGS"] = str(env["ASFLAGS"]).replace("-x assembler-with-cpp", "").replace("-ffunction-sections -fdata-sections", "").replace("-Os", "").replace("-nostdlib", "")
#
# # Needed so we actually use the GCC one, not the one with different comments
# if exists("src/microbit-dal/asm/CortexContextSwitch.s.gcc"):
# 	os.unlink("src/microbit-dal/asm/CortexContextSwitch.s")
# 	os.rename("src/microbit-dal/asm/CortexContextSwitch.s.gcc", "src/microbit-dal/asm/CortexContextSwitch.s")
#
# # This appears to be an actual bug related to an old version of the function twi_master_init_and_clear
# i2cpp_file = "lib/microbit-dal/source/drivers/MicroBitI2C.cpp"
# i2cpp = open(i2cpp_file).read()
# i2cpp = i2cpp.replace("twi_master_init_and_clear()", "twi_master_init_and_clear(NRF_TWI1)")
# open(i2cpp_file, "w").write(i2cpp)
