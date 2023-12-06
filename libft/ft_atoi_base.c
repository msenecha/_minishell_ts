/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:45:16 by msenecha          #+#    #+#             */
/*   Updated: 2023/06/29 17:38:50 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_isblank(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}

int	ft_valueof(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	ft_isvalid(char c, int base)
{
	char	*base_min;
	char	*base_maj;

	base_min = "0123456789abcdef";
	base_maj = "0123456789ABCDEF";
	while (base--)
	{
		if (c == base_min[base] || c == base_maj[base])
			return (1);
	}
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = 2;
	while (ft_isblank(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isvalid(str[i], str_base))
		result = result * str_base + ft_valueof(str[i++]);
	return (result * sign);
}
