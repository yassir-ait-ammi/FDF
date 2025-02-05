/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:26:56 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/05 16:49:53 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_z(t_data *data, int *z)
{
	if (!data->zz || *z < 5)
		return ;
	*z *= data->zz;
}

void	ft_help(int z, int *color, t_data *data)
{
	if (!data->kk)
		return ;
	if (z <= 2)
		*color = 0x0000ff;
	else if (z <= 50)
		*color = 0x00ff00;
	else if (z <= 200)
		*color = 0x802020;
	else
		*color = 0xffffff;
}

int	**read_map(t_data *data, const char *filename, int *lines, int *line_size)
{
	int	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("Error opening file");
		exit(1);
	}
	char buf;
	int k = 0, h = 0;

	while (read(fd, &buf, 1) > 0) {
		if (buf == '\n')
			h++;
		k++;
	}
	close(fd);
	char *s = malloc(k + 1);
	fd = open(filename, O_RDONLY);
	int p = 0;

	while (read(fd, &s[p], 1) > 0)
		p++;
	close(fd);
	s[p] = '\0';
	char **d = ft_split(s, " \n");
	parsing(d, data);
	*line_size = count_word(s) / h;
	*lines = h;
	int **map = malloc((h + 1) * sizeof(int *));
	int i = 0;
	while (i <= h)
	{
		map[i] = malloc((*line_size) * sizeof(int));
		i++;
	}
	int v = 0, a = 0;
	i = 0;
	while (d[a])
	{
		map[i][v] = strtol(d[a], NULL, 10);
		v++;
		if (v == *line_size)
		{
			v = 0;
			i++;
		}
		a++;
	}
	free_split(d);
	free(s);
	return map;
}

void parsing(char **d, t_data *data)
{
	int i = 0;
	int count = 0;

	while (d[count])
		count++;
	data->g_dd = malloc(count * sizeof(long int));
	if (!data->g_dd)
		return ;
	char **c;
	i = 0;
	while (d[i])
	{
		c = ft_split(d[i], ",");
		data->g_dd[i] = (c[1]) ? strtol(c[1], NULL, 16) : 0xffffff;
		free_split(c);
		i++;
	}
}

int main(int ac, char **av)
{
	t_data data;
	if (ac != 2) {
		printf("Usage: ./test <file map name>\n");
		exit(1);
	}
	int fd = open(av[1], O_RDONLY);
	if (fd < 0) {
		perror("Error opening file");
		cleanup(&data);
		exit(1);
	}
	char buf;
	if (read(fd, &buf, 1) == 0)
	{
		printf("Error :invalid map\n");
		cleanup(&data);
		exit(1);
	}
	close(fd);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_SIZE, WINDOW_SIZE, "FDF Zoom");
	data.map = read_map(&data, av[1], &data.lines, &data.line_size);
	data.image.img = mlx_new_image(data.mlx, WINDOW_SIZE, WINDOW_SIZE);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.b_p_pex, &data.image.len, &data.image.endian);
	data.zoom = 0.1;
	data.angle = 0.0;
	data.ofsset_x = 1;
	data.z_offset = 0;
	data.y_offset = 0;
	data.x_offset = 0;
	data.xu = 0;
	data.kk = 0;
	data.yu = 0;
	data.zz = 0;
	print_grid(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_loop(data.mlx);
	cleanup(&data);
	return 0;
}
