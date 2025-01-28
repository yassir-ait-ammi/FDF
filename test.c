#include "fdf.h"

int offset_x = 0; // Added global offset for horizontal movement

void put_pixel_to_image(t_image *image, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_SIZE && y >= 0 && y < WINDOW_SIZE)
	{
		char *dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void print_grid(t_image *image, int **map, int lines, int line_size)
{
	int scale_x = (1000 / line_size) * zoom;
	int scale_y = (1000 / lines) * zoom;
	int scale = (scale_x < scale_y) ? scale_x : scale_y;
	int grid_center_x = (line_size - 1) / 2;
	if (scale > 20)
		scale = 15;
	else if (scale == 5)
		scale = 3;
	else
		scale = 1;
	int grid_center_y = (lines - 1) / 2;
	int x1 = grid_center_x * scale;
	int y1 = grid_center_y * scale;
	isometric(&x1, &y1, 0);
	int x_offset = (1000 / 2) - x1 + offset_x;
	int y_offset = (1000 / 2) - y1;
	int y = 0;
	int x;
	while (y < lines)
	{
		x = 0;
		while (x < line_size)
		{
			int z = map[y][x];
			int color = g_dd[y * line_size + x];
			x1 = x * scale;
			y1 = y * scale;
			isometric(&x1, &y1, z);
			x1 += x_offset;
			y1 += y_offset;
			put_pixel_to_image(image, x1, y1, color);
			x++;
		}
		y++;
	}
}

int handle_key(int keycode, void *param)
{
	t_data *data = (t_data *)param;
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == LEFT_KEY)
		offset_x -= 20;
	else if (keycode == RIGHT_KEY)
		offset_x += 20;

	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);

	print_grid(&data->image, data->map, data->lines, data->line_size);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("Usage: ./test <file map name>\n");
		exit(1);
	}
	t_data data;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_SIZE, WINDOW_SIZE, "FDF Zoom and Move");
	data.map = read_map(av[1], &data.lines, &data.line_size);
	data.image.img = mlx_new_image(data.mlx, WINDOW_SIZE, WINDOW_SIZE);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bits_per_pixel, &data.image.line_length, &data.image.endian);

	print_grid(&data.image, data.map, data.lines, data.line_size);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
	return 0;
}
