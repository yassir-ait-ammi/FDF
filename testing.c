#include "fdf.h"

int ofsset_x = 1;

void put_pixel_to_image(t_image *image, int x, int y, int color)
{
	if (x >= 0 && x < WINDOW_SIZE && y >= 0 && y < WINDOW_SIZE)
	{
		char *dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int interpolate(int start, int end, float t)
{
	return (int)(start + t * (end - start));
}

void extract_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int create_color(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

void draw_line_image(t_image *image, int x1, int y1, int x2, int y2, int color1, int color2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int steps = (dx > dy) ? dx : dy;
	int r1, g1, b1, r2, g2, b2;
	extract_rgb(color1, &r1, &g1, &b1);
	extract_rgb(color2, &r2, &g2, &b2);
	int i = 0;
	while (i <= steps)
	{
		float t = (steps == 0) ? 0 : (float)i / steps;
		int r = interpolate(r1, r2, t);
		int g = interpolate(g1, g2, t);
		int b = interpolate(b1, b2, t);
		int interpolated_color = create_color(r, g, b);
		put_pixel_to_image(image, x1, y1, interpolated_color);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
		i++;
	}
}

void isometric(int *x, int *y, int z)
{
	if (!ofsset_x)
		return ;
	int prev_x = *x;
	int prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = ((prev_x + prev_y) * sin(0.523599) - z);
}

void	ft_help(int z, int *color)
{
	if (!kk)
		return ;
	if (z <= 5)
		*color = 0x0000ff;
	else if ( z > 0 && z <= 15)
		*color = 0x00ff00;
	else if (z <= 80)
		*color = 0x802020;
	else
		*color = 0xffffff;
}

void print_grid(t_image *image, int **map, int lines, int line_size)
{
	int scale_x = (1000 / line_size) * zoom;
	int scale_y = (1000 / lines) * zoom;
	int scale = (scale_x < scale_y) ? scale_x : scale_y;
	int grid_center_x = (line_size - 1) / 2;
	if (scale > 20)
		scale = zoom + 15;
	else if (scale == 5)
		scale = zoom + 3;
	else
		scale = zoom +1;
	int grid_center_y = (lines - 1) / 2;
	int x1 = grid_center_x * scale;
	int y1 = grid_center_y * scale;
	isometric(&x1, &y1, 0);
	int x_offset = (1000 / 2) - x1;
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
			ft_help(z, &color);
			x1 = x * scale;
			y1 = y * scale;
			isometric(&x1, &y1, z);
			x1 += x_offset;
			y1 += y_offset;
			put_pixel_to_image(image, x1, y1, color);
			if (x + 1 < line_size) {
				int z_next = map[y][x + 1];
				int x2 = (x + 1) * scale;
				int y2 = y * scale;
				isometric(&x2, &y2, z_next);
				x2 += x_offset;
				y2 += y_offset;
				draw_line_image(image, x1, y1, x2, y2, color, g_dd[y * line_size + x + 1]);
			}
			if (y + 1 < lines) {
				int z_next = map[y + 1][x];
				int x2 = x * scale;
				int y2 = (y + 1) * scale;
				isometric(&x2, &y2, z_next);
				x2 += x_offset;
				y2 += y_offset;
				draw_line_image(image, x1, y1, x2, y2, color, g_dd[(y + 1) * line_size + x]);
			}
			x++;
		}
		y++;
	}
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

int handle_key(int keycode, void *param)
{
	t_data *data = (t_data *)param;
	if (keycode == ESC_KEY)
		exit(0);
	else if (keycode == UP)
		ofsset_x = 0;
	if (keycode == 99)
		kk = 1;
	else if (keycode == DOWN)
		ofsset_x = 1;
	if (keycode == 114)
	{
		kk = 0;
		zoom = 0.1;
		ofsset_x = 1;
	}
	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bits_per_pixel, &data->image.line_length, &data->image.endian);
	print_grid(&data->image, data->map, data->lines, data->line_size);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}


int handle_mouse(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	if (button == ZOOM_IN)
		zoom++;
	if (button == ZOOM_OUT)
		zoom--;
	if (zoom > 50) zoom = 50;
	if (zoom < 0.1) zoom = 0.1;
	t_data *data = (t_data *)param;
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
	data.win = mlx_new_window(data.mlx, WINDOW_SIZE, WINDOW_SIZE, "FDF Zoom");
	data.map = read_map(av[1], &data.lines, &data.line_size);
	data.image.img = mlx_new_image(data.mlx, WINDOW_SIZE, WINDOW_SIZE);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bits_per_pixel, &data.image.line_length, &data.image.endian);

	print_grid(&data.image, data.map, data.lines, data.line_size);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_loop(data.mlx);
	return 0;
}
