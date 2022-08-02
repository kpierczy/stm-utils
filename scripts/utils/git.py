# ====================================================================================================================================
# @file       git.py
# @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
# @date       Tuesday, 2nd August 2022 8:04:00 pm
# @modified   Tuesday, 2nd August 2022 9:06:28 pm
# @project    stm-utils
# @brief      GIT utilities
# 
# 
# @copyright Krzysztof Pierczyk © 2022
# ====================================================================================================================================

# ============================================================== Doc =============================================================== #

""" 

.. module:: 
   :platform: Unix, Windows
   :synopsis: GIT utilities

.. moduleauthor:: Krzysztof Pierczyk <krzysztof.pierczyk@gmail.com>

"""

# ============================================================ Imports ============================================================= #

import os
import shutil
import git
import rich.progress
import rich.console

# ============================================================= Helpers ============================================================ #

class GitRemoteProgress(git.RemoteProgress):

    """Custom progess bar drawer"""

    # Stages
    OP_CODES = [
        "BEGIN",
        "CHECKING_OUT",
        "COMPRESSING",
        "COUNTING",
        "END",
        "FINDING_SOURCES",
        "RECEIVING",
        "RESOLVING",
        "WRITING",
    ]
    
    # Stages map
    OP_CODE_MAP = {
        getattr(git.RemoteProgress, _op_code): _op_code for _op_code in OP_CODES
    }


    def __init__(self) -> None:

        """Initializes the drawer"""

        super().__init__()
        
        self.progressbar = rich.progress.Progress(
            rich.progress.SpinnerColumn(),
            rich.progress.TextColumn("[rich.progress.description]{task.description}"),
            rich.progress.BarColumn(),
            rich.progress.TextColumn("[rich.progress.percentage]{task.percentage:>3.0f}%"),
            "eta",
            rich.progress.TimeRemainingColumn(),
            rich.progress.TextColumn("{task.fields[message]}"),
            console=rich.console.Console(),
            transient=False,
        )
        
        self.progressbar.start()
        self.active_task = None


    def __del__(self) -> None:
        self.progressbar.stop()


    @classmethod
    def get_curr_op(cls, op_code: int) -> str:

        """Get OP name from OP code."""
        
        # Remove BEGIN- and END-flag and get op name
        op_code_masked = op_code & cls.OP_MASK
        return cls.OP_CODE_MAP.get(op_code_masked, "?").title()


    def update(
        self,
        op_code: int,
        cur_count: str | float,
        max_count: str | float | None = None,
        message: str | None = "",
    ) -> None:

        # Start new bar on each BEGIN-flag
        if op_code & self.BEGIN:
            self.curr_op = self.get_curr_op(op_code)
            self.active_task = self.progressbar.add_task(
                description=self.curr_op,
                total=max_count,
                message=message,
            )

        self.progressbar.update(
            task_id=self.active_task,
            completed=cur_count,
            message=message,
        )

        # End progress monitoring on each END-flag
        if op_code & self.END:
            self.progressbar.update(
                task_id=self.active_task,
                message=f"[bright_black]{message}",
            )


# ============================================================ Utilities =========================================================== #

def download_repo(url, directory, cleanup=False):

    """Downloads GIT repository from @p url into @p directory. Clears @p directory if @p cleanup is @c True"""

    # Remove previous download
    if cleanup:
        shutil.rmtree(directory, ignore_errors=True)

    # Clone repository
    if not os.path.exists(directory):
        git.Repo.clone_from(url, directory, progress=GitRemoteProgress())

# ================================================================================================================================== #
