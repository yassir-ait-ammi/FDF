/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:26:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/07 15:36:32 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	help_atoi(int sign)
{
	if (sign > 0)
		return (214748364);
	else
		return (-214748364);
}

int	ft_atoi(char *str)
{
	int		i;
	long	yas;
	int		sir;

	i = 0;
	sir = 1;
	yas = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sir = -sir;
		i++;
	}
	while (str[i] != '\0' && ('0' <= str[i] && str[i] <= '9'))
	{
		yas = (yas * 10 + (str[i] - 48));
		if (yas > 214748364)
			return (help_atoi(sir));
		i++;
	}
	return ((int)yas * sir);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	more_prs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i -= 3;
	if (str[i] != 'f')
		return (1);
	i--;
	if (str[i] != '.')
		return (1);
	if (i == 0)
		return (1);
	i--;
	if (str[i] == '/' && str[i + 1] == '.')
		return (1);
	return (0);
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cleanup(data);
	exit(0);
	return (0);
}
