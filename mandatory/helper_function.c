/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:23:13 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/31 21:14:04 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parsing_the_map(int ac, char **av, t_data *data, long int **g_dd)
{
	char	buf;
	int		fd;

	if (ac != 2)
	{
		printf("Usage: ./fdf <file map name>\n");
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		cleanup(data, g_dd);
		exit(1);
	}
	if (read(fd, &buf, 1) == 0)
	{
		printf("Error :invalid map\n");
		cleanup(data, g_dd);
		exit(1);
	}
	close(fd);
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

void	ft_help_read(int ***map, char ***d, int line_size)
{
	int	fd;
	int	h;
	int	k;

	fd = 0;
	h = 0;
	k = 0;
	while ((*d)[fd])
	{
		(*map)[k][h] = ft_strtol((*d)[fd], 10);
		h++;
		if (h == line_size)
		{
			h = 0;
			k++;
		}
		fd++;
	}
}

void	adjust_scale(t_p *p)
{
	if (p->scale > 20)
		p->scale = 15;
	else if (p->scale == 5)
		p->scale = 3;
	else
		p->scale = 1;
}

void	calculate_grid_params(t_cord **main, t_p *p)
{
	p->scale_x = (WINDOW_SIZE / (*main)->line_size);
	p->scale_y = (WINDOW_SIZE / (*main)->line);
	if (p->scale_x < p->scale_y)
		p->scale = p->scale_x;
	else
		p->scale = p->scale_y;
	p->grid_center_x = ((*main)->line_size - 1) / 2;
	p->grid_center_y = ((*main)->line - 1) / 2;
	adjust_scale(p);
}
