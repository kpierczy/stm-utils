# ====================================================================================================================================
# @file       parse_hal_modules.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Friday, 16th July 2021 10:17:57 am
# @modified   Wednesday, 3rd August 2022 12:07:21 am
# @project    stm-utils
# @brief      Parses '*_hal_conf_template.h' from the 'config/templates' folder looking for given pattern definitions. Prints all
#             lines found (uniquelly filtered) to the result file whose content can be in turn copied to the main HAL config header.
# @details    This script may be used e.g. to generate list of all HAL modules for the given MCU family
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

from pathlib import Path
import re
import os

# ========================================================== Configuration ========================================================= #

# Name of the result file (if empty or None, result will be written to std out)
OUTPUT_FILE = ''
# Establish regex pattern to be searched
pattern = re.compile('#define  USE_HAL.*REGISTER_CALLBACKS')
# Suffix to be added to the matching line
suffix = ' 0U'

# ============================================================== Paths ============================================================= #

# Calculate package home
PACKAGE_HOME = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')

# Calculate path to the 'config' directory
CONFIG_HOME = os.path.join(PACKAGE_HOME, 'config/templates')

# =========================================================== List files =========================================================== #

# Get path to the config folder
config_home_path = Path(CONFIG_HOME)

# Gather all configuration file templates into list
config_files = list()
for path in config_home_path.iterdir():
    if path.name.endswith('_hal_conf_template.h'):
        config_files.append(Path(os.path.join(CONFIG_HOME, path)))

# ======================================================== Parse HAL modules ======================================================= #

# Initializae list of unique modules found
modules = list()

# Iterate over all tempaltes
for f in config_files:
    # Iterate over file's lines
    for i, line in enumerate(open(f)):
        # Strip a line
        line = line.strip()
        # Look for pattern in lnie
        for match in re.finditer(pattern, line):
            # If module's not noticed yet, add it to list
            if not match[0] in modules:
                modules.append(match[0])

# Sort modules that have been found
modules.sort()

# Write list of modules to the output file
if OUTPUT_FILE is not None and OUTPUT_FILE != '':
    with open(OUTPUT_FILE, 'w') as file :
        for module in modules:
            file.write(module + suffix + '\n')
# Otherwise, write it to stdout
else:
    for module in modules:
        print(module + suffix)
