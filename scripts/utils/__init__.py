# ====================================================================================================================================
# @file       __init__.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 2nd August 2022 7:45:20 pm
# @modified   Tuesday, 2nd August 2022 8:25:39 pm
# @project    stm-utils
# @brief      Auxiliary Python utilities used along the project
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Unix, Windows
   :synopsis: Auxiliary Python utilities used along the project

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""


# ============================================================ Imports ============================================================= #

import os
import glob
import coloredlogs
import logging
import importlib

# =========================================================== Submodules =========================================================== #

# Predefine models list
__all__ = []

# Import all submodules
import automodinit
automodinit.automodinit(__name__, __file__, globals())
del automodinit

# ============================================================= Helpers ============================================================ #

# Create logger
logger = logging.getLogger('cmsis-update')
# Set log level
coloredlogs.install(level='DEBUG', logger=logger)

# ================================================================================================================================== #
