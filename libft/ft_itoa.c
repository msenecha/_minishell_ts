/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:01:08 by msenecha          #+#    #+#             */
/*   Updated: 2023/03/31 11:34:08 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_itoa_string(int n, int len)
{
	char	*buf;

	buf = ft_calloc(len + 1, sizeof(*buf));
	if (!buf)
		return (NULL);
	if (n == 0)
		buf[0] = '0';
	buf[len] = '\0';
	if (n < 0)
	{
		buf[0] = '-';
		n = -n;
	}
	len--;
	while (n > 0)
	{
		buf[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (buf);
}

char	*ft_itoa(int n)
{
	int	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_itoa_len(n);
	return (ft_itoa_string(n, len));
}
