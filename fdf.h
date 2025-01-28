/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:09:11 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/03 11:02:35 by yaait-am         ###   ########.fr       */
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

#define ESC_KEY 65307
#define WINDOW_SIZE 1000
#define ZOOM_IN 4
#define ZOOM_OUT 5
#define UP 117
#define DOWN 100
#define PLUS 65451
#define MINUS 65453

long int *g_dd;
float zoom = 0.1;
int kk;

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


#endif
