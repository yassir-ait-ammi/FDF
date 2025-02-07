/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:34:25 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/07 10:44:33 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	put_pixel_to_image(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_X && y >= 0 && y < WINDOW_Y)
	{
		dst = image->addr +(y * image->len + x * (image->b_p_pex / 8));
		*(unsigned int *)dst = color;
	}
}

int	interpolate(int start, int end, float t)
{
	return ((int)(start + t * (end - start)));
}

void	extract_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	count_word(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
	}
	return (count);
}
