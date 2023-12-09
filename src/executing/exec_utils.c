
#include "../../includes/minishell.h"

// Cree un fichier temporaire qui va recuperer le contenu de readline
// Le prompte reste ouvert tant qu'on trouve pas le delimiteur, ex : EOF, FIN ..
// Puis on configure pour que la fonction lise a partir de ce fichier au lieu de l'entree standard
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

// Simple config pour que la fonction lise a partir du fichier passe en argument
// On ouvre le fichier grace au path ex : "./src/builtin/cd.c"
// On utilise le file descriptor genere par open comme source pour l'entree standard
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


int	setup_redir(int type, char *path)
{
	int	out_fd;
	int	flags;

	if (type == LEFT_REDIRECT)
		set_input_redir(path);
	//else if (type == HEREDOC)
		//set_heredoc(path);
	else if (type == REDIRECTION || type == DOUBLE_REDIRECT)
	{
		flags = O_WRONLY | O_CREAT; // flags pour creer et ecrire dans un fichier
		if (type == DOUBLE_REDIRECT)
			flags |= O_APPEND; // flag pour ecrire dans un fichier sans l'ecraser
		out_fd = open(path, flags, 0666);
		if (out_fd < 0)
			return (1);
		dup2(out_fd, STDOUT_FILENO); // le fichier devient la sortie standard
		close(out_fd);
	}
	return (0);
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
		argv[0] = search_in_bin(node->value, env); // remplace l'executable par son chemin d'acces complet : 'ls' devient 'usr/bin/ls'
	else if (is_builtin(node->value) == 1)
		argv[0] = ft_strdup(node->value);
	i = 1;
	node = node->next;
	while (node && node->type != PIPE)
	{
		if (node->type == ARGUMENT || node->type == ENV_VAR || node->value[0] == '-') // rajouter ENUM Option au parsing
			argv[i] = expand_arg(node->value, env); // expansion des arguments : $USER devient tscasso
		else if (node->type == LEFT_REDIRECT || node->type == REDIRECTION
			|| node->type == DOUBLE_REDIRECT || ft_strcmp(node->value, "<<") == 0) // rajouter le type heredoc enum
		{
			if (setup_redir(node->type, node->next->value)) // on verifie le type de la redirection et on configure les entrees sorties
				return (perror("erreur redirection"), NULL);
			break;
		}
		i++;
		node = node->next;
	}
	argv[i] = NULL;
	return (argv);
}
