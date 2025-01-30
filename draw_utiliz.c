/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utiliz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:59:31 by yaait-am          #+#    #+#             */
/*   Updated: 2025/01/30 12:59:41 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_ternaries_1(int *a, int *b, int *x)
{
	if (*a > *b)
		*x = *a;
	else
		*x = *b;
}

void	ft_ternaries_2(int *a, int *b, int *x)
{
	if (*a < *b)
		*x = 1;
	else
		*x = -1;
}

void	ft_ternaries_3(int *a, int *b, float *x)
{
	if (*b == 0)
		*x = 0;
	else
		*x = (float)*a / *b;
}
