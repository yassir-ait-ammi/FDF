/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:25:00 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 19:44:15 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	calculate_scale(t_data *data, t_draw_info *info)
{
	int	scale_x;
	int	scale_y;

	scale_x = (WINDOW_SIZE / data->line_size) * data->zoom;
	scale_y = (WINDOW_SIZE / data->lines) * data->zoom;
	if (scale_x < scale_y)
		info->scale = scale_x;
	else
		info->scale = scale_y;
	if (info->scale > 20)
		info->scale = data->zoom + 15;
	else if (info->scale == 5)
		info->scale = data->zoom + 3;
	else
		info->scale = data->zoom + 1;
}

static void	calculate_offsets(t_data *data, t_draw_info *info)
{
	int	x1;
	int	y1;
	int	grid_center_x;
	int	grid_center_y;

	grid_center_x = (data->line_size - 1) / 2;
	grid_center_y = (data->lines - 1) / 2;
	x1 = grid_center_x * info->scale;
	y1 = grid_center_y * info->scale;
	isometric(data, &x1, &y1, 0);
	info->x_offset = (WINDOW_SIZE / 2) - x1 + data->xu;
	info->y_offset = (WINDOW_SIZE / 2) - y1 + data->yu;
}

static void	draw_connections(t_image *image, t_point p, t_data *data,
		t_draw_info *info)
{
	if (info->x + 1 < data->line_size)
	{
		p.x1 = (info->x + 1) * info->scale;
		p.y1 = info->y * info->scale;
		p.z1 = data->map[info->y][info->x + 1];
		ft_z(data, &p.z1);
		isometric(data, &p.x1, &p.y1, p.z1);
		p.x1 += info->x_offset;
		p.y1 += info->y_offset;
		p.color1 = data->g_dd[info->y * data->line_size + info->x + 1];
		draw_line_image(image, p.x, p.y, &p);
	}
	if (info->y + 1 < data->lines)
	{
		p.x1 = info->x * info->scale;
		p.y1 = (info->y + 1) * info->scale;
		p.z1 = data->map[info->y + 1][info->x];
		ft_z(data, &p.z1);
		isometric(data, &p.x1, &p.y1, p.z1);
		p.x1 += info->x_offset;
		p.y1 += info->y_offset;
		p.color1 = data->g_dd[(info->y + 1) * data->line_size + info->x];
		draw_line_image(image, p.x, p.y, &p);
	}
}

static void	process_point(t_image *image, t_data *data, t_draw_info *info)
{
	t_point	p1;
	int		z;

	z = data->map[info->y][info->x];
	ft_z(data, &z);
	p1.color = data->g_dd[info->y * data->line_size + info->x];
	ft_help(z, &p1.color, data);
	p1.x = info->x * info->scale;
	p1.y = info->y * info->scale;
	p1.z = z;
	isometric(data, &p1.x, &p1.y, z);
	p1.x += info->x_offset;
	p1.y += info->y_offset;
	put_pixel_to_image(image, p1.x, p1.y, p1.color);
	draw_connections(image, p1, data, info);
}

void	print_grid(t_data *data)
{
	t_draw_info	info;

	info.y = 0;
	calculate_scale(data, &info);
	calculate_offsets(data, &info);
	while (info.y < data->lines)
	{
		info.x = 0;
		while (info.x < data->line_size)
		{
			process_point(&data->image, data, &info);
			info.x++;
		}
		info.y++;
	}
}
