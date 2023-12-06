/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svidal <svidal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:55:27 by msenecha          #+#    #+#             */
/*   Updated: 2023/11/17 18:04:35 by svidal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dest = malloc(len1 + len2 + 1);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (++i < len1)
		dest[i] = s1[i];
	i = -1;
	while (++i < len2)
		dest[len1 + i] = s2[i];
	dest[len1 + len2] = '\0';
	return (dest);
}
