#include "execute.h"

static void redirect_input(t_exec *data);
static void redirect_output(void);

void  redirection(t_exec *data)
{
    int pfd[2];

    if (pipe(pfd) == -1) 
      exit(EXIT_FAILURE);
    redirect_input(data);
    redirect_output();
    return ;
}

static void redirect_input(t_exec *data)
{
  int infile_fd;

  if (data -> is_infile)
    infile_fd = open(data -> infile, O_RDONLY);
  else if (data -> is_heredoc)
    infile_fd = open(TEMP_FILE, O_RDONLY);
  if (!infile_fd)
    exit(EXIT_FAILURE);
  if (dup2(infile_fd, STDIN_FILENO) == -1)
    exit(EXIT_FAILURE);
  
  return ;
}

static void redirect_output(void)
{
  return ;
}

