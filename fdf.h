/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:09:11 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 19:28:05 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>

#define ESC_KEY 65307
#define WINDOW_SIZE 1000


typedef struct	s_image {
	void	*img;
	char	*addr;
	int		b_pix;
	int		len;
	int		endian;
}				t_image;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	t_image	image;
	int		**map;
	int		lines;
	int		line_size;

}				t_data;

typedef struct s_cord
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	line;
	int	line_size;
	t_image	*image;
	int		**map;
	long int	**g_dd;
}		t_cord;

int			main(int ac, char **av);
char		**ft_split(char *s, char *charset);
long int	*parsing(char **d);
int			render(void *param);
int			count_word(char *s);
int			**read_map(const char *filename, int *lines, int *line_size, long int **g_dd);
int			handle_key(int keycode, void *param);
void		cleanup(t_data *data, long int **g_dd);
void		free_map(int **map, int lines);
void		free_split(char **split);
void		print_grid(t_cord **main);
void		put_pixel_to_image(t_image *image, int x, int y, int color);
int			interpolate(int start, int end, float t);
void		draw_line_image(t_image *image, int x1, int y1, int x2, int y2, int color1, int color2);
void		isometric(int *x, int *y, int z);
void		extract_rgb(int color, int *r, int *g, int *b);
int			create_color(int r, int g, int b);
void		ft_ternaries_1(int *a, int *b, int *x);
void		ft_ternaries_2(int *a, int *b, int *x);
void		ft_ternaries_3(int *a, int *b, float *x);
void		ft_help_read(int ***map, char ***d, int line_size);
void		ft_help_print(t_cord **poi, t_cord **sec, t_cord **scal, t_cord **cen);
void		put_pix(t_cord **poi, t_cord **cen, t_cord **scal, t_cord **sec);
void		ft_alloc(t_cord **poi, t_cord **sec, t_cord **	scal, t_cord **cen);
void		ft_pass_to_draw(t_cord **sec, t_cord **poi, t_cord **cen, t_cord **scal);
void		parsing_the_map(int ac, char **av, t_data *data, long int **g_dd);

#endif
