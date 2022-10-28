# ====================================================================================================================================
# @file       update.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 3rd August 2022 10:54:18 pm
# @modified   Friday, 28th October 2022 10:54:12 pm
# @project    stm-utils
# @brief      Wrapper script providing unified update interface for dependent packages of the project
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Unix, Windows
   :synopsis: Wrapper script providing unified update interface for dependent packages of the project

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

import sys
import os

# ========================================================== Configuration ========================================================= #

# Path to the main project's dircetory
PROJECT_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)))

# Add python module to the PATH containing links definitions
sys.path.append(os.path.join(PROJECT_HOME, 'scripts'))

# ============================================================ Imports ============================================================= #

import utils
import argparse
import subprocess

# ============================================================ Arguments =========================================================== #

# Create parser
parser = argparse.ArgumentParser(description=
    'Updates components of the project. To update all variants of all components run ' + 
    '`update.py all --families all --cmsis-components all`'
)

# Components to be updated (argument)
parser.add_argument('components', metavar='COMPONENT', type=str, nargs='*', choices=[ [], 'cmsis', 'device', 'hal', 'all' ],
    help='List of components to be updated')

# ======================================================== Options (common) ======================================================== #

# Define common options
utils.arguments.define_common_arguments(parser)

# Families to be updated (argument)
parser.add_argument('-f', '--families', dest='families', type=str, nargs='+', choices=[ 'all', *utils.config.SUPPORTED_FAMILIES ],
    help='List of target families for which sources should be updated')

# ========================================================= Options (cmsis) ======================================================== #
    
# Families to be updated (argument)
parser.add_argument('--cmsis-components', dest='cmsis_components', type=str, nargs='+', choices=[ 'core', 'rtos', 'all' ], default=['all'],
    help='List of target CMSIS components to be updated')

# Target repository URL (option)
parser.add_argument('--cmsis-repo-url', type=str, dest='cmsis_repo_url', nargs=1, default=None,
    help='URL of the target git repository for the CMSIS module')
# Target branch of the source repository (option)
parser.add_argument('--cmsis-repo-branch', type=str, dest='cmsis_repo_branch', nargs=1, default=None,
    help='String naming target branch for source repository for the CMSIS module')
# Target commit ID of the source repository (option)
parser.add_argument('--cmsis-repo-commit', type=str, dest='cmsis_repo_commit', nargs=1, default=None,
    help='String naming target commit for source repository for the CMSIS module')

# Target name of the repository directory (option)
parser.add_argument('--cmsis-repo-name', type=str, dest='cmsis_repo_name', nargs=1, default=None,
    help='Target name of the repository directory for the CMSIS module')

# ======================================================== Options (Device) ======================================================== #

# Target repository URL scheme (option)
parser.add_argument('--device-repo-url-scheme', type=str, dest='device_repo_url', nargs=1, default=None,
    help='URL scheme of the target git repository for the Device module. Every occurence of "<family>" ' +
        'will be replaced with the actual family identifier (if <FAMILY> given, the identifier will be uppercased)')
# Target branch of the source repository (option)
parser.add_argument('--device-repo-branch', type=str, dest='device_repo_branch', nargs=1, default=None,
    help='Either string naming target branch for all source repositories for the Device module or a ' +
        'JSON dictionary holding branches names matched for the given family (note that JSON dictionary is ' +
        'expected to define members with keys wrapped in \"\" not \'\')')
# Target commit ID of the source repository (option)
parser.add_argument('--device-repo-commit', type=str, dest='device_repo_commit', nargs=1, default=None,
    help='JSON dictionary holding branches names for the Device module matched for the given family ' +
        '(note that JSON dictionary is expected to define members with keys wrapped in \"\" not \'\')')

# Target name of the repository directory (option)
parser.add_argument('--device-repo-name', type=str, dest='device_repo_name', nargs=1, default=None,
    help='Target name of the repository directory for the Device module. Every occurence of "<family>" ' +
         'will be replaced with the actual family identifier (if <FAMILY> given, the identifier will be ' +
         'uppercased)')

# ========================================================== Options (HAL) ========================================================= #

# Target repository URL scheme (option)
parser.add_argument('--HAL-repo-url-scheme', type=str, dest='hal_repo_url', nargs=1, default=None,
    help='URL scheme of the target git repository for the HAL module. Every occurence of "<family>" ' +
        'will be replaced with the actual family identifier (if <FAMILY> given, the identifier will be uppercased)')
# Target branch of the source repository (option)
parser.add_argument('--HAL-repo-branch', type=str, dest='hal_repo_branch', nargs=1, default=None,
    help='Either string naming target branch for all source repositories for the HAL module or a ' +
        'JSON dictionary holding branches names matched for the given family (note that JSON dictionary is ' +
        'expected to define members with keys wrapped in \"\" not \'\')')
# Target commit ID of the source repository (option)
parser.add_argument('--HAL-repo-commit', type=str, dest='hal_repo_commit', nargs=1, default=None,
    help='JSON dictionary holding branches names for the HAL module matched for the given family ' +
        '(note that JSON dictionary is expected to define members with keys wrapped in \"\" not \'\')')

# Target name of the repository directory (option)
parser.add_argument('--HAL-repo-name', type=str, dest='hal_repo_name', nargs=1, default=None,
    help='Target name of the repository directory for the Device module. Every occurence of "<family>" ' +
         'will be replaced with the actual family identifier (if <FAMILY> given, the identifier will be ' +
         'uppercased)')

# ============================================================= Update ============================================================= #

# Parse options
arguments = parser.parse_args()

# Check if there is anything to do
if len(arguments.components) == 0:
    utils.logger.info('Nothing to do')
    exit(0)

# ------------------------------------------------------------- Helpers ------------------------------------------------------------ #

def parse_common_options():

    """Parses common options"""
    
    options = []
    
    # Parse options (common)
    if arguments.repo_use_old:
        options += [ '--use-existing-repo' ]
    if arguments.repo_home is not None:
        options += [ '--repo-home', arguments.repo_home if type(arguments.repo_home) == str else arguments.repo_home[0] ]
    if arguments.repo_keep:
        options += [ '--repo-keep' ] 

    return options
    
def run_script(script_path, options, posargs):

    """Runs Python script under @p script_path with given @p options and @p posargs"""

    # Prepare command
    p = subprocess.Popen([ sys.executable, script_path, *options, *posargs ])
    # Call script
    p.communicate()

# ---------------------------------------------------------- Update CMSIS ---------------------------------------------------------- #

if 'cmsis' in arguments.components or 'all' in arguments.components:
    
    # Compute script path
    script_path = os.path.join(PROJECT_HOME, 'src/cmsis/scripts/update.py')

    posargs = []
    options = []
    
    # Parse options (common)
    options += parse_common_options()
    
    # Parse options (specific)
    if arguments.cmsis_repo_url is not None:
        options += ['--repo-url', arguments.cmsis_repo_url]
    if arguments.cmsis_repo_branch is not None:
        options += ['--repo-branch', arguments.cmsis_repo_branch]
    if arguments.cmsis_repo_commit is not None:
        options += ['--repo-commit', arguments.cmsis_repo_commit]
    if arguments.cmsis_repo_name is not None:
        options += ['--repo-name', arguments.cmsis_repo_name]

    # Parse arguments
    if arguments.cmsis_components is not None:
        posargs += arguments.cmsis_components
    
    # Run script
    run_script(script_path, options, posargs)

# ---------------------------------------------------------- Update Device --------------------------------------------------------- #

if 'device' in arguments.components or 'all' in arguments.components:
    
    # Compute script path
    script_path = os.path.join(PROJECT_HOME, 'src/device/scripts/update.py')

    posargs = []
    options = []

    # Parse options (common)
    options += parse_common_options()
    
    # Parse options (specific)
    if arguments.device_repo_url is not None:
        options += ['--repo-url', arguments.device_repo_url]
    if arguments.device_repo_branch is not None:
        options += ['--repo-branch', arguments.device_repo_branch]
    if arguments.device_repo_commit is not None:
        options += ['--repo-commit', arguments.device_repo_commit]
    if arguments.device_repo_name is not None:
        options += ['--repo-name', arguments.device_repo_name]

    # Parse arguments
    if arguments.families is not None:
        posargs += arguments.families
    
    # Run script
    run_script(script_path, options, posargs)

# ----------------------------------------------------------- Update HAL ----------------------------------------------------------- #

if 'hal' in arguments.components or 'all' in arguments.components:
    
    # Compute script path
    script_path = os.path.join(PROJECT_HOME, 'src/hal/scripts/update.py')

    posargs = []
    options = []

    # Parse options (common)
    options += parse_common_options()
    
    # Parse options (specific)
    if arguments.device_repo_url is not None:
        options += ['--repo-url', arguments.hal_repo_url]
    if arguments.device_repo_branch is not None:
        options += ['--repo-branch', arguments.hal_repo_branch]
    if arguments.device_repo_commit is not None:
        options += ['--repo-commit', arguments.hal_repo_commit]
    if arguments.device_repo_name is not None:
        options += ['--repo-name', arguments.hal_repo_name]

    # Parse arguments
    if arguments.families is not None:
        posargs += arguments.families
    
    # Run script
    run_script(script_path, options, posargs)

# ================================================================================================================================== #
