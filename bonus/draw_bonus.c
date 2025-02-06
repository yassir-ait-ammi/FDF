/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:37:31 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 15:52:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	help_init(int x, int y, int z)
{
	if (z == 1)
	{
		if (x < y)
			return (1);
		else
			return (-1);
	}
	if (z == 2)
	{
		if (x > y)
			return (x);
		else
			return (y);
	}
	return (0);
}

static void	ft_init_line(t_d *d, int x1, t_point *p, int y1)
{
	d->dx = abs(p->x1 - x1);
	d->dy = abs(p->y1 - y1);
	d->sx = help_init(x1, p->x1, 1);
	d->sy = help_init(y1, p->y1, 1);
	d->err = d->dx - d->dy;
	d->steps = help_init(d->dx, d->dy, 2);
	d->i = 0;
}

static void	ft_update_position(t_d *d, int *x1, int *y1)
{
	d->e2 = 2 * d->err;
	if (d->e2 > -d->dy)
	{
		d->err -= d->dy;
		*x1 += d->sx;
	}
	if (d->e2 < d->dx)
	{
		d->err += d->dx;
		*y1 += d->sy;
	}
}

static void	ft_calc_color(t_d *d)
{
	if (d->steps == 0)
		d->t = 0;
	else
		d->t = (float)d->i / d->steps;
	d->r = interpolate(d->r1, d->r2, d->t);
	d->g = interpolate(d->g1, d->g2, d->t);
	d->b = interpolate(d->b1, d->b2, d->t);
	d->i_color = create_color(d->r, d->g, d->b);
}

void	draw_line_image(t_image *image, int x1, int y1, t_point *p)
{
	t_d	d;

	ft_init_line(&d, x1, p, y1);
	extract_rgb(p->color, &d.r1, &d.g1, &d.b1);
	extract_rgb(p->color1, &d.r2, &d.g2, &d.b2);
	while (d.i <= d.steps)
	{
		ft_calc_color(&d);
		put_pixel_to_image(image, x1, y1, d.i_color);
		if (x1 == p->x1 && y1 == p->y1)
			break ;
		ft_update_position(&d, &x1, &y1);
		d.i++;
	}
}
