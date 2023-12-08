
#include "../../includes/minishell.h"

int run_simple_command(char **args, t_env *env, int mode, t_parser *data)
{
	char **env_tab;
	int status;
	pid_t pid;

	if (is_builtin(args[0]))
		return (exec_builtin(args, env));
	else
	{
		if (mode == 1)
			pid = fork();
		if (pid == 0 || mode == 0)
		{
			env_tab = env_to_str(env);
			if (execve(args[0], args, env_tab) == -1)
			{
				perror("execve");
				return(1);
			}
			else
			{
				free_command(data->command_list);
				_exit(0);
			}
		}
		else if (pid > 0 && mode == 1)
		{
			waitpid(-1, &status, 0);
			if (WEXITSTATUS(status) == 1)
				return (1);
		}
	}
	return (0);
}

int	setup_pipe(t_parser *data, t_env *env, int out)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	**cmd1;
	char	**cmd2;

	if (pipe(fd) == -1 || ((pid = fork()) == -1))
	{
		perror("error fatal");
		return(1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if ((cmd1 = build_exec_line(data->command_list->head, env)) == NULL)
			return (1);
		if (run_simple_command(cmd1, env, 0, data))
			return(1);
		else
		{
			free_command(data->command_list);
			_exit(0);
		}
	}
	else
	{
		waitpid(-1, &status, WNOHANG);
		if (WEXITSTATUS(status) == 1)
			printf("erreur premiere commande\n");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(out, STDOUT_FILENO);
		close(out);
		if ((cmd2 = build_exec_line(data->command_list->head->next, env)) == NULL)
			return (1);
		if (run_simple_command(cmd2, env, 1, data))
			return(1);
	}
	return (0);
}

void execute_command(t_parser *data, t_env *env)
{
	t_list   *full_cmd;
	char	**cmd1;
	int		original_in_fd;
	int		original_out_fd;

	original_in_fd = dup(STDIN_FILENO);
	original_out_fd = dup(STDOUT_FILENO);
	full_cmd = data->command_list->head;
	while (full_cmd)
	{
		if (check_for_pipe(full_cmd))
		{
			if (setup_pipe(data, env, original_out_fd))
				break;
			full_cmd = full_cmd->next->next;
		}
		else
		{
			if ((cmd1 = build_exec_line(data->command_list->head, env)) == NULL)
				break;
			if (run_simple_command(cmd1, env, 1, data))
				break;
			full_cmd = full_cmd->next;
		}
	}
	dup2(original_in_fd, STDIN_FILENO);
	dup2(original_out_fd, STDOUT_FILENO);
	close(original_in_fd);
	close(original_out_fd);
}
