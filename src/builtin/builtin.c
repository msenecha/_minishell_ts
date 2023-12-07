
#include "../../includes/minishell.h"

int	exec_builtin(char **args, t_env *env)
{
	(void)env;
	while(*args != NULL)
		printf("args[0] = %s\n", *args++);
	return (0);
}

int	is_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	if (strcmp(command, "cd") == 0)
		return (1);
	if (strcmp(command, "pwd") == 0)
		return (1);
	if (strcmp(command, "env") == 0)
		return (1);
	if (strcmp(command, "export") == 0)
		return (1);
	if (strcmp(command, "unset") == 0)
		return (1);
	return (0);
}
