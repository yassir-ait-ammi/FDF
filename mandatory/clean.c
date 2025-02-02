/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:26:36 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/01 11:17:43 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	cleanup(t_data *data, long int **g_dd)
{
	if (g_dd)
		return ;
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->map)
	{
		free_map(data->map, data->lines);
		data->map = NULL;
	}
	if (g_dd)
	{
		free(g_dd);
		g_dd = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
