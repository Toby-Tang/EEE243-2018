cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_FIND_ROOT_PATH "C:/ProgramData/WinAVR-20100110")

# toolchain settings
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSS_COMPILING 1)
set(CMAKE_C_COMPILER "C:/ProgramData/WinAVR-20100110/bin/avr-gcc.exe")
set(OBJCOPY "C:/ProgramData/WinAVR-20100110/bin/avr-objcopy.exe" CACHE PATH "objcopy" FORCE)
set(OBJDUMP "C:/ProgramData/WinAVR-20100110/bin/avr-objdump.exe" CACHE PATH "objdump" FORCE)
set(AVRSIZE "C:/ProgramData/WinAVR-20100110/bin/avr-size.exe" CACHE PATH "size" FORCE)

# Important project paths
set(BASE_PATH "${${PROJECT_NAME}_SOURCE_DIR}")
set(SRC_PATH "${BASE_PATH}/src")
set(LIB_PATH "${BASE_PATH}/lib")

# necessary settings for the chip we use
if (NOT DEFINED MCU)
    set(MCU atmega328p)
endif ()
if (NOT DEFINED F_CPU)
    set(F_CPU 2000000)
endif ()

SET(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os")
SET(CMAKE_C_LINK_FLAGS "-mmcu=${MCU}")
set(AVR_LINKER_LIBS "-lc -lm -lgcc")

include_directories(
        C:/ProgramData/WinAVR-20100110/avr/include
        C:/ProgramData/WinAVR-20100110/lib/gcc/avr/4.3.3/include
        C:/ProgramData/WinAVR-20100110/lib/gcc/avr/4.3.3/include-fixed
        C:/ProgramData/WinAVR-20100110/avr/lib/
)

# we need a little function to add multiple targets
function(add_executable_avr NAME)
    # define file names we will be using
    set(elf_file ${NAME}-${MCU}.elf)
    set(map_file ${NAME}-${MCU}.map)
    set(hex_file ${NAME}-${MCU}.hex)
    set(lst_file ${NAME}-${MCU}.lst)

    message(STATUS "Set elf_file to ${elf_file}")

    # add elf target
    add_executable(${elf_file}
            ${ARGN}
            )

    target_link_libraries(${elf_file} pololu_atmega328p)

    # set compile and link flags for elf target
    set_target_properties(
            ${elf_file}

            PROPERTIES
            COMPILE_FLAGS "-mmcu=${MCU} -w -std=c99"
            LINK_FLAGS "-mmcu=${MCU} -Wl,-Map,${map_file} ${AVR_LINKER_LIBS}"
    )

    # generate the lst file
    add_custom_command(
            OUTPUT ${lst_file}

            COMMAND
            ${OBJDUMP} -h -S ${elf_file} > ${lst_file}

            DEPENDS ${elf_file}
    )

    # create hex file
    add_custom_command(
            OUTPUT ${hex_file}

            COMMAND
            ${OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}

            DEPENDS ${elf_file}
    )

    add_custom_command(
            OUTPUT "print-size-${elf_file}"

            COMMAND
            ${AVRSIZE} ${elf_file}

            DEPENDS ${elf_file}
    )

    # build the intel hex file for the device
    add_custom_target(
            ${NAME}
            ALL
            DEPENDS ${hex_file} ${lst_file} "print-size-${elf_file}"
    )

    set_target_properties(
            ${NAME}

            PROPERTIES
            OUTPUT_NAME ${elf_file}
    )

endfunction(add_executable_avr)