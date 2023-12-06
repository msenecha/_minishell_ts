
#include "../../includes/minishell.h"
/*
int	ft_execve(t_cmd *cmd, t_gen *gen)
{
	char	*exec_args[MAX_ARGS + 2];
	int		i;
	char	**env;

	exec_args[0] = cmd->cmd;
	i = 0;
	while (i <= cmd->nb_args)
	{
		exec_args[i + 1] = cmd->args[i].arg_value;
		i++;
	}
	exec_args[cmd->nb_args + 1] = NULL;
	env = env_to_str(gen);
	if (execve(cmd->cmd, exec_args, env) == -1)
		return (1);
	return (0);
}
*/

int	set_heredoc(char *delim)
{
	int		in_fd;
	char	*buffer;

	in_fd = open("./heredoc_tmp.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (in_fd < 0)
		return (-1);
	while (1)
	{
		buffer = readline("> ");
		if (ft_strcmp(buffer, delim) == 0)
			break ;
		else
		{
			write(in_fd, buffer, ft_strlen(buffer));
			write(in_fd, "\n", 1);
			free(buffer);
		}
	}
	free(buffer);
	close(in_fd);
	in_fd = open("./heredoc_tmp.txt", O_RDONLY);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	return (0);
}

int	set_input_redir(char *path)
{
	int	in_fd;

	in_fd = open(path, O_RDONLY);
	if (in_fd < 0)
		return (-1);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	return (0);
}

void	setup_redir(int type, char *path)
{
	int	out_fd;
	int	flags;

	if (type == LEFT_REDIRECT)
		set_input_redir(path);
	//else if (type == HEREDOC)
		//set_heredoc(path);
	else if (type == REDIRECTION || type == DOUBLE_REDIRECT)
	{
		flags = O_WRONLY | O_CREAT;
		if (type == DOUBLE_REDIRECT)
			flags |= O_APPEND;
		out_fd = open(path, flags, 0666);
		//if (out_fd < 0)
		//	return (-1);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	//return (0);
}
/*
void	setup_pipe(t_pipe *pipe, int a, int b, char mode)
{
	if (mode == 'o')
	{
		close(pipe->pipe_fd[a]);
		dup2(pipe->pipe_fd[b], STDOUT_FILENO);
		close(pipe->pipe_fd[b]);
	}
	else if (mode == 'i')
	{
		close(pipe->pipe_fd[a]);
		dup2(pipe->pipe_fd[b], STDIN_FILENO);
		close(pipe->pipe_fd[b]);
	}
	else if (mode == 'c')
	{
		close(pipe->pipe_fd[a]);
		close(pipe->pipe_fd[b]);
	}
}
*/
