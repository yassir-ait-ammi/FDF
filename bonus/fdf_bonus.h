/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:09:11 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 16:21:38 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define ESC_KEY 65307
# define WINDOW_SIZE 1000
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define AFLA 117
# define IZDAR 100
# define PLUS 65451
# define MINUS 65453
# define FOK 65362
# define TAHT 65364
# define LIMN 65363
# define LISSR 65361
# define Z 122
# define Z_AFASSIY 65431
# define Z_AZLMAD 65433
# define X_AFASSIY 65432
# define X_AZLMAD 65430
# define Y_AFASSIY 65434
# define Y_AZLMAD 65436
# define X 120
# define COLOR 99
# define ANTI_COLOR 118

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			b_p_pex;
	int			len;
	int			endian;
}				t_image;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		image;
	int			**map;
	int			lines;
	int			line_size;
	long int	*g_dd;
	float		zoom;
	int			kk;
	int			xu;
	int			yu;
	double		angle;
	int			ofsset_x;
	int			z_offset;
	int			zz;
	int			scale_x;
	int			scale_y;
	int			scale;
	int			grid_center_x;
	int			grid_center_y;
	int			x1;
	int			y1;
	int			x_offset;
	int			y_offset;
	int			x;
	int			y;
	int			z;
	int			z_next;
	int			x2;
	int			y2;
	int			color;
	int			color2;
}				t_data;

typedef struct s_iso
{
	int			prev_x;
	int			prev_y;
	int			new_x;
	int			new_y;
	int			new_z;
	int			iso_x;
	int			iso_y;
}				t_iso;

typedef struct s_d
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			steps;
	int			r1;
	int			g1;
	int			b1;
	int			r2;
	int			g2;
	int			b2;
	int			i;
	int			r;
	int			g;
	int			b;
	int			i_color;
	int			e2;
	float		t;
}				t_d;

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
	int			x1;
	int			y1;
	int			z1;
	int			color1;
}				t_point;

typedef struct s_draw_info
{
	int			x;
	int			y;
	int			scale;
	int			x_offset;
	int			y_offset;
}				t_draw_info;

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

char				**ft_split(char *s, char *charset);
void				parsing(char **d, t_data *data);
int					render(void *param);
void				print_grid(t_data *data);
void				ft_help(int z, int *color, t_data *data);
void				isometric(t_data *data, int *x, int *y, int z);
void				ft_z(t_data *data, int *z);
void				put_pixel_to_image(t_image *image, int x, int y, int color);
int					interpolate(int start, int end, float t);
void				extract_rgb(int color, int *r, int *g, int *b);
int					create_color(int r, int g, int b);
void				draw_line_image(t_image *image, int x1, int y1, t_point *p);
int					count_word(char *s);
void				free_split(char **split);
int					**read_map(t_data *data, const char *filename,
						int *lines, int *line_size);
void				parsing(char **d, t_data *data);
void				free_map(int **map, int lines);
void				cleanup(t_data *data);
int					handle_key(int keycode, void *param);
int					handle_mouse(int button, int x, int y, void *param);
int					main(int ac, char **av);
void				handle_color_mode(t_data *data, int keycode);
long				ft_strtol(const char *str, int base);
void				init_map_vars(int *k, int *h, int *p);
void				parsing_the_map(int ac, char **av, t_data *data);
void				prs_the_fd(char *str);
void				ft_handle_the_error(char *filename, t_data *data);
int					ft_help_the_handle(char **str);
int					is_digit(char c);
int					more_prs(char *str);
void				help_read_map(int *fd, const char *filename, int *k,
						int *h);
int					close_window(void *param);

#endif
