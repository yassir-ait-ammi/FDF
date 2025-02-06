/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiliz_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:42:04 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 16:10:47 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	parsing(char **d, t_data *data)
{
	int		i;
	int		count;
	char	**c;

	i = 0;
	count = 0;
	while (d[count])
		count++;
	data->g_dd = malloc(count * sizeof(long int));
	if (!data->g_dd)
		return ;
	i = 0;
	while (d[i])
	{
		c = ft_split(d[i], ",");
		if (c[1])
			data->g_dd[i] = ft_strtol(c[1], 16);
		else
			data->g_dd[i] = 0xffffff;
		free_split(c);
		i++;
	}
}

void	init_map_vars(int *k, int *h, int *p)
{
	*k = 0;
	*h = 0;
	*p = 0;
}

void	handle_color_mode(t_data *data, int keycode)
{
	if (keycode == COLOR)
		data->kk = 1;
	else if (keycode == ANTI_COLOR)
		data->kk = 0;
}

void	help_read_map(int *fd, const char *filename, int *k, int *h)
{
	char	buf;

	*fd = open(filename, O_RDONLY);
	*k = 0;
	*h = 0;
	while (read(*fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			(*h)++;
		(*k)++;
	}
	close(*fd);
}
