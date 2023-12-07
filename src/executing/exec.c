
#include "../../includes/minishell.h"

int run_simple_command(char **args, t_env *env)
{
	char **env_tab;
	int status;
	pid_t pid;

	if (is_builtin(args[0]))
		return (exec_builtin(args, env));
	else
	{
		pid = fork();
		if (pid == 0)
		{
			env_tab = env_to_str(env);
			if (execve(args[0], args, env_tab) == -1)
			{
				perror("execve");
				return(1);
			}
		}
		else if (pid > 0)
		{
			waitpid(-1, &status, 0);
			if (WEXITSTATUS(status) == 1)
				return (1);
		}
	}
	return (0);
}

int	setup_pipe(char **cmd1, char **cmd2, t_env *env, int out)
{
	int		fd[2];
	pid_t	pid;
	//pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return(1);
	}
	if ((pid = fork()) == -1)
	{
		perror("fork");
		return(1);
	}
	if (pid == 0)
	{
		//close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (run_simple_command(cmd1, env))
			return(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 1)
			printf("erreur premiere commaande\n");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(out, STDOUT_FILENO);
		close(out);
		//pid2 = fork();
		//if(pid2 == 0)
		//{
			if (run_simple_command(cmd2, env))
				return(1);
		//}
		/*else
		{
			waitpid(-1, &status, 0);
			if (WEXITSTATUS(status) == 1)
				return (1);
		}*/
	}
	return (0);
}

void execute_command(t_parser *data, t_env *env)
{
	t_list   *full_cmd;
	char	**cmd1;
	char	**cmd2;
	int		original_in_fd;
	int		original_out_fd;

	original_in_fd = dup(STDIN_FILENO);
	original_out_fd = dup(STDOUT_FILENO);
	full_cmd = data->command_list->head;
	while (full_cmd)
	{
		cmd1 = build_exec_line(data->command_list->head, env);
		if (check_for_pipe(full_cmd))
		{
			cmd2 = build_exec_line(data->command_list->head->next, env);
			if (setup_pipe(cmd1, cmd2, env, original_out_fd))
				break;
			full_cmd = full_cmd->next->next;
		}
		else
		{
			if (run_simple_command(cmd1, env))
				break;
			full_cmd = full_cmd->next;
		}
	}
	dup2(original_in_fd, STDIN_FILENO);
	dup2(original_out_fd, STDOUT_FILENO);
	close(original_in_fd);
	close(original_out_fd);
}
