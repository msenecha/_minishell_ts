
#include "../../includes/minishell.h"

void	run_simple_command(char **args, t_env *env)
{
	char	**env_tab;
	int		status;

	//if (is_builtin(args[0]))
	//	exec_builtin(args, env);
	//else
	//{
		if (fork() == 0)
		{
			env_tab = env_to_str(env);
			execve(args[0], args, env_tab);
		}
		else
			waitpid(-1, &status, 0);
	//}
}

int check_for_pipe(t_list *sub_list)
{
	t_node  *current;

	current = sub_list->head;
	while(current)
	{
		if (current->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

char    **build_exec_line(t_list *sub_list, t_env *env)
{
	t_node  *node;
	char    **argv;
	int		i;

	node = sub_list->head;
	argv = malloc((ft_lstsize(node) + 1) * sizeof(char *));
	if (node->type == COMMAND)
		argv[0] = search_in_bin(node->value, env);
	i = 1;
	node = node->next;
	while (node && node->type != PIPE)
	{
		if (node->type == ARGUMENT || node->type == ENV_VAR)
			argv[i] = expand_arg(node->value, env);
		else if (node->type == LEFT_REDIRECT || node->type == REDIRECTION || node->type == DOUBLE_REDIRECT)
			setup_redir(node->type, node->next->value);
		i++;
		node = node->next;
	}
	argv[i] = NULL;
	return (argv);
}

void execute_command(t_parser *data, t_env *env)
{
	t_list   *full_cmd;
	char	**cmd1;
	char	**cmd2;
	(void)env;

	full_cmd = data->command_list->head;
	while (full_cmd)
	{
		cmd1 = build_exec_line(data->command_list->head, env);
		printf("cmd1[1] = %s\n", cmd1[1]);
		if (check_for_pipe(full_cmd))
		{
			//setup_pipe(data, env);
			cmd2 = build_exec_line(data->command_list->head->next, env);
			printf("cmd2[0] = %s\n", cmd2[0]);
			//run_complex_command(cmd1, cmd2, env);
			full_cmd = full_cmd->next->next;
		}
		else
		{
			run_simple_command(cmd1, env);
			full_cmd = full_cmd->next;
		}
	}
}

/*
	char    *built;


built = strdup(cmd->head->value);
		if (is_builtin(built))
		{
			free(built);
			//execute_builtin(data, env);
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
*/