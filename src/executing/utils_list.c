
#include "../../includes/minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_env	*ft_lstnew_env(char *env)
{
	t_env	*new_elem;
	char	*equal_sign;
	int		key_len;
	int		value_len;

	equal_sign = ft_strchr(env, '=');
	new_elem = malloc(sizeof(t_env));
	if (new_elem)
	{
		key_len = equal_sign - env;
		new_elem->key = malloc(key_len + 1);
		ft_strncpy(new_elem->key, env, key_len);
		new_elem->key[key_len] = '\0';
		value_len = strlen(env) - key_len - 1;
		new_elem->value = malloc(value_len + 1);
		ft_strncpy(new_elem->value, equal_sign + 1, value_len);
		new_elem->value[value_len] = '\0';
		new_elem->next = NULL;
	}
	return (new_elem);
}

t_env	*ft_lstnew(char	*env_data)
{
	t_env	*element;

	element = (t_env *)malloc(sizeof(t_env));
	if (element == NULL)
		return (NULL);
	element->value = env_data;
	element->next = NULL;
	return (element);
}

int	ft_lstsize(t_node *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	ft_envsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

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

void	freelist(t_env *head)
{
	t_env	*tmp;

	while (head->next != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free (head);
}

void	my_free(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		free (argv[i]);
		i++;
	}
	free (argv);
}
