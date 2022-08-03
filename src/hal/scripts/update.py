# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Wednesday, 3rd August 2022 10:55:34 pm
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

# Default scheme of URL of the github repository to be downloaded
DEFAULT_URL_SCHEME = 'https://github.com/STMicroelectronics/stm32<family>xx_hal_driver'

# List of supported families
SUPPORTED_FAMILIES = [ 'f0', 'f1', 'f2', 'f3', 'f4', 'f7', 'g0', 'g4', 'h7', 'l0', 'l1', 'l4', 'l5' ]

# ============================================================ Arguments =========================================================== #

# Create parser
parser = argparse.ArgumentParser(description='Updates the HAL sublibrary')

# Define common arguments
utils.arguments.define_common_arguments(parser)
# Define family-dependent common arguments
utils.arguments.define_common_family_dependenc_arguments(parser, SUPPORTED_FAMILIES, DEFAULT_URL_SCHEME)

# Config templates copy ON/OFF (option)
parser.add_argument('-c', '--copy-config', dest='copy_config', action='store_true', default=False,
    help='If true, script will copy original templates of config files from HAL packages')

# Parse options
arguments = parser.parse_args()

# ====================================================== Private configuration ===================================================== #

# Define package home directory
PACKAGE_HOME = os.path.join(PROJECT_HOME, 'src/hal')

# Destination of the downloaded repository
HAL_ROOT = os.path.join(
    arguments.repo_home if type(arguments.repo_home) == str else arguments.repo_home[0],
    arguments.repo_name if type(arguments.repo_name) == str else arguments.repo_name[0]
)

# ========================================================= Update devcies ===========================================================

# Check if there is anything to do
if len(arguments.families) == 0:
    utils.logger.info('Nothing to do')
    exit(0)

# Check if all families are to be updated
if 'all' in arguments.families:
    arguments.families = SUPPORTED_FAMILIES

# Iterate over all devices
for family in arguments.families:

    utils.logger.info(f'Updating HAL library for {family.capitalize()} family...')

    # Parse URL schem
    url_scheme = arguments.repo_url if type(arguments.repo_url) == str else arguments.repo_url[0]
    # Download repo
    utils.arguments.download_repo(
        repo_url_scheme=url_scheme,
        repo_root=HAL_ROOT.replace('<family>', family).replace('<FAMILY>', family.capitalize()),
        family=family,
        branch_opt=arguments.repo_branch,
        commit_opt=arguments.repo_commit,
        cleanup=not arguments.repo_use_old
    )

    utils.logger.info(f' - Copying include files...')

    # Set device's name
    DEVICE_NAME = f'stm32{family}xx'

    # Remove old device-specific include files
    utils.os.refresh_directory(f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}')
    utils.os.refresh_directory(f'{PACKAGE_HOME}/include/ll/{DEVICE_NAME}')

    # Copy all include files from the downloaded repository
    utils.os.copy_glob_content(
        f'{HAL_ROOT}/Inc/{DEVICE_NAME}_hal*',
        f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}/')
    utils.os.copy_glob_content(
        f'{HAL_ROOT}/Inc/Legacy/*',
        f'{PACKAGE_HOME}/include/hal/{DEVICE_NAME}/Legacy/')
    utils.os.copy_glob_content(
        f'{HAL_ROOT}/Inc/{DEVICE_NAME}_ll*',
        f'{PACKAGE_HOME}/include/ll/{DEVICE_NAME}/' )
    
    # Copy configuration templates, if requested
    if arguments.copy_config:

        utils.logger.info(f' - Copying config files...')

        # Create target directory
        utils.os.make_dir(f'{PACKAGE_HOME}/config/templates')
        # Remove old device-specific configuration files
        utils.os.remove(f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_assert_template.h')
        utils.os.remove(f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_hal_conf_template.h')
        # Move template configuration header files to the config folder
        utils.os.move(
            f'{HAL_ROOT}/Inc/stm32_assert_template.h',
            f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_assert_template.h')
        utils.os.move(
            f'{HAL_ROOT}/Inc/{DEVICE_NAME}_hal_conf_template.h',
            f'{PACKAGE_HOME}/config/templates/{DEVICE_NAME}_hal_conf_template.h')

    utils.logger.info(f' - Copying source files...')

    # Remove old device-specific source files
    utils.os.refresh_directory(f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}')
    utils.os.refresh_directory(f'{PACKAGE_HOME}/src/ll/{DEVICE_NAME}')
    # Copy new source files from the downloaded repository
    utils.os.copy_glob_content(
        f'{HAL_ROOT}/Src/{DEVICE_NAME}_hal*',
        f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/')
    utils.os.copy_glob_content(
        f'{HAL_ROOT}/Src/Legacy/*',
        f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/Legacy/')
    utils.os.copy_glob_content(
        f'{HAL_ROOT}/Src/{DEVICE_NAME}_ll*',
        f'{PACKAGE_HOME}/src/ll/{DEVICE_NAME}/' )

    # Remove all template files
    utils.os.remove_glob_content(f'{PACKAGE_HOME}/src/hal/{DEVICE_NAME}/*_template.c')

    # Remove downlaoded repository
    if not arguments.repo_keep:
        utils.os.remove_dir(HAL_ROOT)

# ================================================================================================================================== #
