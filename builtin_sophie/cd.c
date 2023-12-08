/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:41:46 by svidal            #+#    #+#             */
/*   Updated: 2023/11/22 15:50:48 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_recup_par_dir(char *str, t_dir *dir)
{
	char	*last_slash;
	size_t	par_len;

	if (!str)
		return (NULL);
	last_slash = ft_strrchr(str, '/');
	par_len = last_slash - str;
	dir->par_dir = (char *)malloc(par_len + 1);
	ft_strlcpy(dir->par_dir, str, par_len + 1);
	return (dir->par_dir);
}

int	ft_cd(t_args *new_dir, t_dir *dir, t_gen *gen)
{
	char	*old_pwd;

	if (!new_dir[0].arg_value || new_dir[0].arg_value[0] == '\0')
		return (printf("missing argument\n"), 1);
	old_pwd = ft_strdup(dir->cur_dir);
	if (ft_strcmp(new_dir[0].arg_value, "..") == 0)
	{
		free(dir->par_dir);
		dir->par_dir = ft_recup_par_dir(dir->cur_dir, dir);
		if (dir->par_dir != NULL)
			chdir(dir->par_dir);
	}
	else
	{
		free(dir->par_dir);
		dir->par_dir = ft_strdup(dir->cur_dir);
		chdir(new_dir[0].arg_value);
	}
	dir->cur_dir = getcwd(dir->buff, PATH_MAX);
	ft_update_env_var("OLDPWD", old_pwd, gen);
	ft_update_env_var("PWD", dir->cur_dir, gen);
	free(old_pwd);
	return (0);
}
