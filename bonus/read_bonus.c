/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:56:30 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/07 15:35:26 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	count_lines_and_chars(const char *filename, int *k, int *h)
{
	int		fd;
	char	buf;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error opening file\n", 20);
		exit(1);
	}
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			(*h)++;
		(*k)++;
	}
	close(fd);
}

static char	*read_file_content(const char *filename, int k)
{
	int		fd;
	char	*s;
	int		p;

	s = malloc(k + 1);
	if (!s)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(s);
		return (NULL);
	}
	p = 0;
	while (read(fd, &s[p], 1) > 0)
		p++;
	close(fd);
	s[p] = '\0';
	return (s);
}

static int	**allocate_map(int h, int line_size)
{
	int	**map;
	int	i;

	map = malloc((h + 1) * sizeof(int *));
	if (!map)
		return (NULL);
	i = 0;
	while (i <= h)
	{
		map[i] = malloc(line_size * sizeof(int));
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

static void	fill_map(int **map, char **d, int *line_size)
{
	int	v;
	int	a;
	int	i;

	v = 0;
	a = 0;
	i = 0;
	while (d[a])
	{
		map[i][v] = ft_atoi(d[a]);
		v++;
		if (v == *line_size)
		{
			v = 0;
			i++;
		}
		a++;
	}
}

int	**read_map(t_data *data, const char *filename, int *lines, int *line_size)
{
	char	*s;
	char	**d;
	int		k;
	int		h;
	int		**map;

	init_map_vars(&k, &h, lines);
	count_lines_and_chars(filename, &k, &h);
	s = read_file_content(filename, k);
	if (!s)
		return (NULL);
	d = ft_split(s, " \n");
	parsing(d, data);
	*line_size = count_word(s) / h;
	*lines = h;
	map = allocate_map(h, *line_size);
	if (!map)
	{
		free_split(d);
		free(s);
		return (NULL);
	}
	fill_map(map, d, line_size);
	free_split(d);
	return (free(s), map);
}
