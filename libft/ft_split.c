/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:33:09 by msenecha          #+#    #+#             */
/*   Updated: 2023/06/29 17:53:48 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_words(const char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (*str)
	{
		if (*str != c && word == 0)
		{
			word = 1;
			i++;
		}
		else if (*str == c)
			word = 0;
		str++;
	}
	return (i);
}

char	**ft_allocate_tab(int i)
{
	char	**tab;

	tab = ft_calloc(sizeof(char *), i + 1);
	if (!tab)
		return (0);
	return (tab);
}

char	*ft_allocate_words(const char *str, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	t_split			p;
	size_t			i;
	size_t			j;

	if (s == NULL || c == '0')
		return (NULL);
	p.len = ft_nb_words(s, c);
	p.tab = ft_allocate_tab(p.len);
	p.len = ft_strlen(s);
	p.index = -1;
	i = 0;
	j = 0;
	while (i <= p.len)
	{
		if (s[i] != c && p.index < 0)
			p.index = i;
		else if ((s[i] == c || i == p.len) && p.index >= 0)
		{
			p.tab[j++] = ft_allocate_words(s, p.index, i);
			p.index = -1;
		}
		i++;
	}
	return (p.tab);
}
