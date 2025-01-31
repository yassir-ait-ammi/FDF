/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:09:11 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/31 21:26:34 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define ESC_KEY 65307
# define WINDOW_SIZE 1000

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		b_pix;
	int		len;
	int		endian;
}				t_image;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_image	image;
	int		**map;
	int		lines;
	int		line_size;

}				t_data;

typedef struct s_cord
{
	int			x;
	int			y;
	int			z;
	int			color;
	int			line;
	int			line_size;
	t_image		*image;
	int			**map;
	long int	**g_dd;
}		t_cord;

typedef struct s_fd
{
	int		fd;
	int		k;
	int		h;
	char	buf;
	char	*s;
	int		**map;
	char	**d;
}		t_fd;

typedef struct s_p
{
	int	scale_x;
	int	scale_y;
	int	scale;
	int	grid_center_x;
	int	grid_center_y;
	int	x1;
	int	y1;
	int	x_offset;
	int	y_offset;
	int	x;
	int	y;
	int	z;
	int	z_next;
	int	x2;
	int	y2;
	int	color;
	int	color2;
}		t_p;

typedef struct s_l
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		steps;
	int		i;
	int		r;
	float	t;
	int		g;
	int		b;
	int		cre_color;
	int		r1;
	int		r2;
	int		g1;
	int		g2;
	int		b1;
	int		b2;
	int		e2;
}		t_l;

long		help_strtol(const char *str, int base, int sign);
long		ft_strtol(const char *str, int base);
int			main(int ac, char **av);
char		**ft_split(char *s, char *charset);
long int	*parsing(char **d);
int			render(void *param);
int			count_word(char *s);
int			**read_map(const char *filename,
				int *lines, int *line_size, long int **g_dd);
int			handle_key(int keycode, void *param);
void		cleanup(t_data *data, long int **g_dd);
void		free_map(int **map, int lines);
void		free_split(char **split);
void		print_grid(t_cord **main);
void		put_pixel_to_image(t_image *image, int x, int y, int color);
int			interpolate(int start, int end, float t);
void		draw_line_image(t_image *image, int x1, int y1, t_p *p);
void		isometric(int *x, int *y, int z);
void		extract_rgb(int color, int *r, int *g, int *b);
int			create_color(int r, int g, int b);
void		ft_ternaries_1(int *a, int *b, int *x);
void		ft_ternaries_2(int *a, int *b, int *x);
void		ft_ternaries_3(int *a, int *b, float *x);
void		ft_help_read(int ***map, char ***d, int line_size);
void		calculate_grid_params(t_cord **main, t_p *p);
void		adjust_scale(t_p *p);
void		help_draw_func(t_l *d, int *x1, int *y1);
void		parsing_the_map(int ac, char **av, t_data *data, long int **g_dd);
void		help_read_map(int *fd, const char *filename, int *k, int *h);

#endif
