# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Tuesday, 2nd August 2022 10:50:29 pm
# @project    stm-utils
# @brief      Updates CMSIS device files from official ST's github
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

import sys
import os

# ========================================================== Configuration ========================================================= #

# Path to the main project's dircetory
PROJECT_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../../..')

# Add python module to the PATH containing links definitions
sys.path.append(os.path.join(PROJECT_HOME, 'scripts'))

# ============================================================= Imports ============================================================ #

import argparse
import utils

# ========================================================== Configuration ========================================================= #

# URL of the github repository to be downloaded
URL_BASE = 'https://github.com/STMicroelectronics/cmsis_device'

# ============================================================= Options ============================================================ #

# List of supported families
SUPPORTED_FAMILIES = [ 'f0', 'f1', 'f2', 'f3', 'f4', 'f7', 'g0', 'g4', 'h7', 'l0', 'l1', 'l4', 'l5' ]

# Create parser
parser = argparse.ArgumentParser(description='Updates the CMSIS sublibrary to the newest version')
# Options
parser.add_argument('families', metavar='FAMILY', type=str, nargs='*', choices=[ [], *SUPPORTED_FAMILIES ],
    help = 'List of target families for which device sources should be updated', )

# ====================================================== Private configuration ===================================================== #

# Define package home directory
PACKAGE_HOME = os.path.join(PROJECT_HOME, 'src/device')

# Destination of the downloaded repository
DOWNLOAD_DEVICE_HOME = 'tmp_download/stm_device'

# ========================================================= Parse arguments ======================================================== #

# Parse options
options = parser.parse_args()

# Check if there is anything to do
if len(options.families) == 0:
    utils.logger.info('Nothing to do')
    exit(0)

# ========================================================= Update devcies ===========================================================

# Iterate over all devices
for family in options.families:

    # URL of the downloaded repository
    DEVICE_URL = f'{URL_BASE}_{family}'

    utils.logger.info(f'Downloading STM32{family.capitalize()} repository...')

    # Clone repository
    utils.git.download_repo(DEVICE_URL, DOWNLOAD_DEVICE_HOME, cleanup=True)

    utils.logger.info(f'Copying STM32{family.capitalize()} include files...')

    # Remove old device-specific include files
    utils.os.refresh_directory(f'{PACKAGE_HOME}/include/device/stm32{family}xx')
    # Remove aggregating header
    utils.os.remove(f'{PACKAGE_HOME}/include/device/stm32{family}xx.h')

    # Copy all include files from the downloaded repository
    utils.os.copy_glob_content(
        f'{DOWNLOAD_DEVICE_HOME}/Include/*',
        f'{PACKAGE_HOME}/include/device/stm32{family}xx/')
    # Move aggregating header to the upper folder
    utils.os.move(
        f'{PACKAGE_HOME}/include/device/stm32{family}xx/stm32{family}xx.h',
        f'{PACKAGE_HOME}/include/device/stm32{family}xx.h')

    utils.logger.info(f'Copying STM32{family.capitalize()} source files...')

    # Remove old device-specific source files
    utils.os.remove(f'{PACKAGE_HOME}/src/device/system_stm32{family}xx.c')
    # Copy new source files from the downloaded repository
    utils.os.copy(
        f'{DOWNLOAD_DEVICE_HOME}/Source/Templates/system_stm32{family}xx.c',
        f'{PACKAGE_HOME}/src/device/')

    # Remove downlaoded repository
    utils.os.remove_dir(DOWNLOAD_DEVICE_HOME)

# ================================================================================================================================== #
