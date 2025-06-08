#include "execute.h"

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
