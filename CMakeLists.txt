cmake_minimum_required(VERSION 3.15.3)

project(stm32)

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_C_FLAGS "-g")

add_definitions(-DSTM32L152xB)

set(STM32CUBEMX_GENERATED_FILES
		Core/Src/main.c
		Core/Src/stm32l1xx_hal_msp.c
		Core/Src/stm32l1xx_it.c
		Core/Src/syscalls.c
		Core/Src/sysmem.c
		Core/Src/system_stm32l1xx.c
		Core/Src/LCD.c
		
		Core/Startup/startup_stm32l152rbtx.s
		
		Core/Inc/main.h
		Core/Inc/stm32l1xx_hal_conf.h
		Core/Inc/stm32l1xx_it.h
		Core/Inc/LCD.h
		
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_cortex.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_dma.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_exti.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ex.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash_ramfunc.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_flash.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_gpio.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr_ex.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_pwr.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc_ex.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_rcc.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim_ex.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal_tim.c
		Drivers/STM32L1xx_HAL_Driver/Src/stm32l1xx_hal.c)

include_directories(Core/Inc)
include_directories(Core/Src)
include_directories(Core/Startup)
include_directories(Drivers/STM32L1xx_HAL_Driver/Src)
include_directories(Drivers/STM32L1xx_HAL_Driver/Inc)
include_directories(Drivers/STM32L1xx_HAL_Driver/Inc/Legacy)
include_directories(Drivers/CMSIS/Device/ST/STM32L1xx/Include)
include_directories(Drivers/CMSIS/Include)

add_executable(${PROJECT_NAME}.elf ${STM32CUBEMX_GENERATED_FILES})

#target_link_libraries(${PROJECT_NAME}.elf STM32CUBEMX_GENERATED_FILES)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map")
set(HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
