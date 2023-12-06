
#include "../../includes/minishell.h"

char	**env_to_str(t_env *env)
{
	int		str_len;
	int		tab_size;
	int		i;
	char	**env_tab;

	//if (ft_strcmp(gen->cmd->cmd, "minishell") == 0
	//	|| ft_strcmp(gen->cmd->cmd, "./minishell") == 0)
	//	ft_increase_shlvl();
	tab_size = ft_envsize(env);
	env_tab = malloc((tab_size + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		env->key = ft_strjoin(env->key, "=");
		str_len = ft_strlen(env->key) + ft_strlen(env->value);
		env_tab[i] = malloc((str_len + 1) * sizeof(char));
		env_tab[i] = ft_strjoin(env->key, env->value);
		env = env->next;
		i++;
	}
	env_tab[i] = '\0';
	return (env_tab);
}