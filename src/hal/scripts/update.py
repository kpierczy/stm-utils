# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Tuesday, 2nd August 2022 11:58:09 pm
# @project    stm-utils
# @brief      Updates device-specific HAL files from the official ST's github
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
URL_BASE        = 'https://github.com/STMicroelectronics/stm32'
URL_BASE_SUFFIX = 'xx_hal_driver'

# ============================================================= Options ============================================================ #

# List of supported families
SUPPORTED_FAMILIES = [ 'f0', 'f1', 'f2', 'f3', 'f4', 'f7', 'g0', 'g4', 'h7', 'l0', 'l1', 'l4', 'l5' ]

# Create parser
parser = argparse.ArgumentParser(description='Updates the CMSIS sublibrary to the newest version')
# Options
parser.add_argument('families', metavar='FAMILY', type=str, nargs='*', choices=[ [], *SUPPORTED_FAMILIES ],
    help = 'List of target families for which device sources should be updated', )
parser.add_argument('-c', '--copy-config', dest='copy_config', action='store_true', default=False,
    help='If true, script will copy original templates of config files from HAL packages')

# ====================================================== Private configuration ===================================================== #

# Define package home directory
PACKAGE_HOME = os.path.join(PROJECT_HOME, 'src/hal')

# Destination of the downloaded repository
DOWNLOAD_HAL_HOME = 'tmp_download/stm_hal'

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
    HAL_URL = URL_BASE + family + URL_BASE_SUFFIX

    # Set device's name
    DEVICE_NAME = f'stm32{family}xx'

    utils.logger.info(f'Downloading STM32{family.capitalize()} HAL repository...')

    # Clone repository
    utils.git.download_repo(HAL_URL, DOWNLOAD_HAL_HOME, cleanup=True)

    utils.logger.info(f'Copying STM32{family.capitalize()} include files...')

    # Remove old device-specific include files
    utils.os.refresh_directory(f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}')
    utils.os.refresh_directory(f'{PACKAGE_HOME}/include/ll/{DEVICE_NAME}')

    # Copy all include files from the downloaded repository
    utils.os.copy_glob_content(
        f'{DOWNLOAD_HAL_HOME}/Inc/{DEVICE_NAME}_hal*',
        f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}/')
    utils.os.copy_glob_content(
        f'{DOWNLOAD_HAL_HOME}/Inc/Legacy/*',
        f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}/Legacy/')
    utils.os.copy_glob_content(
        f'{DOWNLOAD_HAL_HOME}/Inc/{DEVICE_NAME}_ll*',
        f'{PACKAGE_HOME}/include/ll/{DEVICE_NAME}/' )
    
    # Copy configuration templates, if requested
    if options.copy_config:

        utils.logger.info(f'Copying STM32{family.capitalize()} config files...')

        # Create target directory
        utils.os.make_dir(f'{PACKAGE_HOME}/config/templates')
        # Remove old device-specific configuration files
        utils.os.remove(f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_assert_template.h')
        utils.os.remove(f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_hal_conf_template.h')
        # Move template configuration header files to the config folder
        utils.os.move(
            f'{DOWNLOAD_HAL_HOME}/Inc/stm32_assert_template.h',
            f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_assert_template.h')
        utils.os.move(
            f'{DOWNLOAD_HAL_HOME}/Inc/{DEVICE_NAME}_hal_conf_template.h',
            f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_hal_conf_template.h')

    utils.logger.info(f'Copying STM32{family.capitalize()} source files...')

    # Remove old device-specific source files
    utils.os.refresh_directory(f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}')
    utils.os.refresh_directory(f'{PACKAGE_HOME}/src/ll/{DEVICE_NAME}')
    # Copy new source files from the downloaded repository
    utils.os.copy_glob_content(
        f'{DOWNLOAD_HAL_HOME}/Src/{DEVICE_NAME}_hal*',
        f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/')
    utils.os.copy_glob_content(
        f'{DOWNLOAD_HAL_HOME}/Src/Legacy/*',
        f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/Legacy/')
    utils.os.copy_glob_content(
        f'{DOWNLOAD_HAL_HOME}/Src/{DEVICE_NAME}_ll*',
        f'{PACKAGE_HOME}/src/ll/{DEVICE_NAME}/' )

    # Remove all template files
    utils.os.remove_glob_content(f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/*_template.c')

    # Remove downlaoded repository
    utils.os.remove_dir(DOWNLOAD_HAL_HOME)

# ================================================================================================================================== #
