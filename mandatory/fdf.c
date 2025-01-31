/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:24:04 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/31 21:13:42 by yaait-am         ###   ########.fr       */
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

int	**read_map(const char *filename, int *len, int *size, long int **g_dd)
{
	t_fd	fd;

	help_read_map(&fd.fd, filename, &fd.k, &fd.h);
	fd.s = malloc(fd.k + 1);
	fd.fd = open(filename, O_RDONLY);
	fd.k = 0;
	while (read(fd.fd, &fd.s[fd.k], 1) > 0)
		fd.k++;
	fd.s[fd.k] = '\0';
	close(fd.fd);
	fd.d = ft_split(fd.s, " \n");
	*g_dd = parsing(fd.d);
	*size = count_word(fd.s) / fd.h;
	*len = fd.h;
	fd.map = malloc((fd.h + 1) * sizeof(int *));
	fd.k = 0;
	while (fd.k <= fd.h)
	{
		fd.map[fd.k] = malloc((*size) * sizeof(int));
		fd.k++;
	}
	ft_help_read(&fd.map, &fd.d, *size);
	return (free_split(fd.d), free(fd.s), fd.map);
}

long int	*parsing(char **d)
{
	int			i;
	int			count;
	char		**c;
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
		if (c[1])
			g_dd[i] = ft_strtol(c[1], 16);
		else
			g_dd[i] = 0xffffff;
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
		exit(0);
	}
	else
		return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_cord		*main;
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
