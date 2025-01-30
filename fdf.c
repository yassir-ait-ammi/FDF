/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:24:04 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 19:27:18 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_word(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
	}
	return (count);
}

int	**read_map(const char *filename, int *lines, int *line_size, long int **g_dd)
{
	int		fd;
	int		k;
	int		h;
	char	buf;
	char	*s;
	int		**map;
	char	**d;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	k = 0;
	h = 0;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			h++;
		k++;
	}
	close(fd);
	s = malloc(k + 1);
	fd = open(filename, O_RDONLY);
	k = 0;
	while (read(fd, &s[k], 1) > 0)
		k++;
	s[k] = '\0';
	close(fd);
	d = ft_split(s, " \n");
	*g_dd = parsing(d);
	*line_size = count_word(s) / h;
	*lines = h;
	map = malloc((h + 1) * sizeof(int *));
	k = 0;
	while (k <= h)
	{
		map[k] = malloc((*line_size) * sizeof(int));
		k++;
	}
	ft_help_read(&map, &d, *line_size);
	return (free_split(d), free(s), map);
}

void	ft_help_read(int ***map, char ***d, int line_size)
{
	int	fd;
	int	h;
	int	k;

	fd = 0;
	h = 0;
	k = 0;
	while ((*d)[fd])
	{
		(*map)[k][h] = strtol((*d)[fd], NULL, 10);
		h++;
		if (h == line_size)
		{
			h = 0;
			k++;
		}
		fd++;
	}
}

long int	*parsing(char **d)
{
	int		i;
	int		count;
	char	**c;
	long int	*g_dd;

	i = 0;
	count = 0;
	while (d[count])
		count++;
	g_dd = malloc(count * sizeof(long int));
	if (!g_dd)
		return (0);
	i = 0;
	while (d[i])
	{
		c = ft_split(d[i], ",");
		g_dd[i] = (c[1]) ? strtol(c[1], NULL, 16) : 0xffffff;
		free_split(c);
		i++;
	}
	return (g_dd);
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC_KEY)
	{
		cleanup(data, NULL);
		exit(1);
	}
	else
		return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_cord	*main;
	long int	*g_dd;

	parsing_the_map(ac, av, &data, &g_dd);
	g_dd = NULL;
	main = malloc(sizeof(t_cord));
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_SIZE, WINDOW_SIZE, "Yassir");
	data.map = read_map(av[1], &data.lines, &data.line_size, &g_dd);
	data.image.img = mlx_new_image(data.mlx, WINDOW_SIZE, WINDOW_SIZE);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.b_pix,
			&data.image.len, &data.image.endian);
	main->image = &data.image;
	main->map = data.map;
	main->line_size = data.line_size;
	main->line = data.lines;
	main->g_dd = &g_dd;
	print_grid(&main);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	free(g_dd);
	free(main);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
	return (cleanup(&data, &g_dd), 0);
}
