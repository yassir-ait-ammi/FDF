/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:23:23 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/31 15:58:52 by yaait-am         ###   ########.fr       */
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

void	draw_line_image(t_image *image, int x1, int y1, t_p *p)
{
	t_l	d;

	d.i = 0;
	d.dy = abs(p->y2 - y1);
	d.dx = abs(p->x2 - x1);
	ft_ternaries_1(&d.dx, &d.dy, &d.steps);
	d.err = d.dx - d.dy;
	ft_ternaries_2(&y1, &p->y2, &d.sy);
	ft_ternaries_2(&x1, &p->x2, &d.sx);
	extract_rgb(p->color, &d.r1, &d.g1, &d.b1);
	extract_rgb(p->color2, &d.r2, &d.g2, &d.b2);
	while (d.i <= d.steps)
	{
		ft_ternaries_3(&d.i, &d.steps, &d.t);
		d.r = interpolate(d.r1, d.r2, d.t);
		d.g = interpolate(d.g1, d.g2, d.t);
		d.b = interpolate(d.b1, d.b2, d.t);
		d.cre_color = create_color(d.r, d.g, d.b);
		put_pixel_to_image(image, x1, y1, d.cre_color);
		if (x1 == p->x2 && y1 == p->y2)
			break ;
		d.e2 = 2 * d.err;
		help_draw_func(&d, &x1, &y1);
		d.i++;
	}
}

void	help_draw_func(t_l *d, int *x1, int *y1)
{
	if (d->e2 > -d->dy)
	{
		d->err -= d->dy;
		(*x1) += d->sx;
	}
	if (d->e2 < d->dx)
	{
		d->err += d->dx;
		(*y1) += d->sy;
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
