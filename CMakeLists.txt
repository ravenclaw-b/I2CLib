cmake_minimum_required(VERSION 3.12)

# Project name
project(I2CLib 
        VERSION 1.0.0
        DESCRIPTION "Bit-banged I2C library for AVR microcontrollers"
        LANGUAGES C CXX)

# Create the library target
add_library(i2c_lib STATIC
    lib/I2C/I2C.cpp
)

# Set the target's include directories
target_include_directories(i2c_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/I2C
)

# Set compile options for AVR
target_compile_options(i2c_lib
    PRIVATE
        -mmcu=atmega328p  # Target MCU
        -Os               # Optimize for size
        -Wall            # Enable all warnings
        -Wextra          # Enable extra warnings
)

# Set properties specific to AVR
set_target_properties(i2c_lib PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Installation rules
install(TARGETS i2c_lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES lib/I2C/I2C.h
    DESTINATION include/I2C
)