#include "execute.h"
#include "libft/libft.h"


int     is_builtin(char *func_name);
void  execution(t_exec *data, char **envp);
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

void  execution(t_exec *data, char  **envp)
{
  int     status;
  pid_t   pid; 

  pid = fork();
  if (pid == 0)
  {
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
  char *binary_path = "/bin/ls";

  // Arguments for the binary (argv must be NULL-terminated)
  char *args[] = { "ls", "-l", "/tmp", NULL };

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
  return (data);
}


int     is_builtin(char *func_name)
{
  if (ft_strncmp(func_name, "echo", -1) == 0) 
    return (1);
  if (ft_strncmp(func_name, "cd", -1) == 0) 
    return (1);
  if (ft_strncmp(func_name, "pwd", -1) == 0) 
    return (1);
  if (ft_strncmp(func_name, "export", -1) == 0) 
    return (1);
  if (ft_strncmp(func_name, "unset", -1) == 0) 
    return (1);
  if (ft_strncmp(func_name, "env", -1) == 0) 
    return (1);
  if (ft_strncmp(func_name, "exit", -1) == 0) 
    return (1);
  return (0);
}

