/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:25:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/31 15:58:38 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	setup_grid_offset(t_p *p)
{
	p->x1 = p->grid_center_x * p->scale;
	p->y1 = p->grid_center_y * p->scale;
	isometric(&p->x1, &p->y1, 0);
	p->x_offset = (WINDOW_SIZE / 2) - p->x1;
	p->y_offset = (WINDOW_SIZE / 2) - p->y1;
}

static void	draw_point(t_cord **main, t_p *p)
{
	p->z = (*main)->map[p->y][p->x];
	p->color = (*(*main)->g_dd)[p->y * (*main)->line_size + p->x];
	p->x1 = p->x * p->scale;
	p->y1 = p->y * p->scale;
	isometric(&p->x1, &p->y1, p->z);
	p->x1 += p->x_offset;
	p->y1 += p->y_offset;
	put_pixel_to_image((*main)->image, p->x1, p->y1, p->color);
}

static void	draw_horizontal_line(t_cord **main, t_p *p)
{
	p->z_next = (*main)->map[p->y][p->x + 1];
	p->x2 = (p->x + 1) * p->scale;
	p->y2 = p->y * p->scale;
	isometric(&p->x2, &p->y2, p->z_next);
	p->x2 += p->x_offset;
	p->y2 += p->y_offset;
	p->color2 = (*(*main)->g_dd)[p->y * (*main)->line_size + p->x + 1];
	draw_line_image((*main)->image, p->x1, p->y1, p);
}

static void	draw_vertical_line(t_cord **main, t_p *p)
{
	p->z_next = (*main)->map[p->y + 1][p->x];
	p->x2 = p->x * p->scale;
	p->y2 = (p->y + 1) * p->scale;
	isometric(&p->x2, &p->y2, p->z_next);
	p->x2 += p->x_offset;
	p->y2 += p->y_offset;
	p->color2 = (*(*main)->g_dd)[(p->y + 1) * (*main)->line_size + p->x];
	draw_line_image((*main)->image, p->x1, p->y1, p);
}

void	print_grid(t_cord **main)
{
	t_p	p;

	calculate_grid_params(main, &p);
	setup_grid_offset(&p);
	p.y = 0;
	while (p.y < (*main)->line)
	{
		p.x = 0;
		while (p.x < (*main)->line_size)
		{
			draw_point(main, &p);
			if (p.x + 1 < (*main)->line_size)
				draw_horizontal_line(main, &p);
			if (p.y + 1 < (*main)->line)
				draw_vertical_line(main, &p);
			p.x++;
		}
		p.y++;
	}
}
