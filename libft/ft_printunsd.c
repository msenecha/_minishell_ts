/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:22:29 by msenecha          #+#    #+#             */
/*   Updated: 2023/06/29 17:26:52 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_uitoa_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_uitoa_string(unsigned int n, int len)
{
	char	*buf;

	buf = ft_calloc(len + 1, sizeof(*buf));
	if (!buf)
		return (NULL);
	if (n == 0)
		buf[0] = '0';
	buf[len] = '\0';
	len--;
	while (n > 0)
	{
		buf[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (buf);
}

static	char	*ft_uitoa(unsigned int n)
{
	int	len;

	len = ft_uitoa_len(n);
	return (ft_uitoa_string(n, len));
}

int	ft_printunsd(unsigned int n)
{
	char	*result;
	int		len;

	result = ft_uitoa(n);
	len = ft_printstr(result);
	free(result);
	return (len);
}
