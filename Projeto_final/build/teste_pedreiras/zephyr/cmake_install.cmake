# Install script for directory: C:/ncs/v3.1.1/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/ncs/toolchains/c1a76fddb2/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/fpmp0/OneDrive/Documentos/Nordic/teste_pedreiras/build/teste_pedreiras/zephyr/cmake/reports/cmake_install.cmake")
endif()

