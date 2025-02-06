/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:26:56 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/05 12:15:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void ft_z(t_data *data, int *z)
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

int **read_map(t_data *data, const char *filename, int *lines, int *line_size)
{
	int fd = open(filename, O_RDONLY);
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

int handle_key(int keycode, void *param)
{
	t_data *data = (t_data *)param;
    if (keycode == ESC_KEY)
	{
		cleanup(data);
	    exit(0);
	}
	else if (keycode == AFLA)
		data->ofsset_x = 0;
	if (keycode == COLOR)
		data->kk = 1;
	else if (keycode == ANTI_COLOR)
		data->kk = 0;
	if (keycode == IZDAR)
		data->ofsset_x = 1;
	if (keycode == FOK)
		data->yu -= 20;
	else if (keycode == TAHT)
		data->yu += 20;
	else if (keycode == LISSR)
		data->xu -= 20;
	else if (keycode == LIMN)
		data->xu += 20;
	if (keycode == 114)
	{
		data->kk = 0;
		data->zoom = 0.1;
		data->ofsset_x = 1;
		data->xu = 0;
		data->yu = 0;
		data->zz = 0;
		data->angle = 0.5;
		data->x_offset = 0;
		data->z_offset = 0;
		data->y_offset = 0;
	}
	if (keycode == Z)
		data->zz++;
	else if (keycode == X)
		data->zz--;
	if (keycode == Z_AZLMAD)
	{
		data->z_offset = 1;
		data->angle += 0.5;
	}
	else if (keycode == Z_AFASSIY)
	{
		data->z_offset = 1;
		data->angle -= 0.5;
	}
	if (keycode == X_AZLMAD)
	{
		data->x_offset = 1;
		data->angle += 0.5;
	}
	else if (keycode == X_AFASSIY)
	{
		data->x_offset = 1;
		data->angle -= 0.5;
	}
	if (keycode == Y_AZLMAD)
	{
		data->y_offset = 1;
		data->angle += 0.5;
	}
	else if (keycode == Y_AFASSIY)
	{
		data->y_offset = 1;
		data->angle -= 0.5;
	}
	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.b_p_pex, &data->image.len, &data->image.endian);
	print_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	render(data);
	return (0);
}

int render(void *param)
{
    t_data *data = (t_data *)param;

    mlx_clear_window(data->mlx, data->win);
    print_grid(data);
    mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	mlx_string_put(data->mlx, data->win, 40, 40, 0xFFFFFF, "this is my FDF");
	mlx_string_put(data->mlx, data->win, 40, 60, 0xFFFFFF, "here is a resume of the keys and their use:");
	mlx_string_put(data->mlx, data->win, 40, 80, 0xFFFFFF, "R -> back to the original | C -> color | V -> anti color");
	mlx_string_put(data->mlx, data->win, 40, 100, 0xFFFFFF, "U -> up view | D -> down view");
	mlx_string_put(data->mlx, data->win, 40, 120, 0xFFFFFF, "Z -> to increment | X -> to decrement the z of all the point");
	mlx_string_put(data->mlx, data->win, 40, 140, 0xFFFFFF, "'6 and 4' -> rotate with the X axis");
	mlx_string_put(data->mlx, data->win, 40, 160, 0xFFFFFF, "'1 and 9' -> rotate with the Y axis");
	mlx_string_put(data->mlx, data->win, 40, 180, 0xFFFFFF, "'2 and 8' -> rotate with the Z axis");
	mlx_string_put(data->mlx, data->win, 40, 200, 0xFFFFFF, "use the mouse to zoom in and zoom out");
	mlx_string_put(data->mlx, data->win, 40, 220, 0xFFFFFF, "arrows are to move the map the way you like");
	mlx_string_put(data->mlx, data->win, 40, 240, 0xFFFFFF, "I hope that you like it!");
	return (0);
}

int handle_mouse(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	t_data *data = (t_data *)param;
	if (button == ZOOM_IN)
		data->zoom++;
	if (button == ZOOM_OUT)
		data->zoom--;
	if (data->zoom > 50)
		data->zoom = 50;
	if (data->zoom < 0.1)
		data->zoom = 0.1;
	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.b_p_pex, &data->image.len, &data->image.endian);
	print_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	render(data);
	return (0);
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
