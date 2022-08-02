# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Tuesday, 2nd August 2022 11:31:49 pm
# @project    stm-utils
# @brief      Downloads CMSIS source from the given URL and replaces local files with the downloaded ones, performing general update
#             of the CMSIS-Core and CMSIS-RTOS (RT5-based) packages
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
PACKAGE_HOME = os.path.join(PROJECT_HOME, 'src/cmsis')

# Destination of the downloaded repository
DOWNLOAD_CMSIS_HOME = 'tmp_download/cmsis'

# ========================================================= Parse arguments ======================================================== #

# Parse options
options = parser.parse_args()

# Check if there is anything to do
if not options.core and not options.rtos:
    utils.logger.info('Nothing to do')
    exit(0)

# ======================================================== Download sources ======================================================== #

utils.logger.info('Downloading CMSIS repository (it may take a while)...')

# Clone repository
utils.git.download_repo(URL_BASE, DOWNLOAD_CMSIS_HOME, cleanup=True)

# Verify whether expected folder are present in the 
if not os.path.isdir(f'{DOWNLOAD_CMSIS_HOME}/{CORE_PATH}'):
    utils.logger.error('Configured path to the CMIS-Core folder is invalid!')
    exit(1)
elif not os.path.isdir(f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}'):
    utils.logger.error('Configured path to the CMIS-RTOS folder is invalid!')
    exit(1)

# ======================================================== Update CMSIS-Core ======================================================= #

if options.core:

    # Extend path to the downloaded Core sources
    CORE_PATH = f'{DOWNLOAD_CMSIS_HOME}/{CORE_PATH}'

    utils.logger.info('Updatting CMSIS-Core package...')

    # Copy new files
    utils.os.copy_glob_content(
        f'{CORE_PATH   }/Include/*',
        f'{PACKAGE_HOME}/core/include/',
        cleanup=True)

    utils.logger.info('CMSIS-Core package updated')

# ======================================================== Update CMSIS-RTOS ======================================================= #

if options.rtos:

    # Extend path to the downloaded RTOS sources
    RTOS_PATH = f'{DOWNLOAD_CMSIS_HOME}/{RTOS_PATH}'

    utils.logger.info('Updatting CMSIS-RTOS package...')

    # Copy new include files
    utils.os.copy_glob_content(
        f'{RTOS_PATH   }/Include/*',
        f'{PACKAGE_HOME}/rtos/include/',
        cleanup=True)
    
    # Copy new CMSIS RTOS files
    utils.os.copy(
        f'{RTOS_PATH   }/Source/os_systick.c',
        f'{PACKAGE_HOME}/rtos/src/',
        cleanup=True)
    
    # Update old RTX config files (remove all files except RTE_Components.h which is hand-written)
    utils.os.find_and_remove_except(
        f'{PACKAGE_HOME}/rtos/config/',
        [ 'RTE_Components.h' ])
    # Copy new files
    utils.os.copy_glob_content(
        f'{RTOS_PATH   }/RTX/Config/*',
        f'{PACKAGE_HOME}/rtos/config/')
    # Rename handlers configuration file
    utils.os.move(
        f'{PACKAGE_HOME}/rtos/config/handlers.c',
        f'{PACKAGE_HOME}/rtos/config/RTX_Handlers.c')

    # Copy new RTX5 include files
    utils.os.copy_glob_content(
        f'{RTOS_PATH   }/RTX/Include/*',
        f'{PACKAGE_HOME}/rtos/src/rtx/include/',
        cleanup=True)

    # Update old RTX source files
    utils.os.refresh_directory(f'{PACKAGE_HOME}/rtos/src/rtx/src')
    # Copy new files
    utils.os.copy_glob_content(f'{RTOS_PATH}/RTX/Source/GCC/*', f'{PACKAGE_HOME}/rtos/src/rtx/src/gcc/')
    utils.os.copy_glob_content(f'{RTOS_PATH}/RTX/Source/*.h',   f'{PACKAGE_HOME}/rtos/src/rtx/src/'    )
    utils.os.copy_glob_content(f'{RTOS_PATH}/RTX/Source/*.c',   f'{PACKAGE_HOME}/rtos/src/rtx/src/'    )

    # Log update finish
    utils.logger.info('CMSIS-RTOS package updated')

# ============================================================= Cleanup ============================================================ #

# Remove downlaoded repository
utils.os.remove_dir(DOWNLOAD_CMSIS_HOME)

# ================================================================================================================================== #
