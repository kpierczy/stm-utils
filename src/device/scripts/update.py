# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Monday, 1st August 2022 10:29:53 pm
# @project    stm-utils
# @brief      Updates CMSIS device files from official ST's github
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

from codecs import ignore_errors
import os
import sys
import coloredlogs
import logging
import shutil
import git
import glob

# ============================================================ Constants =========================================================== #

# URL of the github repository to be downloaded
URL_BASE = 'https://github.com/STMicroelectronics/cmsis_device'

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
DOWNLOAD_DEVICE_HOME = '/tmp/stm_device'

# Create logger
logger = logging.getLogger(__name__)
# Set log level
coloredlogs.install(level='DEBUG', logger=logger)

# Iterate over all devices
for device in devices:

    # Update device, if requested
    if update_list[device]:

        # URL of the downloaded repository
        DEVICE_URL = f'{URL_BASE}_{device}'

        logger.info(f'Downloading STM32${device.capitalize()} repository...')

        # Remove previous download
        shutil.rmtree(DOWNLOAD_DEVICE_HOME, ignore_errors=True)        
        # Clone repository
        git.Repo.clone_from(DEVICE_URL, DOWNLOAD_DEVICE_HOME)

        logger.info(f'Copying STM32${device.capitalize()} include files...')

        # Remove old device-specific include files
        shutil.rmtree(f'{PACKAGE_HOME}/include/device/stm32{device}xx', ignore_errors=True)
        # Create destination directory
        os.makedirs(f'{PACKAGE_HOME}/include/device/stm32{device}xx', exist_ok=True)
        # Remove aggregating header
        os.remove('{PACKAGE_HOME}/include/device/stm32{device}xx.h', ignore_errors=True)
        # Copy all include files from the downloaded repository
        copy_content(f'{DOWNLOAD_DEVICE_HOME}/Include/*', f'{PACKAGE_HOME}/include/device/stm32{device}xx/')
        # Move aggregating header to the upper folder
        shutil.move(
            f'{PACKAGE_HOME}/include/device/stm32{device}xx/stm32{device}xx.h',
            f'{PACKAGE_HOME}/include/device/stm32{device}xx.h'
        )

        logger.info(f'Copying STM32${device.capitalize()} source files...')

        # Remove old device-specific source files
        os.remove(f'{PACKAGE_HOME}/src/device/system_stm32{device}xx.c')
        # Copy new source files from the downloaded repository
        shutil.copy(f'{DOWNLOAD_DEVICE_HOME}/Source/Templates/system_stm32{device}xx.c', f'{PACKAGE_HOME}/src/device/')

        # Remove downlaoded repository
        shutil.rmtree(DOWNLOAD_DEVICE_HOME,  ignore_errors=True)

# ================================================================================================================================== #
