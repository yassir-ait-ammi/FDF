/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:03:27 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/05 16:47:15 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	ft_rotate_z(t_iso *iso, int *x, int *y, double angle)
{
	iso->new_x = iso->prev_x * cos(angle) - iso->prev_y * sin(angle);
	iso->new_y = iso->prev_x * sin(angle) + iso->prev_y * cos(angle);
	*x = iso->new_x;
	*y = iso->new_y;
}

static void	ft_rotate_x(t_iso *iso, int *y, int *z, double angle)
{
	iso->new_y = iso->prev_y * cos(angle) - *z * sin(angle);
	iso->new_z = iso->prev_y * sin(angle) + *z * cos(angle);
	*z = iso->new_z;
	*y = iso->new_y;
}

static void	ft_rotate_y(t_iso *iso, int *x, int *z, double angle)
{
	iso->new_x = iso->prev_x * cos(angle) - *z * sin(angle);
	iso->new_z = iso->prev_x * sin(angle) + *z * cos(angle);
	*z = iso->new_z;
	*x = iso->new_x;
}

void	isometric(t_data *data, int *x, int *y, int z)
{
	t_iso	iso;

	if (!x || !y || !data->ofsset_x)
		return ;
	iso.prev_x = *x;
	iso.prev_y = *y;
	if (data->z_offset)
		ft_rotate_z(&iso, x, y, data->angle);
	if (data->x_offset)
		ft_rotate_x(&iso, y, &z, data->angle);
	if (data->y_offset)
		ft_rotate_y(&iso, x, &z, data->angle);
	iso.iso_x = (*x - *y) * cos(0.523599);
	iso.iso_y = (*x + *y) * sin(0.523599) - z;
	*x = iso.iso_x;
	*y = iso.iso_y;
}
