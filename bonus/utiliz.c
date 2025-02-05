/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiliz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:42:04 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/05 15:54:56 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	handle_color_mode(t_data *data, int keycode)
{
	if (keycode == COLOR)
		data->kk = 1;
	else if (keycode == ANTI_COLOR)
		data->kk = 0;
}
