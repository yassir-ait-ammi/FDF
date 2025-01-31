/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:09:11 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 11:42:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

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
#define ZOOM_IN 4
#define ZOOM_OUT 5
#define AFLA 117
#define IZDAR 100
#define PLUS 65451
#define MINUS 65453
#define FOK 65362
#define TAHT 65364
#define LIMN 65363
#define LISSR 65361 
#define Z 122
#define Z_AFASSIY 65431
#define Z_AZLMAD 65433
#define X_AFASSIY 65432
#define X_AZLMAD 65430
#define Y_AFASSIY 65434
#define Y_AZLMAD 65436
#define X 120
#define COLOR 99
#define ANTI_COLOR 118
long int *g_dd;
float zoom = 0.1;
int kk;
int xu;
int yu;
double angle = 0.0;
int ofsset_x = 1;
int x_offset = 0;
int z_offset = 0;
int y_offset = 0;
int zz;

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

char	**ft_split(char *s, char *charset);
void    parsing(char **d);
int 	render(void *param);


#endif
