/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:13:51 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/07 10:45:46 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	reset_data(t_data *data)
{
	data->kk = 0;
	data->zoom = 0.1;
	data->ofsset_x = 1;
	data->xu = 0;
	data->yu = 0;
	data->zz = 0;
	data->angle = 0.5;
	data->x_offset = 0;
	data->z_offset = 0;
	data->y_offset = 0;
}

static void	handle_movement(t_data *data, int keycode)
{
	if (keycode == FOK)
		data->yu -= 20;
	else if (keycode == TAHT)
		data->yu += 20;
	else if (keycode == LISSR)
		data->xu -= 20;
	else if (keycode == LIMN)
		data->xu += 20;
}

static void	handle_rotation(t_data *data, int keycode)
{
	if (keycode == Z_AZLMAD || keycode == Z_AFASSIY)
	{
		data->z_offset = 1;
		if (keycode == Z_AZLMAD)
			data->angle += 0.5;
		else
			data->angle += -0.5;
	}
	else if (keycode == X_AZLMAD || keycode == X_AFASSIY)
	{
		data->x_offset = 1;
		if (keycode == X_AZLMAD)
			data->angle += 0.5;
		else
			data->angle += -0.5;
	}
	else if (keycode == Y_AZLMAD || keycode == Y_AFASSIY)
	{
		data->y_offset = 1;
		if (keycode == Y_AZLMAD)
			data->angle += 0.5;
		else
			data->angle += -0.5;
	}
}

static void	recreate_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, WINDOW_X, WINDOW_Y);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.b_p_pex,
			&data->image.len, &data->image.endian);
	print_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	render(data);
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC_KEY)
	{
		cleanup(data);
		exit(0);
	}
	else if (keycode == AFLA)
		data->ofsset_x = 0;
	else if (keycode == IZDAR)
		data->ofsset_x = 1;
	else if (keycode == 114)
		reset_data(data);
	else if (keycode == Z)
		data->zz++;
	else if (keycode == X)
		data->zz--;
	else
	{
		handle_movement(data, keycode);
		handle_color_mode(data, keycode);
		handle_rotation(data, keycode);
	}
	return (recreate_image(data), 0);
}
