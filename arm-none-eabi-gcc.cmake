INCLUDE(CMakeForceCompiler)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

SET(COMMON_FLAGS "-mcpu=cortex-m3 -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -Wall -Wextra -Wshadow  \
 -Wredundant-decls -Wno-missing-field-initializers -pipe")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc ${COMMON_FLAGS})
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++ ${COMMON_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32L152RBTX_FLASH.ld)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

#set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
#set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
#set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

SET(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m3 -Wl,-gc-sections -T ${LINKER_SCRIPT} --specs=nosys.specs --specs=nano.specs \
 -ffreestanding -Wl,-u,_printf_float -Wl,-u,_scanf_float -Wl,-u,vfprintf -Wl,-u,cosf -Wl,-u,sinf -lm")


set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)