/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:38:51 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/05 12:11:27 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(int **map, int lines)
{
	int	i;

	i = 0;
	while (i <= lines)
	{
		free(map[i]);
		i++;
	}
	if (map)
	{
		free(map);
		map = NULL;
	}
}

void	cleanup(t_data *data)
{
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map)
	{
		free_map(data->map, data->lines);
		data->map = NULL;
	}
	if (data->g_dd)
	{
		free(data->g_dd);
		data->g_dd = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
