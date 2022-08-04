# ====================================================================================================================================
# @file       arguments.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Wednesday, 3rd August 2022 10:05:17 pm
# @modified   Thursday, 4th August 2022 11:36:52 am
# @project    stm-utils
# @brief      Arguments parsing utilities
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Unix, Windows
   :synopsis: Arguments parsing utilities

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

import utils
import json

# ============================================================ Utilities =========================================================== #

def download_repo(
    repo_url_scheme,
    repo_root,
    family,
    branch_opt,
    commit_opt,
    cleanup
):

    """Auxiliary function downloading target repo for the given family
    
    Parameters
    ----------
    repo_url_scheme: str
        scheme of the target repository URL; all occerences of <family> will be replaced with @p family 
        while all occurences of <FAMILY> will be replaced with upppercased @p family 
    repo_root: str
        target root directory of the repo
    family: str
        target MCU family name
    branch_opt: str
        parsed (argparse) option storing either None, or array with a single string representing
        target branch(es) for repository;
          
            - if None the repository will be downloaded with the default branch
            - if JSON convertible string, the branch will be choosen either as value
              of the @p family key (if exists) or default branch (if not)
            - otherwise name of the target branch
    commit_opt: str
        parsed (argparse) option storing either None, or array with a single string representing
        target commit(s) for repository;
          
            - if None the repository will be downloaded with the default HEAD
            - if JSON convertible string, the commit will be choosen either as value
              of the @p family key (if exists) or default HEAD (if not)
            - otherwise name of the target commit
    cleanup: bool
        if @c true the repository will be removed before downloading
    """
    
    # Prepare URL of the downloaded repository
    repo_url = repo_url_scheme.replace('<family>', family).replace('<FAMILY>', family.capitalize())
    
    utils.logger.info(f' - Downloading repository family...')

    # Auxiliary function parsing option string as either JSON or string
    def parse_json_or_str(opt):

        # If string is not None
        if opt is not None:

            # Try to parse branch as JSON
            try:
                mapping = json.loads(opt[0])
                return mapping[family] if family in mapping else None
            # On failure, treat it as a raw string
            except:
                return opt[0]

        # Else, return None
        else:
            return None
    
    # Parse branch
    branch = parse_json_or_str(branch_opt)
    # Parse commit
    commit = parse_json_or_str(commit_opt)

    # Clone repository
    utils.git.download_repo(
        url=repo_url,
        directory=repo_root,
        cleanup=cleanup,
        branch=branch,
        commit=commit
    )

# ============================================================= Helpers ============================================================ #

def define_common_arguments(parser):

    """Defines arguments common for all update scripts in the @p parser object"""

    # Whether to use existing repository (option)
    parser.add_argument('-e', '--use-existing-repo', dest='repo_use_old', action='store_true', default=False,
        help='If given, the old repository present at the target repo will not be redownloaded')
        
    # Home directory for the downloaded repo (option)
    parser.add_argument('-o', '--repo-home', type=str, dest='repo_home', nargs=1, default='.',
        help='Home directory for the downloaded repo(s)')
    # Target name of the repository directory (option)
    parser.add_argument('-k', '--repo-keep', dest='repo_keep', action='store_true', default=False,
        help='If given, downloaded repository(ies) will NOT be removed')


def define_common_family_dependenc_arguments(
    parser,
    default_url_scheme,
    default_repo_name
):

    """Defines arguments common for update scripts that perform MCU-family-specific resource updates"""

    import utils

    # Families to be updated (argument)
    parser.add_argument('families', metavar='FAMILY', type=str, nargs='+', choices=[ [], 'all', *utils.config.SUPPORTED_FAMILIES ],
        help='List of target families for which device sources should be updated')

    # Target repository URL scheme (option)
    parser.add_argument('-r', '--repo-url-scheme', type=str, dest='repo_url', nargs=1, default=default_url_scheme,
        help='URL scheme of the target git repository. Every occurence of "<family>" will be replaced with the ' +
            'actual family identifier (if <FAMILY> given, the identifier will be uppercased)')
    # Target branch of the source repository (option)
    parser.add_argument('-b', '--repo-branch', type=str, dest='repo_branch', nargs=1, default=None,
        help='Either string naming target branch for all source repositories or a JSON dictionary holding '  +
            'branches names matched for the given family (note that JSON dictionary is expected to define ' +
            'members with keys wrapped in \"\" not \'\')')
    # Target commit ID of the source repository (option)
    parser.add_argument('-i', '--repo-commit', type=str, dest='repo_commit', nargs=1, default=None,
        help='JSON dictionary holding branches names matched for the given family (note that JSON dictionary ' +
            'is expected to define members with keys wrapped in \"\" not \'\')')

    # Target name of the repository directory (option)
    parser.add_argument('-n', '--repo-name', type=str, dest='repo_name', nargs=1, default=default_repo_name,
        help='Target name of the repository directory. Every occurence of "<family>" will be replaced with the ' +
            'actual family identifier (if <FAMILY> given, the identifier will be uppercased)')
            
# ================================================================================================================================== #
