/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:26:56 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 16:34:12 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_z(t_data *data, int *z)
{
	if (!data->zz || *z < 5)
		return ;
	*z *= data->zz;
}

void	ft_help(int z, int *color, t_data *data)
{
	if (!data->kk)
		return ;
	if (z <= 2)
		*color = 0x0000ff;
	else if (z <= 50)
		*color = 0x00ff00;
	else if (z <= 200)
		*color = 0x802020;
	else
		*color = 0xffffff;
}

int	main(int ac, char **av)
{
	t_data	data;

	parsing_the_map(ac, av, &data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_SIZE, WINDOW_SIZE, "Si Yassir");
	data.map = read_map(&data, av[1], &data.lines, &data.line_size);
	data.image.img = mlx_new_image(data.mlx, WINDOW_SIZE, WINDOW_SIZE);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.b_p_pex,
			&data.image.len, &data.image.endian);
	data.angle = 0.0;
	data.ofsset_x = 1;
	data.z_offset = 0;
	data.y_offset = 0;
	data.x_offset = 0;
	data.xu = 0;
	data.kk = 0;
	data.yu = 0;
	data.zz = 0;
	print_grid(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	return (mlx_loop(data.mlx), cleanup(&data), 0);
}
