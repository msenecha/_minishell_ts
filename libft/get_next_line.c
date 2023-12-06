/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:01:26 by msenecha          #+#    #+#             */
/*   Updated: 2023/11/16 16:42:23 by msenecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	new_stash = malloc(ft_strlen(stash) - i + 1 * sizeof(char));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free (stash);
	return (new_stash);
}

char	*trim_line(char *stash)
{
	char	*nl;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	nl = malloc(i + 1 * sizeof(char));
	if (nl == NULL)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		nl[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		nl[i++] = '\n';
	nl[i] = '\0';
	return (nl);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buff;
	int		rd;

	rd = 1;
	while (!ft_strchr(stash, '\n') && rd != 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free (buff);
			return (stash);
		}
		buff[rd] = '\0';
		stash = ft_strjoin(stash, buff);
		free(buff);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, stash, 0) < 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = trim_line(stash);
	stash = clean_stash(stash);
	return (line);
}
