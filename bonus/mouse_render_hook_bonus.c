/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_render_hook_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:14:34 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 18:05:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_clear_window(data->mlx, data->win);
	print_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	mlx_string_put(data->mlx, data->win, 40, 40, 0xFFFFFF, "FDF Controls:");
	mlx_string_put(data->mlx, data->win, 40, 60, 0xFFFFFF, "R -> Reset");
	mlx_string_put(data->mlx, data->win, 40, 80, 0xFFFFFF, "C/V -> Color");
	mlx_string_put(data->mlx, data->win, 40, 100, 0xFFFFFF, "U/D -> For View");
	mlx_string_put(data->mlx, data->win, 40, 120, 0xFFFFFF, "Z/X -> Height");
	mlx_string_put(data->mlx, data->win, 40, 140, 0xFFFFFF, "6/4 -> Rotate X");
	mlx_string_put(data->mlx, data->win, 40, 160, 0xFFFFFF, "1/9 -> Rotate Y");
	mlx_string_put(data->mlx, data->win, 40, 180, 0xFFFFFF, "2/8 -> Rotate Z");
	mlx_string_put(data->mlx, data->win, 40, 200, 0xFFFFFF, "Mouse -> Zoom");
	mlx_string_put(data->mlx, data->win, 40, 220, 0xFFFFFF, "Arrows -> Moving");
	mlx_string_put(data->mlx, data->win, 40, 240, 0xFFFFFF, "ASC -> Exit");
	mlx_string_put(data->mlx, data->win, 40, 260, 0xFFFFFF, "Enjoy!");
	return (0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (button == ZOOM_IN)
		data->zoom++;
	if (button == ZOOM_OUT)
		data->zoom--;
	if (data->zoom > 50)
		data->zoom = 50;
	if (data->zoom < 0.1)
		data->zoom = 0.1;
	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.b_p_pex,
			&data->image.len, &data->image.endian);
	print_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	render(data);
	return (0);
}
