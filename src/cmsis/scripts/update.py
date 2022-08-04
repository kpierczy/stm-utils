# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Thursday, 15th July 2021 11:27:49 am
# @modified   Thursday, 4th August 2022 11:26:54 am
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

# Default URL of the github repository to be downloaded
DEFAULT_URL = 'https://github.com/ARM-software/CMSIS_5'

# ============================================================= Options ============================================================ #

# Create parser
parser = argparse.ArgumentParser(description='Updates the CMSIS sublibrary')

# Components to be updated (argument)
parser.add_argument('components', metavar='COMPONENT', type=str, nargs='*', choices=[ [], 'core', 'rtos', 'all' ],
    help='List of components to be updated')
    
# Define common arguments
utils.arguments.define_common_arguments(parser)
    
# Target repository URL (option)
parser.add_argument('-r', '--repo-url', type=str, dest='repo_url', nargs=1, default=DEFAULT_URL,
    help='URL of the target git repository')
# Target branch of the source repository (option)
parser.add_argument('-b', '--repo-branch', type=str, dest='repo_branch', nargs=1, default=None,
    help='String naming target branch for source repository')
# Target commit ID of the source repository (option)
parser.add_argument('-i', '--repo-commit', type=str, dest='repo_commit', nargs=1, default=None,
    help='String naming target commit for source repository')

# Target name of the repository directory (option)
parser.add_argument('-n', '--repo-name', type=str, dest='repo_name', nargs=1, default='stm-cmsis',
    help='Target name of the repository directory')

# Parse options
arguments = parser.parse_args()

# ====================================================== Private configuration ===================================================== #

# Define package home directory
PACKAGE_HOME = os.path.join(PROJECT_HOME, 'src/cmsis')

# Destination of the downloaded repository
CMSIS_ROOT = os.path.join(
    arguments.repo_home if type(arguments.repo_home) == str else arguments.repo_home[0],
    arguments.repo_name if type(arguments.repo_name) == str else arguments.repo_name[0]
)

# Relative path to the CMSIS-Core package inside downloaded repository
CORE_PATH = 'CMSIS/Core'
# Relative path to the CMSIS-RTOS package inside downloaded repository
RTOS_PATH = 'CMSIS/RTOS2'

# ========================================================= Parse arguments ======================================================== #

# Check if there is anything to do
if len(arguments.components) == 0:
    utils.logger.info('Nothing to do')
    exit(0)

# ======================================================== Download sources ======================================================== #

utils.logger.info('Downloading CMSIS repository (it may take a while)...')

# Parse target branch
branch = arguments.repo_branch[0] if arguments.repo_branch is not None else None
# Parse target commit
commit = arguments.repo_commit[0] if arguments.repo_commit is not None else None
# Clone repository
utils.git.download_repo(
    url=arguments.repo_url,
    directory=CMSIS_ROOT,
    cleanup=not arguments.repo_use_old,
    branch=branch,
    commit=commit
)

# Verify whether expected folder are present in the 
if not os.path.isdir(f'{CMSIS_ROOT}/{CORE_PATH}'):
    utils.logger.error('Configured path to the CMIS-Core folder is invalid!')
    exit(1)
elif not os.path.isdir(f'{CMSIS_ROOT}/{RTOS_PATH}'):
    utils.logger.error('Configured path to the CMIS-RTOS folder is invalid!')
    exit(1)

# ======================================================== Update CMSIS-Core ======================================================= #

if 'core' in arguments.components or 'all' in arguments.components:

    # Extend path to the downloaded Core sources
    CORE_PATH = f'{CMSIS_ROOT}/{CORE_PATH}'

    utils.logger.info('Updatting CMSIS-Core package...')

    # Copy new files
    utils.os.copy_glob_content(
        f'{CORE_PATH   }/Include/*',
        f'{PACKAGE_HOME}/core/include/',
        cleanup=True)

    utils.logger.info('CMSIS-Core package updated')

# ======================================================== Update CMSIS-RTOS ======================================================= #

if 'rtos' in arguments.components or 'all' in arguments.components:

    # Extend path to the downloaded RTOS sources
    RTOS_PATH = f'{CMSIS_ROOT}/{RTOS_PATH}'

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
    utils.os.refresh_directory(f'{PACKAGE_HOME}/rtos/src/rtx/src/gcc')
    # Copy new files
    utils.os.copy_glob_content(f'{RTOS_PATH}/RTX/Source/GCC/*', f'{PACKAGE_HOME}/rtos/src/rtx/src/gcc/')
    utils.os.copy_glob_content(f'{RTOS_PATH}/RTX/Source/*.h',   f'{PACKAGE_HOME}/rtos/src/rtx/src/'    )
    utils.os.copy_glob_content(f'{RTOS_PATH}/RTX/Source/*.c',   f'{PACKAGE_HOME}/rtos/src/rtx/src/'    )

    # Log update finish
    utils.logger.info('CMSIS-RTOS package updated')

# ============================================================= Cleanup ============================================================ #

# Remove downlaoded repository
if not arguments.repo_keep:
    utils.os.remove_dir(CMSIS_ROOT)

# ================================================================================================================================== #
