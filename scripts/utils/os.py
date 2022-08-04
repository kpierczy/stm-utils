# ====================================================================================================================================
# @file       os.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 2nd August 2022 7:44:57 pm
# @modified   Thursday, 4th August 2022 11:25:02 am
# @project    stm-utils
# @brief      OS utilities
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Unix, Windows
   :synopsis: OS utilities

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

import os
import stat
import pathlib
import shutil
import glob

# ============================================================= Helpers ============================================================ #

def remove(file):

    """Removes @p file if it exists"""

    if os.path.isfile(file):
        os.remove(file)
    

def make_dir(dir):

    """Makes @p dir if it does not exist (with required parents"""

    os.makedirs(dir, exist_ok=True)
    

def remove_dir(dir):

    """Removes (potentiallt non-empty) @p dir if it exists
    
    Note
    ----
    Manual file-by-file implementation si required to properly handle routine on Windos
    """
    
    # Check if non-file entity given
    if os.path.isfile(dir):
        raise Exception('Given entity is not a directory!')
    # If does not exist, return
    if not os.path.exists(dir):
        return

    # Remove content
    for root, dirs, files in os.walk(dir, topdown=False):
        for name in files:
            filename = os.path.join(root, name)
            os.chmod(filename, stat.S_IWUSR)
            os.remove(filename)
        for name in dirs:
            os.rmdir(os.path.join(root, name))
            
    # Remove dir
    os.rmdir(dir)    


def refresh_directory(dir):

    """Deletes @p dir with all of it's content (if exist) and creates it"""

    remove_dir(dir)
    os.makedirs(dir, exist_ok=True)


def copy(file, dst, cleanup=False):
    
    """Copies @p file into @p dst"""
    
    if cleanup:
        remove_dir(dst)

    # Create dst directory as needed
    if dst.endswith('/') and not os.path.isdir(dst):
        os.makedirs(dst, exist_ok=True)

    shutil.copy(file, dst)


def copy_dir(src, dst, cleanup=False):
    
    """Copies @p src into @p dst"""
    
    if cleanup:
        remove_dir(dst)

    # Create dst directory as needed
    if dst.endswith('/') and not os.path.isdir(dst):
        os.makedirs(dst, exist_ok=True)

    shutil.copytree(src, dst)


def move(src, dst):

    """Moves @p src into @p dst"""

    shutil.move(src, dst)
    

def copy_glob_content(pattern, dst, cleanup=False):
    
    """Copies all files matching the given @p pattern into @p dst"""
    
    if cleanup:
        refresh_directory(dst)
    
    for file in glob.glob(pattern):
        shutil.copy(file, dst)


def remove_glob_content(pattern):
    
    """Removes all files matching @p pattern"""
    
    for file in glob.glob(pattern):
        os.remove(file)


def find_and_remove_except(directory, file_s : str or list):

    """Removes all files in the @p directory except @p file_s"""

    # Iterate files in the directory
    for root, dirs, files in os.walk(directory):
        for f in files:

            f_path = pathlib.Path(os.path.join(root, f))

            # Match file
            if file_s is str:
                if f_path.name != file_s:
                    os.remove(f_path)
            # Match file(s)
            else:
                if f_path.name not in file_s:
                    os.remove(f_path)

# ================================================================================================================================== #
