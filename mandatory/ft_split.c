/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 08:21:42 by yaait-am          #+#    #+#             */
/*   Updated: 2025/02/02 11:46:33 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	check(char h, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (h == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !check(str[i], charset))
		i++;
	return (i);
}

int	count(char *str, char *charset)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check(str[i], charset))
			i++;
		if (str[i] != '\0')
			y++;
		while (str[i] != '\0' && !check(str[i], charset))
			i++;
	}
	return (y);
}

char	*ft_strdup(char *src, char *charset)
{
	char	*yas;
	int		i;
	int		sir;

	i = 0;
	sir = ft_strlen(src, charset);
	yas = malloc (sizeof(char) * (sir + 1));
	if (!yas)
		return (NULL);
	while (i < sir)
	{
		yas[i] = src[i];
		i++;
	}
	yas[i] = '\0';
	return (yas);
}

char	**ft_split(char *str, char *charset)
{
	char	**yas;
	int		i;
	int		j;

	i = 0;
	j = 0;
	yas = malloc(sizeof(char *) * (count(str, charset) + 1));
	if (!yas)
		return (NULL);
	while (str[j] != '\0')
	{
		while (str[j] != '\0' && check(str[j], charset))
			j++;
		if (str[j] != '\0')
		{
			yas[i] = ft_strdup(&str[j], charset);
			i++;
		}
		while (str[j] != '\0' && !check(str[j], charset))
			j++;
	}
	yas[i] = 0;
	return (yas);
}
