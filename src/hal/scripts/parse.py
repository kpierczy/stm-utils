# ====================================================================================================================================
# @file       parse.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Friday, 16th July 2021 10:17:57 am
# @modified   Friday, 16th July 2021 10:17:57 am
# @project    stm-utils
# @brief      Parses '*_hal_conf_template.h' from the config folder looking for given pattern definitions. Prints all lines found (uniquelly
#             filtered) to the result file whose content can be in turn copied to the main HAL config header.
#    
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

from pathlib import Path
import re
import os

# ========================================================== Configuration ========================================================= #

# Name of the result file
OUTPUT_FILE='callback_list.h'
# Establish regex pattern to be searched
#pattern = re.compile('#define HAL.*MODULE_ENABLED')
pattern = re.compile('#define  USE_HAL.*REGISTER_CALLBACKS')
# Suffix to be added to the matching line
suffix = ' 0U'

# ============================================================== Code ============================================================== #

# Check whether PROJECT_HOME is defined
if os.environ['PROJECT_HOME'] == '':
    print("[ERR] 'PROJECT_HOME' is not defined!")
    exit(1)

# Get path to the current folder
p = Path(os.path.join(os.environ['PROJECT_HOME'], 'extern/platform/hal/config'))

# Gather all configuration file templates into list
conf_files = list()
for path in p.iterdir():
    if path.name.endswith('_hal_conf_template.h'):
        conf_files.append(path)

# Initializae list of unique modules found
modules = list()

# Iterate over all tempaltes
for conf in conf_files:
    # Iterate over file's lnies
    for i, line in enumerate(open(conf.name)):
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
with open(OUTPUT_FILE, 'w') as file :
    for module in modules:
        file.write(module + suffix + '\n')
