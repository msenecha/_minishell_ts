
#include "minishell.h"

char	*path_join(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	tmp = NULL;
	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, command) == 0)
		{
			path = path_join(bin, item->d_name);
			break ;
		}
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

char	*search_in_bin(char *args, t_env *env)
{
	int		i;
	char	**bin;
	char	*path;

	path = NULL;
	while (env && env->key && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (args);
	bin = ft_split(env->value, ':');
	i = 0;
	while (args && bin[i] && path == NULL)
		path = check_dir(bin[i++], args);
	my_free(bin);
	if (path != NULL)
	{
		free(args);
		return (path);
	}
	return (args);
}
