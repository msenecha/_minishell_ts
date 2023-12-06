/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:43:21 by msenecha          #+#    #+#             */
/*   Updated: 2023/06/29 17:12:06 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int a)
{
	write(1, &a, 1);
	return (1);
}

int	ft_printsymb(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_read_flag(va_list args, const char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += ft_printchar(va_arg(args, int));
	if (format == 's')
		length += ft_printstr(va_arg(args, char *));
	if (format == 'p')
		length += ft_printptr(va_arg(args, unsigned long));
	if (format == 'd' || format == 'i')
		length += ft_printnbr(va_arg(args, int));
	if (format == '%')
		length += ft_printsymb();
	if (format == 'u')
		length += ft_printunsd(va_arg(args, unsigned int));
	if (format == 'x' || format == 'X')
		length += ft_printhex(va_arg(args, unsigned int), format);
	return (length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		lgth;
	int		i;

	lgth = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			lgth += ft_read_flag(args, str[i + 1]);
			i++;
		}
		else
			lgth += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (lgth);
}
