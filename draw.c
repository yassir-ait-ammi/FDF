/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:23:23 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 14:31:45 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_image(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_SIZE && y >= 0 && y < WINDOW_SIZE)
	{
		dst = image->addr + (y * image->len
				+ x * (image->b_pix / 8));
		*(unsigned int *)dst = color;
	}
}

int	interpolate(int start, int end, float t)
{
	return ((int)(start + t * (end - start)));
}

void	draw_line_image(t_image *image, int x1, int y1, int x2, int y2, int color1, int color2)
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

	i = 0;
	dy = abs(y2 - y1);
	dx = abs(x2 - x1);
	ft_ternaries_1(&dx, &dy, &steps);
	err = dx - dy;
	ft_ternaries_2(&y1, &y2, &sy);
	ft_ternaries_2(&x1, &x2, &sx);
	extract_rgb(color1, &r1, &g1, &b1);
	extract_rgb(color2, &r2, &g2, &b2);
	while (i <= steps)
	{
		ft_ternaries_3(&i, &steps, &t);
		r = interpolate(r1, r2, t);
		g = interpolate(g1, g2, t);
		b = interpolate(b1, b2, t);
		cre_color = create_color(r, g, b);
		put_pixel_to_image(image, x1, y1, cre_color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
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

void	isometric(int *x, int *y, int z)
{
	int	iso_x;
	int	iso_y;

	if (!x || !y)
		return ;
	iso_x = (*x - *y) * cos(0.523599);
	iso_y = ((*x + *y) * sin(0.523599) - z);
	*x = iso_x;
	*y = iso_y;
}
