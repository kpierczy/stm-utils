# ====================================================================================================================================
# @file       device.cmake
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 2:11:27 pm
# @modified   Wednesday, 3rd August 2022 2:03:35 am
# @project    stm-utils
# @brief      Helper script selecting appropriate device include file and architecture based on the device model
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# Target device
set(DEVICE "Unknown" CACHE STRING "Target device (as checked in stm32xxxx.h files)")

# ====================================================================================================================================
# -------------------------------------------------------- Supported devices ---------------------------------------------------------
# ====================================================================================================================================

# Support devices' list (F0)
list(APPEND DEVICES_F0
    "STM32F030x6" "STM32F030x8" "STM32F031x6" "STM32F038xx" "STM32F042x6" "STM32F048xx"
    "STM32F070x6" "STM32F051x8" "STM32F058xx" "STM32F071xB" "STM32F072xB" "STM32F078xx"
    "STM32F070xB" "STM32F091xC" "STM32F098xx" "STM32F030xC"
)

# Support devices' list (F1)
list(APPEND DEVICES_F1
    "STM32F100xB" "STM32F100xE" "STM32F101x6" "STM32F101xB" "STM32F101xE" "STM32F101xG"
    "STM32F102x6" "STM32F102xB" "STM32F103x6" "STM32F103xB" "STM32F103xE" "STM32F103xG"
    "STM32F105xC" "STM32F107xC"
)


# Support devices' list (F2)
list(APPEND DEVICES_F2
    "STM32F205xx" "STM32F215xx" "STM32F207xx" "STM32F217xx"
)

# Support devices' list (F3)
list(APPEND DEVICES_F3
    "STM32F301x8" "STM32F302x8" "STM32F318xx" "STM32F302xC" "STM32F303xC" "STM32F358xx"
    "STM32F303x8" "STM32F334x8" "STM32F328xx" "STM32F302xE" "STM32F303xE" "STM32F398xx"
    "STM32F373xC" "STM32F378xx"
)

# Supported devices' list (F4)
list(APPEND DEVICES_F4 
    "STM32F405xx" "STM32F415xx" "STM32F407xx" "STM32F417xx" "STM32F427xx" "STM32F437xx"
    "STM32F429xx" "STM32F439xx" "STM32F401xC" "STM32F401xE" "STM32F410Tx" "STM32F410Cx"
    "STM32F410Rx" "STM32F411xE" "STM32F446xx" "STM32F469xx" "STM32F479xx" "STM32F412Cx"
    "STM32F412Zx" "STM32F412Rx" "STM32F412Vx" "STM32F413xx" "STM32F423xx"
)

# Support devices' list (F7)
list(APPEND DEVICES_F7
    "STM32F756xx" "STM32F746xx" "STM32F745xx" "STM32F765xx" "STM32F767xx" "STM32F769xx"
    "STM32F777xx" "STM32F779xx" "STM32F722xx" "STM32F723xx" "STM32F732xx" "STM32F733xx"
    "STM32F730xx" "STM32F750xx"
)

# Support devices' list (G0)
list(APPEND DEVICES_G0
    "STM32G071xx" "STM32G081xx" "STM32G070xx" "STM32G030xx" "STM32G031xx" "STM32G041xx"
    "STM32G0B0xx" "STM32G0B1xx" "STM32G0C1xx" "STM32G050xx" "STM32G051xx" "STM32G061xx"
)

# Support devices' list (G4)
list(APPEND DEVICES_G4
    "STM32G431xx" "STM32G441xx" "STM32G471xx" "STM32G473xx" "STM32G474xx" "STM32G484xx"
    "STM32GBK1CB" "STM32G491xx" "STM32G4A1xx"
)

# Support devices' list (H7)
list(APPEND DEVICES_H7
    "STM32H743xx" "STM32H753xx" "STM32H750xx" "STM32H742xx" "STM32H745xx" "STM32H755xx"
    "STM32H747xx" "STM32H757xx" "STM32H7A3xx" "STM32H7A3xxQ" "STM32H7B3xx" "STM32H7B3xxQ"
    "STM32H7B0xx" "STM32H7B0xxQ" "STM32H735xx" "STM32H733xx" "STM32H730xx" "STM32H730xxQ"
    "STM32H725xx" "STM32H723xx" 
)

# Support devices' list (L0)
list(APPEND DEVICES_L0
    "STM32L010x4" "STM32L010x6" "STM32L010x8" "STM32L010xB" "STM32L011xx" "STM32L021xx"
    "STM32L031xx" "STM32L041xx" "STM32L051xx" "STM32L052xx" "STM32L053xx" "STM32L062xx"
    "STM32L063xx" "STM32L071xx" "STM32L072xx" "STM32L073xx" "STM32L081xx" "STM32L082xx"
    "STM32L083xx"
)

# Support devices' list (L1)
list(APPEND DEVICES_L1
    "STM32L100xB" "STM32L100xBA" "STM32L100xC" "STM32L151xB" "STM32L151xBA" "STM32L151xC"
    "STM32L151xCA" "STM32L151xD" "STM32L151xDX" "STM32L151xE" "STM32L152xB" "STM32L152xBA"
    "STM32L152xC" "STM32L152xCA" "STM32L152xD" "STM32L152xDX" "STM32L152xE" "STM32L162xC"
    "STM32L162xCA" "STM32L162xD" "STM32L162xDX" "STM32L162xE"
)

# Support devices' list (L4)
list(APPEND DEVICES_L4
    "STM32L412xx" "STM32L422xx" "STM32L431xx" "STM32L432xx" "STM32L433xx" "STM32L442xx"
    "STM32L443xx" "STM32L451xx" "STM32L452xx" "STM32L462xx" "STM32L471xx" "STM32L475xx"
    "STM32L476xx" "STM32L485xx" "STM32L486xx" "STM32L496xx" "STM32L4A6xx" "STM32L4P5xx"
    "STM32L4Q5xx" "STM32L4R5xx" "STM32L4R7xx" "STM32L4R9xx" "STM32L4S5xx" "STM32L4S7xx"
    "STM32L4S9xx"
)

# Support devices' list (L5)
list(APPEND DEVICES_L5
    "STM32L552xx" "STM32L562xx"
)

# ====================================================================================================================================
# ----------------------------------------------------- Device info's dispatch -------------------------------------------------------
# ====================================================================================================================================

# Select required variables based on the device
if(${DEVICE} IN_LIST DEVICES_F0)
    set(Architecture "armv6m")
    set(DeviceFamily "stm32f0xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_F0")
elseif(${DEVICE} IN_LIST DEVICES_F1)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32f1xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_F1")
elseif(${DEVICE} IN_LIST DEVICES_F2)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32f2xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_F2")
elseif(${DEVICE} IN_LIST DEVICES_F3)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32f3xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_F3")
elseif(${DEVICE} IN_LIST DEVICES_F4)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32f4xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_F4")
elseif(${DEVICE} IN_LIST DEVICES_F7)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32f7xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_F7")
elseif(${DEVICE} IN_LIST DEVICES_G0)
    set(Architecture "armv6m")
    set(DeviceFamily "stm32g0xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_G0")
elseif(${DEVICE} IN_LIST DEVICES_G4)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32g4xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_G4")
elseif(${DEVICE} IN_LIST DEVICES_H7)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32h7xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_H7")
elseif(${DEVICE} IN_LIST DEVICES_L0)
    set(Architecture "armv6m")
    set(DeviceFamily "stm32l0xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_L0")
elseif(${DEVICE} IN_LIST DEVICES_L1)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32l1xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_L1")
elseif(${DEVICE} IN_LIST DEVICES_L4)
    set(Architecture "armv7m")
    set(DeviceFamily "stm32l4xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_L4")
elseif(${DEVICE} IN_LIST DEVICES_L5)
    set(Architecture "armv8mmbl")
    set(DeviceFamily "stm32l5xx")
    set(DeviceType   "STM32MCU_MAJOR_TYPE_L5")
else()
    message(FATAL_ERROR "Unknown target device (${DEVICE})") 
endif()

# Define device's CMSIS header
set(DeviceInclude ${DeviceFamily}.h)
