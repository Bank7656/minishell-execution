#include "execute.h"


void  execute(t_pipex *data, char *envp[]);
void  get_dummy_data(t_pipex *data);

int main(int argc, char *argv[], char *envp[])
{ 
  t_pipex data;
  get_dummy_data(&data);

  execute(&data, envp);
  return 0;
}

void  execute(t_pipex *data, char *envp[])
{
  
  execve(data->command_path, data->cmds_arg, envp);
}

void  get_dummy_data(t_pipex *data)
{
  data->command_path = malloc(sizeof(char *));
  data->cmds_arg = malloc(sizeof(char *) * 3);
  data->command_path = "/bin/ls";
  data->cmds_arg[0] = "ls";
  data->cmds_arg[1] = "-la";
  data->cmds_arg[2] = NULL;
}
