#include "fdf.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#define ESC_KEY 65307
#define WINDOW_SIZE 1000
#define ZOOM_IN 4  // Mouse scroll up event
#define ZOOM_OUT 5 // Mouse scroll down event

long int *g_dd;
float zoom = 1.0;

typedef struct s_image {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}   t_image;

typedef struct s_data {
	void *mlx;
	void *win;
	t_image image;
	int **map;
	int lines;
	int line_size;
} t_data;

void put_pixel_to_image(t_image *image, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_SIZE && y >= 0 && y < WINDOW_SIZE)
	{
		char *dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void isometric(int *x, int *y, int z)
{
	int prev_x = *x;
	int prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

void print_grid(t_image *image, int **map, int lines, int line_size)
{
	int scale = (1000 / (line_size > lines ? line_size : lines)) * zoom;
	if (scale < 1) scale = 1;

	int grid_center_x = (line_size - 1) / 2;
	int grid_center_y = (lines - 1) / 2;
	int x_offset = (1000 / 2) - (grid_center_x * scale);
	int y_offset = (1000 / 2) - (grid_center_y * scale);

	for (int y = 0; y < lines; y++) {
		for (int x = 0; x < line_size; x++) {
			int z = map[y][x];
			int color = g_dd[y * line_size + x];
			int x1 = x * scale;
			int y1 = y * scale;
			isometric(&x1, &y1, z);
			x1 += x_offset;
			y1 += y_offset;
			put_pixel_to_image(image, x1, y1, color);
		}
	}
}

int handle_key(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		exit(0);
	return (0);
}

int handle_mouse(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	t_data *data = (t_data *)param;
	if (button == ZOOM_IN)
		zoom *= 1.1;
	else if (button == ZOOM_OUT)
		zoom /= 1.1;

	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);

	print_grid(&data->image, data->map, data->lines, data->line_size);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}


int count_word(char *s)
{
	int i = 0;
	int count = 0;

	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
	}
	return count;
}

int **read_map(const char *filename, int *lines, int *line_size)
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
	parsing(d);
	*line_size = count_word(s) / h;
	*lines = h;
	int **map = malloc(h * sizeof(int *));
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
	free(s);
	return map;
}

void parsing(char **d)
{
	int i = 0;
	int count = 0;

	while (d[count])
		count++;
	g_dd = malloc(count * sizeof(long int));

	char **c;
	i = 0;
	while (d[i])
	{
		c = ft_split(d[i], ",");
		g_dd[i] = (c[1]) ? strtol(c[1], NULL, 16) : 0xffffff;
		free(c);
		i++;
	}
}

// Include your read_map, count_word, parsing, and other necessary functions

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("Usage: ./fdf <file map name>\n");
		exit(1);
	}

	t_data data;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_SIZE, WINDOW_SIZE, "FDF Zoom");
	data.map = read_map(av[1], &data.lines, &data.line_size);
	data.image.img = mlx_new_image(data.mlx, WINDOW_SIZE, WINDOW_SIZE);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bits_per_pixel, &data.image.line_length, &data.image.endian);

	print_grid(&data.image, data.map, data.lines, data.line_size);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_key_hook(data.win, handle_key, NULL);
	mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_loop(data.mlx);
	return 0;
}
