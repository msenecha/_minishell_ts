/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:49:49 by msenecha          #+#    #+#             */
/*   Updated: 2023/11/22 11:51:02 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_outer_quotes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_args)
	{
		if (cmd->args[i].arg_value && cmd->args[i].arg_value[0] == '\'')
			cmd->args[i].arg_value = ft_strtrim(cmd->args[i].arg_value, "'");
		else if (cmd->args[i].arg_value && cmd->args[i].arg_value[0] == '"')
			cmd->args[i].arg_value = ft_strtrim(cmd->args[i].arg_value, "\"");
		i++;
	}
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_gen *gen)
{
	int	builtin;

	builtin = 0;
	clean_outer_quotes(cmd);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		builtin = ft_echo(cmd->args);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		builtin = ft_cd(cmd->args, gen->dir, gen);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		builtin = ft_pwd(gen->dir);
	if (ft_strcmp(cmd->cmd, "env") == 0)
		builtin = ft_env(gen->env);
	if (ft_strcmp(cmd->cmd, "export") == 0)
		builtin = ft_export(cmd->args, gen);
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		builtin = ft_unset(gen->env, cmd->args);
	return (builtin);
}
