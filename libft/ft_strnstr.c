/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:09:25 by msenecha          #+#    #+#             */
/*   Updated: 2023/11/10 14:43:02 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *find, size_t len)
{
	size_t	find_len;

	if (str == NULL && len == 0)
		return (NULL);
	find_len = ft_strlen(find);
	if (find_len == 0)
		return ((char *)str);
	while (*str && len-- >= find_len)
	{
		if (*str == *find && ft_strncmp(str, find, find_len) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
