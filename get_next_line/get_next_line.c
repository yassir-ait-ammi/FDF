/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:37:47 by yaait-am          #+#    #+#             */
/*   Updated: 2024/12/25 11:11:22 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_return(char *s)
{
	int		i;
	int		j;
	char	*new_ret;

	i = 0;
	if (!s || !s[0])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	new_ret = malloc(i + 1);
	if (!new_ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_ret[j] = s[j];
		j++;
	}
	new_ret[j] = '\0';
	return (new_ret);
}

char	*ft_after_new_line(char *s)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), s = NULL, NULL);
	save = malloc(ft_strlen(s) - i);
	if (!save)
		return (free(s), s = NULL, NULL);
	i++;
	while (s[i])
		save[j++] = s[i++];
	save[j] = '\0';
	free(s);
	s = NULL;
	return (save);
}

char	*get_next_line(int fd)
{
	int			i;
	char		*readed;
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = malloc(BUFFER_SIZE + 1);
	if (!readed)
		return (free(save), save = NULL, NULL);
	i = 1;
	while (!(ft_strchr(save, '\n')) && i > 0)
	{
		i = read(fd, readed, BUFFER_SIZE);
		if (i < 0)
			return (free(readed), free(save), save = NULL, NULL);
		readed[i] = '\0';
		save = ft_strjoin(save, readed);
	}
	free(readed);
	line = ft_return(save);
	save = ft_after_new_line(save);
	return (line);
}
