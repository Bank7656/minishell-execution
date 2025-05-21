#ifndef EXECUTE_H
# define EXECUTE_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define PERMISSION_DENIED 13
# define COMMAND_NOT_FOUND 127
# define COMMAND_CANNOT_EXECUTE 126
# define TEMP_FILE "temp.txt"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pipex
{
	int		is_here_doc;
	int		process_count;
	int		pfd[2];
	int		prev_pfd;
	char	*infile;
	char	*outfile;
	char	*delimeter;
	char	**cmds_arg;
	char	*command_path;
	char	**envp;
	char	**env_path;
	pid_t	*parent_pid;
}	t_pipex;

#endif
