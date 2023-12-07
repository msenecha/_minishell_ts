
#include "../../includes/minishell.h"

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
	if (node->type == COMMAND && is_builtin(node->value) == 0)
		argv[0] = search_in_bin(node->value, env);
	else if (is_builtin(node->value) == 1)
		argv[0] = ft_strdup(node->value);
	i = 1;
	node = node->next;
	while (node && node->type != PIPE)
	{
		if (node->type == ARGUMENT || node->type == ENV_VAR || node->value[0] == '-')
			argv[i] = expand_arg(node->value, env);
		else if (node->type == LEFT_REDIRECT || node->type == REDIRECTION
			|| node->type == DOUBLE_REDIRECT || ft_strcmp(node->value, "<<") == 0)
		{
			setup_redir(node->type, node->next->value);
			break;
		}
		i++;
		node = node->next;
	}
	argv[i] = NULL;
	return (argv);
}
