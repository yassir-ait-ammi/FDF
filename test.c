/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:30:39 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/03 16:18:02 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

int count_word(char *s)
{
	int i = 0;
	int a = 0;
	if (s[0] != ' ' && s[0] != '\n')
		a++;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == ' ' && (s[i + 1] != ' ' && s[i + 1] != '\0' && s[i + 1] != '\n'))
			a++;
		i++;
	}
	return (a);
}

char	*read_map(int fd, int k)
{
	char *s = malloc((k + 1) * sizeof(char));
	if (!s)
		return (NULL);
	int i = 0;
	int j;
	char c;
	while ((j = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		if (c >= '0' && c <= '9')
		{
			s[i] = c;
			i++;
		}
	}
	s[i] = '\0';
	if (j == 0 && i == 0)
	{
		free(s);
		exit(1);
	}
	return (s);
}

int handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == ESC_KEY)
		exit(0);
	return (0);
}


void	draw_line(void *mlx, void	*win,int x1, int y1, int x2, int y2,int color)
{
	int dx = abs(x2 - x1);// 40 -40 = 0
	int dy = abs(y2 - y1);// 900 - 450 = 450
	int sx;//-1
	int sy;//-1
	int err = dx - dy;//-450

	if (x1 < x2)
		sx = 1;
	else

		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		mlx_pixel_put(mlx, win, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

void project(int x, int y, int z, int *x_proj, int *y_proj, int x_y, int x_offset, int y_offset)
{
	*x_proj = x_offset + (x - y) * (x_y / 2);
	*y_proj = y_offset + (x + y) * (x_y / 4) - z;
z;
}

void print_grid(void *mlx, void *win, int **map, int lines, int line_size, int max_x, int max_y)
{
	int min_x = max_x / line_size;
	int color;
	int min_y = max_y / lines;
	int x_y = (min_x < min_y) ? min_x : min_y;
	int grid_center_x = (line_size - 1) / 2;
	int grid_center_y = (lines - 1) / 2;
	int center_x, center_y;
	project(grid_center_x, grid_center_y, 0, &center_x, &center_y, x_y, 0, 0);
	int x_offset = (max_x / 2) - center_x;
	int y_offset = (max_y / 2) - center_y;
	for (int y = 0; y < lines; y++) {
		for (int x = 0; x < line_size; x++) {
			int x1, y1, x2, y2;
			int z = map[y][x];

			project(x, y, z, &x1, &y1, x_y, x_offset, y_offset);
			if (x + 1 < line_size)
			{
				int z_next = map[y][x + 1];
				project(x + 1, y, z_next, &x2, &y2, x_y, x_offset, y_offset);
				if (z > 0)
					color = 0xFFFFAA;
				else
					color = 0xffffff;
				draw_line(mlx, win, x1, y1, x2, y2, color);
			}
			if (y + 1 < lines) {
				int z_next = map[y + 1][x];
				project(x, y + 1, z_next, &x2, &y2, x_y, x_offset, y_offset);
				draw_line(mlx, win, x1, y1, x2, y2, color);
			}
		}
	}
}

int main(int ac, char **av)
{
	void *mlx;
	void *win;
	int h = 0;
	char buf;
	if (ac != 2)
	{
		printf("./tes <file map name>");
		exit(1);
	}
	int fd = open(av[1], O_RDONLY);
	int k = 0;
	int g = 0;
	while (read(fd, &buf, 1) > 0)
		k++;
	close(fd);
	char *s = malloc(k + 1);
	fd = open(av[1], O_RDONLY);
	int p = 0;
	while (read(fd, &s[p], 1) > 0)
	{
		if (s[p] == '\n')
			h++;
		p++;
	}
	close(fd);
	char **d = ft_split(s, " \n");
	int line_size = count_word(s);
	int **map = malloc(h * sizeof(int *));
	for (int i = 0; i < h; i++)
		map[i] = malloc(line_size * sizeof(int));
	int i = 0, v = 0, a = 0;
	while (d[a])
	{
		map[i][v] = atoi(d[a]);
		v++;
		if (v == line_size) {
			v = 0;
			i++;
		}
		a++;
	}
	mlx = mlx_init();
	int max_x = 1000;
	int max_y = 500;
	win = mlx_new_window(mlx, max_x, max_y, "si yassir");
	print_grid(mlx, win, map, h, line_size, max_x, max_y);
	mlx_key_hook(win, handle_key, NULL);
	mlx_loop(mlx);
	for (int i = 0; i < h; i++) {
		free(map[i]);
	}

	return 0;
}
