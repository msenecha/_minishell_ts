/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidal <svidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:01:57 by svidal            #+#    #+#             */
/*   Updated: 2023/11/17 12:09:22 by svidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_quotes_built(char *str, int has_quotes)
{
	int		i;
	char	is_quote;

	i = 1;
	if (has_quotes > 0)
	{
		if (has_quotes == 1)
			is_quote = '\"';
		else if (has_quotes == 2)
			is_quote = '\'';
		while (str[i] != is_quote && str[i + 1] != ' ')
		{
			if (str[i] == '\0')
				return (0);
			i++;
		}
		return (i);
	}
	return (1);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char		*dest_ptr;
	const char	*src_ptr;

	dest_ptr = dest;
	src_ptr = src;
	while (*src != '\0')
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src++;
	}
	dest = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*dest_ptr;

	dest_ptr = dest;
	while (*dest_ptr != '\0')
		dest_ptr++;
	while (*src != '\0')
	{
		*dest_ptr = *src;
		dest_ptr++;
		src++;
	}
	*dest_ptr = '\0';
	return (dest);
}
