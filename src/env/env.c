
#include "../../includes/minishell.h"

char	*ft_getenv(char *str, t_env *env)
{
	t_env	*var;
	int		var_len;

	var_len = 0;
	if (str[0] == '$')
		str = ft_strtrim(str, "$");
	var_len = ft_strlen(str);
	var = env;
	while (var)
	{
		if (strncmp(var->key, str, var_len) == 0)
		{
			free(str);
			return (var->value);
		}
		var = var->next;
	}
	return (str);
}

int	get_token_len(char *dest)
{
	int	len;

	len = 0;
	while (*dest != '$')
		dest++;
	while (*dest && *dest != ' ' && *dest != '\t' && *dest != '\"')
	{
		len++;
		dest++;
	}
	return (len);
}

char	*expand_with_env_var(char *dest, char *var, int index)
{
	char	*result;
	int		dest_len;
	int		var_len;
	int		i;
	int		j;

	i = 0;
	dest_len = ft_strlen(dest) - get_token_len(dest);
	var_len = ft_strlen(var);
	result = malloc((dest_len + var_len + 2) * sizeof(char));
	while (i < index)
	{
		result[i] = dest[i];
		i++;
	}
	j = 0;
	while (j <= var_len)
		result[i++] = var[j++];
	j = index + get_token_len(dest);
	while (dest[j])
		result[i++] = dest[j++];
	result[i] = '\0';
	//free(dest);
	return (result);
}

char	*get_var_id(char *str, int index)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = index;
	while (str[index] && str[index] != ' ' && str[index] != '\t'
		&& str[index] != '\"' && str[index] != '=')
	{
		index++;
		i++;
	}
	var = malloc((i + 1) * sizeof(char));
	i = 0;
	while (j < index)
	{
		var[i] = str[j];
		i++;
		j++;
	}
	var[i] = '\0';
	return (var);
}

char	*expand_arg(char *str, t_env *env)
{
	int		i;
	char	*id;
	char	*var;
	char	*res;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '$') && (str[i + 1] == '_'
				|| (str[i + 1] > 'A' && str[i + 1] < 'Z')))
		{
			id = get_var_id(str, i);
			var = ft_getenv(id, env);
			free(id);
			res = expand_with_env_var(str, var, i);
			str = ft_strdup(res);
			free(res);
		}
		//else if (str[i] == '$' && str[i + 1] == '?')
		//	str = ft_itoa(gen->ret_val);
		i++;
	}
	return (str);
}
