/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:07:15 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 18:35:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_get_value(char c, int base)
{
	char	*digits;
	int		i;

	digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	i = 0;
	while (i < base)
	{
		if (c == digits[i] || c == digits[i] + 32)
			return (i);
		i++;
	}
	return (-1);
}

long	help_strtol(const char *str, int base, int sign)
{
	long	result;
	int		value;

	result = 0;
	value = ft_get_value(*str, base);
	while (value != -1)
	{
		if (result > (LONG_MAX - value) / base)
		{
			if (sign == 1)
				result = LONG_MAX;
			else
				result = LONG_MIN;
			break ;
		}
		result = result * base + value;
		str++;
		value = ft_get_value(*str, base);
	}
	return (result);
}

long	ft_strtol(const char *str, int base)
{
	long	result;
	int		sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (base == 0)
	{
		if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
			base = 16;
		else if (*str == '0')
			base = 8;
		else
			base = 10;
	}
	if (base == 16 && *str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
		str += 2;
	result = help_strtol(str, base, sign);
	return (result * sign);
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cleanup(data, NULL);
	exit(0);
	return (0);
}

void	more_handel(int fd)
{
	char	buf;

	read(fd, &buf, 1);
	if (!(buf >= '0' && buf <= '9') && buf != '-' && buf != '+'
		&& buf != ' ' && buf != ',' && buf != '\n')
	{
		write(2, "Error : invalid map\n", 21);
		exit(1);
	}
}
