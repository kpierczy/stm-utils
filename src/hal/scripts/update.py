# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Monday, 1st August 2022 11:33:51 pm
# @project    stm-utils
# @brief      Updates device-specific HAL files from the official ST's github
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

import os
import sys
import coloredlogs
import logging
import shutil
import git
import glob
import argparse

# ============================================================ Constants =========================================================== #

# URL of the github repository to be downloaded
URL_BASE        = 'https://github.com/STMicroelectronics/stm32'
URL_BASE_SUFFIX = 'xx_hal_driver'

# ============================================================= Options ============================================================ #

# Create parser
parser = argparse.ArgumentParser(description='Updates the HAL sublibrary to the newest version')
# Options
parser.add_argument('-c', '--copy-config', dest='copy_config', action='store_true', default=False,
    help='If true, HAL configuration tempalte files are cloned to the config folder')

# ========================================================== Configuration ========================================================= #

# Supported devices' list
devices = [ 'f0' 'f1' 'f2' 'f3' 'f4' 'f7' 'g0' 'g4' 'h7' 'l0' 'l1' 'l4' 'l5' ]

# Supported devices update (1:on, 0:off)
if len(sys.argv) > 0 and sys.argv[0] == 'update':
    update_list = {
        'f0' : ('f0' in sys.argv),
        'f1' : ('f1' in sys.argv),
        'f2' : ('f2' in sys.argv),
        'f3' : ('f3' in sys.argv),
        'f4' : ('f4' in sys.argv),
        'f7' : ('f7' in sys.argv),
        'g0' : ('g0' in sys.argv),
        'g4' : ('g4' in sys.argv),
        'h7' : ('h7' in sys.argv),
        'l0' : ('l0' in sys.argv),
        'l1' : ('l1' in sys.argv),
        'l4' : ('l4' in sys.argv),
        'l5' : ('l5' in sys.argv),
    }

# ====================================================== Private configuration ===================================================== #

# Define package home directory
PACKAGE_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')

# ============================================================= Helpers ============================================================ #

# Helper deleting and creating the directory
def refresh_directory(dir):
    shutil.rmtree(dir, ignore_errors=True)
    os.makedirs(dir, exist_ok=True)

# Helper copying all files with the given @p pattern into @p dst
def copy_content(pattern, dst):
    for file in glob.glob(pattern):
        shutil.copy(file, dst)

# Helper deleting all files with the given @p pattern
def remove_content(pattern):
    for file in glob.glob(pattern):
        os.remove(file)

# ========================================================= Update devcies ===========================================================

# Destination of the downloaded repository
DOWNLOAD_HAL_HOME = '/tmp/stm_hal'

# Create logger
logger = logging.getLogger('hal-update')
# Set log level
coloredlogs.install(level='DEBUG', logger=logger)

# Parse options
options = parser.parse_args()

# Iterate over all devices
for device in devices:

    # Update device, if requested
    if update_list[device]:

        # URL of the downloaded repository
        HAL_URL = URL_BASE + device + URL_BASE_SUFFIX

        # Set device's name
        DEVICE_NAME = f'stm32${device}xx'

        logger.info(f'Downloading STM32${device.capitalize()} HAL repository...')

        # Remove previous download
        shutil.rmtree(DOWNLOAD_HAL_HOME, ignore_errors=True)
        # Clone repository
        git.Repo.clone_from(HAL_URL, DOWNLOAD_HAL_HOME)

        logger.info(f'Copying STM32${device.capitalize()} include files...')

        # Remove old device-specific include files
        refresh_directory(f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}')
        refresh_directory(f'{PACKAGE_HOME}/include/ll/{DEVICE_NAME}')

        # Copy all include files from the downloaded repository
        copy_content(f'{DOWNLOAD_HAL_HOME}/Inc/{DEVICE_NAME}_hal*', f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}/')
        copy_content(f'{DOWNLOAD_HAL_HOME}/Inc/Legacy',             f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}/')
        copy_content(f'{DOWNLOAD_HAL_HOME}/Inc/{DEVICE_NAME}_ll*',  f'{PACKAGE_HOME}/include/ll/{DEVICE_NAME}/' )
        
        # Copy configuration templates, if requested
        if options.copy_config:

            logger.info(f'Copying STM32${device.capitalize()} config files...')

            # Remove old device-specific configuration files
            os.remove(f'{PACKAGE_HOME}/config/{DEVICE_NAME}_assert_template.h')
            os.remove(f'{PACKAGE_HOME}/config/{DEVICE_NAME}_hal_conf_template.h')
            # Move template configuration header files to the config folder
            shutil.move(f'{PACKAGE_HOME}/include/{DEVICE_NAME}/stm32_assert_template.h'           f'{PACKAGE_HOME}/config/{DEVICE_NAME}_assert_template.h'  )
            shutil.move(f'{PACKAGE_HOME}/include/{DEVICE_NAME}/{DEVICE_NAME}_hal_conf_template.h' f'{PACKAGE_HOME}/config/{DEVICE_NAME}_hal_conf_template.h')

        logger.info(f'Copying STM32${device.capitalize()} source files...')

        # Remove old device-specific source files
        refresh_directory(f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}')
        refresh_directory(f'{PACKAGE_HOME}/src/ll/{DEVICE_NAME}')
        # Copy new source files from the downloaded repository
        copy_content(f'{DOWNLOAD_HAL_HOME}/Src/{DEVICE_NAME}_hal*', f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/')
        copy_content(f'{DOWNLOAD_HAL_HOME}/Src/Legacy',             f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/')
        copy_content(f'{DOWNLOAD_HAL_HOME}/Src/{DEVICE_NAME}_ll*',  f'{PACKAGE_HOME}/src/ll/{DEVICE_NAME}/' )

        # Remove all template files
        remove_content(f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/*_template.c')

        # Remove downlaoded repository
        shutil.rmtree(DOWNLOAD_HAL_HOME,  ignore_errors=True)

# ================================================================================================================================== #
