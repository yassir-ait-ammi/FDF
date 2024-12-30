#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define ESC_KEY 65307


char	*readhh(int fd)
{
	char *s = malloc(12 * sizeof(char));
	if (!s)
		return (NULL);
	int i = 0;
	int j;
	char c;
	while ((j = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		if (c == '0')
		{
			s[i] = c;
			printf("%c", s[i]);
			i++;
		}
	}
	s[i] = '\0';
	printf("\n");
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



void	creat_px(void *mlx, void	*win,int x1, int y1, int x2, int y2,int color)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(mlx, win, x1, y1, color);
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
	}
}

void	print1(void *mlx, void *win, char *s)
{
	int i = 0;
	while (s[i]!='\0')
		i++;
	int j = 1;
	static int y;
	y = y + 45;
	int b;
	while (j < i - 1)
	{
		b = j * 45;
			creat_px(mlx, win, b, y, b + 45, y, 0xff0000);
		j++;
	}
}

void	print2(void *mlx, void *win, char *s)
{
	int j = 1;
	int i = 0;
	int b;
	static int y;
	y = y + 45;
	while (s[i]!='\0')
		i++;
	while (j < i)
	{
		b = j * 45;
			creat_px(mlx, win, b, y, b, y + 45, 0x00FFFF);
		j++;
	}
}

int main()
{
	void *mlx;
	void *win;

	int fd = open("map", O_RDONLY);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "Star Example");
	int p = 0;
	char *s[10];
	while(p <= 9)
	{
		s[p] = readhh(fd);
		print1(mlx, win, s[p]);
		p++;
	}
	p = 0;
	while(p < 9)
	{
		print2(mlx, win, s[p]);
		p++;
	}
	mlx_key_hook(win, handle_key, NULL);
	mlx_loop(mlx);

	return (0);
}
