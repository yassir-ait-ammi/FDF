/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:25:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 21:32:29 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_grid(t_cord **main)
{
	t_cord	*poi;
	t_cord	*sec;
	t_cord	*scal;
	t_cord	*cen;

	poi = malloc(sizeof(t_cord));
	poi->line = (*main)->line;
	poi->line_size = (*main)->line_size;
	ft_alloc(&poi, &sec, &scal, &cen);
	poi->g_dd = (*main)->g_dd;
	poi->image = (*main)->image;
	poi->map = (*main)->map;
	while (cen->y < poi->line)
	{
		cen->x = 0;
		while (cen->x++ < poi->line_size)
			ft_pass_to_draw(&sec, &poi, &cen, &scal);
		cen->y++;
	}
	free(poi);
	free(sec);
	free(scal);
	free(cen);
}

void	put_pix(t_cord **poi, t_cord **cen, t_cord **scal, t_cord **sec)
{
	(*poi)->x = (*cen)->x * (*scal)->z;
	(*poi)->y = (*cen)->y * (*scal)->z;
	isometric(&(*poi)->x, &(*poi)->y, (*sec)->z);
	(*poi)->x += (*cen)->z;
	(*poi)->y += (*cen)->color;
}

void	ft_help_print(t_cord **poi, t_cord **sec, t_cord **scal, t_cord **cen)
{
	(*sec)->x = (*cen)->x * (*scal)->z;
	(*sec)->y = ((*cen)->y + 1) * (*scal)->z;
	isometric(&(*sec)->x, &(*sec)->y, (*poi)->z);
	(*sec)->x += (*cen)->z;
	(*sec)->y += (*cen)->color;
}

void	ft_alloc(t_cord **poi, t_cord **sec, t_cord **scal, t_cord **cen)
{
	(*sec) = malloc(sizeof(t_cord));
	(*scal) = malloc(sizeof(t_cord));
	(*cen) = malloc(sizeof(t_cord));
	if (!*sec || !*scal || !*cen)
		return ;
	(*scal)->x = (1000 / (*poi)->line_size);
	(*scal)->y = (1000 / (*poi)->line);
	if ((*scal)->x < (*scal)->y)
		(*scal)->z = (*scal)->x;
	else
		(*scal)->z = (*scal)->y;
	(*cen)->x = ((*poi)->line_size - 1) / 2;
	(*cen)->y = 0;
	if ((*scal)->z > 20)
		(*scal)->z = 15;
	else if ((*scal)->z == 5)
		(*scal)->z = 3;
	else
		(*scal)->z = 1;
	(*scal)->color = ((*poi)->line - 1) / 2;
	(*poi)->x = (*cen)->x * (*scal)->z;
	(*poi)->y = (*scal)->color * (*scal)->z;
	isometric(&(*poi)->x, &(*poi)->y, 0);
	(*cen)->z = (WINDOW_SIZE / 2) - (*poi)->x;
	(*cen)->color = (WINDOW_SIZE / 2) - (*poi)->y;
}

void	ft_pass_to_draw(t_cord **sec, t_cord **poi, t_cord **cen, t_cord **scal)
{
	if ((*cen)->y >= (*poi)->line || (*cen)->x >= (*poi)->line_size)
		return ;
	(*sec)->z = (*poi)->map[(*cen)->y][(*cen)->x];
	(*poi)->color = (*(*poi)->g_dd)[(*cen)->y * (*poi)->line_size + (*cen)->x];
	put_pix(&(*poi), &(*cen), &(*scal), &(*sec));
	put_pixel_to_image((*poi)->image, (*poi)->x, (*poi)->y, (*poi)->color);
	if ((*cen)->x + 1 < (*poi)->line_size)
	{
		(*poi)->z = (*poi)->map[(*cen)->y][(*cen)->x + 1];
		ft_help_print(&(*poi), &(*sec), &(*scal), &(*cen));
		draw_line_image((*poi)->image, (*poi)->x, (*poi)->y, (*sec)->x, (*sec)->y, (*poi)->color, (*(*poi)->g_dd)[(*cen)->y * (*poi)->line_size + (*cen)->x + 1]);
	}
	if ((*cen)->y + 1 < (*poi)->line)
	{
		(*poi)->z = (*poi)->map[(*cen)->y + 1][(*cen)->x];
		ft_help_print(&(*poi), &(*sec), &(*scal), &(*cen));
		draw_line_image((*poi)->image, (*poi)->x, (*poi)->y, (*sec)->x, (*sec)->y, (*poi)->color, (*(*poi)->g_dd)[((*cen)->y + 1) * (*poi)->line_size + (*cen)->x]);
	}
}
