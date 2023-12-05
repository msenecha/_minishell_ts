
#include "minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = NULL;
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env	*ft_lstnew_env(char *env)
{
	t_env	*new_elem;
	char	*equal_sign;
	int		key_len;
	int		value_len;

	equal_sign = strchr(env, '=');
	new_elem = malloc(sizeof(t_env));
	if (new_elem)
	{
		key_len = equal_sign - env;
		new_elem->key = malloc(key_len + 1);
		strncpy(new_elem->key, env, key_len);
		new_elem->key[key_len] = '\0';
		value_len = strlen(env) - key_len - 1;
		new_elem->value = malloc(value_len + 1);
		strncpy(new_elem->value, equal_sign + 1, value_len);
		new_elem->value[value_len] = '\0';
		new_elem->next = NULL;
	}
	return (new_elem);
}

t_env	*init_env_list(char **env)
{
	t_env	*var;
	t_env	*new_elem;
	int		i;

	var = NULL;
	i = 0;
	while (env[i])
	{
		new_elem = ft_lstnew_env(env[i]);
		if (new_elem)
			ft_lstadd_back(&var, new_elem);
		i++;
	}
	return (var);
}