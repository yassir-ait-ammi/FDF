/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:23:13 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 19:28:31 by yaait-am         ###   ########.fr       */
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
