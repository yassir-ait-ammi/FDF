/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:31:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/06 19:02:27 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parsing_the_map(int ac, char **av, t_data *data, long int **g_dd)
{
	char	buf;
	int		fd;

	if (ac != 2)
	{
		write(2, "Usage: ./fdf <file map name>\n", 30);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error opening file\n", 20);
		cleanup(data, g_dd);
		exit(1);
	}
	prs_the_fd(av[1]);
	read(fd, &buf, 1);
	if (!(buf >= '0' && buf <= '9') && buf != '-' && buf != '+' && buf != ' ')
	{
		write(2, "Error : invalid map\n", 21);
		exit(1);
	}
	ft_handle_the_error(av[1], data);
	more_handel(fd);
	close(fd);
}

void	prs_the_fd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] != 'f')
	{
		write(2, "Error : invalid argument !!\n", 29);
		exit(1);
	}
	i--;
	if (str[i] != 'd')
	{
		write(2, "Error : invalid argument !!\n", 29);
		exit(1);
	}
	i--;
	if (more_prs(str))
	{
		write(2, "Error : invalid argument !!\n", 29);
		exit(1);
	}
}

int	ft_strlen_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_handle_the_error(char *filename, t_data *data)
{
	t_fd	fd;
	int		i;

	(void)data;
	help_read_map(&fd.fd, filename, &fd.k, &fd.h);
	fd.s = malloc(fd.k + 1);
	fd.fd = open(filename, O_RDONLY);
	fd.k = 0;
	while (read(fd.fd, &fd.s[fd.k], 1) > 0)
		fd.k++;
	fd.s[fd.k] = '\0';
	close(fd.fd);
	fd.d = ft_split(fd.s, " \n");
	i = ft_strlen_2(fd.d);
	if ((i % fd.h) || !ft_help_the_handle(fd.d))
	{
		free(fd.s);
		free_split(fd.d);
		write(2, "Error : invalid map\n", 21);
		exit(1);
	}
	free(fd.s);
	free_split(fd.d);
}

int	ft_help_the_handle(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != ','
			&& str[i][j] != '-' && str[i][j] != '+')
		{
			if (!(is_digit(str[i][j])))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
