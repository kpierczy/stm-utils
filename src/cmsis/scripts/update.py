# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Monday, 1st August 2022 11:04:37 pm
# @project    stm-utils
# @brief      Downloads CMSIS source from the given URL and replaces local files with the downloaded ones, performing general update
#             of the CMSIS-Core and CMSIS-RTOS (RT5-based) packages
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

import os
from pydoc import isdata
import sys
import coloredlogs
import logging
import shutil
import git
import glob
import argparse

# ============================================================ Constants =========================================================== #

# URL of the github repository to be downloaded
URL_BASE = 'https://github.com/ARM-software/CMSIS_5'

# Relative path to the CMSIS-Core package inside downloaded repository
CORE_PATH = 'CMSIS/Core'
# Relative path to the CMSIS-RTOS package inside downloaded repository
RTOS_PATH = 'CMSIS/RTOS2'

# ============================================================= Options ============================================================ #

# Create parser
parser = argparse.ArgumentParser(description='Updates the CMSIS sublibrary to the newest version')
# Options
parser.add_argument('-c', '--core', dest='core', action='store_true', default=False,
    help='If true, CMSIS Core will be updated')
parser.add_argument('-r', '--rtos', dest='rtos', action='store_true', default=False,
    help='If true, CMSIS RTOS will be updated')

# ====================================================== Private configuration ===================================================== #

# Define package home directory
PACKAGE_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')

# ============================================================= Helpers ============================================================ #

# Helper copying all files with the given @p pattern into @p dst
def copy_content(pattern, dst):
    if not os.path.isdir(dst):
        os.makedirs(dst)
    for file in glob.glob(pattern):
        shutil.copy(file, dst)

# Helper deleting all files with the given @p pattern
def remove_content(pattern):
    for file in glob.glob(pattern):
        os.remove(file)

# Finds files in the @ directory and removes all except @p file 
def find_and_remove_except(file, directory):
    for roots, dirs, files in os.walk(directory):
        for f in files:
            if not f.endswith(file):
                os.remove(f)

# ========================================================= Update devcies ===========================================================

# Destination of the downloaded repository
DOWNLOAD_CMSIS_HOME = '/tmp/cmsis'

# Create logger
logger = logging.getLogger(__name__)
# Set log level
coloredlogs.install(level='DEBUG', logger=logger)

# Parse options
options = parser.parse_args()

# ======================================================== Download sources ======================================================== #

# Check if there is anything to do
if not options['core'] and not options['rtos']:
    logger.info('Nothing to do')
    exit(0)

logger.info('Downloading CMSIS repository (it may take a while)...')

# Remove previous download
shutil.rmtree(DOWNLOAD_CMSIS_HOME, ignore_errors=True)
# Clone repository
git.Repo.clone_from(URL_BASE, DOWNLOAD_CMSIS_HOME)

# Verify whether expected folder are present in the 
if not os.path.isdir(f'{DOWNLOAD_CMSIS_HOME}/{CORE_PATH}'):
    logger.error('Configured path to the CMIS-Core folder is invalid!')
    exit(1)
elif not os.path.isdir(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}'):
    logger.error('Configured path to the CMIS-RTOS folder is invalid!')
    exit(1)

# ======================================================== Update CMSIS-Core ======================================================= #

if options['core']:

    logger.info('Updatting CMSIS-Core package...')

    # Remove old files
    shutil.rmtree(f'{PACKAGE_HOME}/core/include', ignore_errors=True)
    # Copy new files
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/{CORE_PATH}/Include/*', f'{PACKAGE_HOME}/core/include/')

    logger.info('CMSIS-Core package updated')

# ======================================================== Update CMSIS-RTOS ======================================================= #

if options['rtos']:

    logger.info('Updatting CMSIS-RTOS package...')

    # Update old CMSIS-RTOS include files
    shutil.rmtree(f'{PACKAGE_HOME}/rtos/include', ignore_errors=True)
    # Copy new files
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}/Include/*', f'{PACKAGE_HOME}/rtos/include/')
    
    # Update old CMSIS-RTOS source files
    shutil.rmtree(f'{PACKAGE_HOME}/rtos/src', ignore_errors=True)
    # Copy new files
    shutil.copy(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}/Source/os_systick.c', f'{PACKAGE_HOME}/rtos/src/os_systick.c')
    
    # Update old RTX config files (remove all files except RTE_Components.h which is hand-written)
    find_and_remove_except('RTE_Components.h', f'{PACKAGE_HOME}/rtos/config')
    # Copy new files
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/RTOS_PATH/RTX/Config/*', f'{PACKAGE_HOME}/rtos/config/')
    # Rename handlers configuration file
    shutil.move(f'{PACKAGE_HOME}/rtos/config/handlers.c', f'{PACKAGE_HOME}/rtos/config/RTX_Handlers.c')

    # Update old RTX include files
    shutil.rmtree(f'{PACKAGE_HOME}/rtos/src/rtx/include', ignore_errors=True)
    # Copy new files
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}/RTX/Include/*', f'{PACKAGE_HOME}/rtos/src/rtx/include/')

    # Update old RTX source files
    shutil.rmtree(f'{PACKAGE_HOME}/rtos/src/rtx/src', ignore_errors=True)
    # Copy new files
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}/RTX/Source/GCC/*', f'{PACKAGE_HOME}/rtos/src/rtx/src/gcc/')
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}/RTX/Source/*.h',   f'{PACKAGE_HOME}/rtos/src/rtx/src/'    )
    copy_content(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}/RTX/Source/*.c',   f'{PACKAGE_HOME}/rtos/src/rtx/src/'    )

    # Log update finish
    logger.info('CMSIS-RTOS package updated')

# ============================================================= Cleanup ============================================================ #

# Remove downlaoded repository
shutil.rmtree(DOWNLOAD_CMSIS_HOME, ignore_errors=True)

# ================================================================================================================================== #
