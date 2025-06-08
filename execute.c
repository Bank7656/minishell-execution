#include "execute.h"

int          is_builtin(char *func_name);
void  redirection(t_exec *data);
void  create_temp_file(t_exec *data);
static void  execution(t_exec *data, char **envp);
t_exec  *get_exec_dummy(char **envp);

int main(int argc, char *argv[], char *envp[])
{ 
  t_exec  *data;

  printf("[Execution start]\n");
  data = get_exec_dummy(envp);
  execution(data, envp);
  printf("[Execution end]\n");
  return 0;
}

static void  execution(t_exec *data, char  **envp)
{
  int     i;
  int     status;
  pid_t   pid; 

  /* This have to have loop for many cmds */
  if (data -> is_heredoc)
    create_temp_file(data);
  pid = fork();
  if (pid == 0)
  {
    redirection(data);
    if (is_builtin(data->cmds_arg[0]))
    {
      /* For doing builtin function later */
      printf("This is a builtin function\n");
      exit(EXIT_SUCCESS);
    }
    printf("This is not a builtin function\n");
    if (execve(data->command_path, data->cmds_arg, data -> envp) == -1)
    {
      printf("Execution Failed\n");
      exit(EXIT_FAILURE);
    }
  }
  wait(&status);
}

/* This function create a simple case for execution */
t_exec  *get_exec_dummy(char **envp)
{ // Path to the binary to execute
  // char *binary_path = "/bin/ls";
  char *binary_path = "/bin/cat";

  // Arguments for the binary (argv must be NULL-terminated)
  //char *args[] = { "ls", "-l", "/tmp", NULL };
  char *args[] = { "cat", "-e", NULL };

  // Environment variables (envp must be NULL-terminated)
  //char *env[] = { "HOME=/home/user", "PATH=/bin:/usr/bin", NULL };

  t_exec *data; 

  data = (t_exec *)malloc(sizeof(t_exec));
  if (data == NULL)
    exit(EXIT_FAILURE);
  data -> command_path = ft_strdup(binary_path);
  data -> cmds_arg = (char **)malloc(sizeof(char *) * sizeof(args)/sizeof(args[0]));
  for (int i = 0; i < sizeof(args)/sizeof(args[0]); i++)
    data -> cmds_arg[i] = args[i];
  data -> envp = envp;
  data -> is_pipe = false;
  data -> is_infile = false;
  data -> infile = ft_strdup("hello.txt");
  // data -> is_heredoc = false;
  data -> is_heredoc = true;
  data -> end_of_file = ft_strdup("EOF");
  return (data);
}

void  create_temp_file(t_exec *data)
{
    int   temp_fd;
    char  *line;

    temp_fd = open(TEMP_FILE, O_CREAT | O_WRONLY, 0644);  
    if (!temp_fd)
      exit(EXIT_FAILURE);
    while (true)
    {
      ft_putstr_fd("> ", STDOUT_FILENO);
      line = get_next_line(STDIN_FILENO);
      if (!line)
        exit(EXIT_FAILURE);
      if (ft_strncmp(line, data -> end_of_file, ft_strlen(line) - 1) == 0)
        break;
      ft_putstr_fd(line, temp_fd);
      free(line);
    }
    if (dup2(temp_fd, STDIN_FILENO) == -1)
      exit(EXIT_FAILURE);
    close(temp_fd);
    return ;
}



