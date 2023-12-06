/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:59:39 by msenecha          #+#    #+#             */
/*   Updated: 2023/11/10 14:41:07 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((s1[i] == s2[i]) && (s2[i] != '\0' || s1[i] != '\0')
			&& (i < n - 1)))
	{
		i++;
	}
	return ((unsigned char)s1[i] - s2[i]);
}
