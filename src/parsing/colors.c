/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:43:16 by chchao            #+#    #+#             */
/*   Updated: 2022/09/30 16:39:49 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	encode_rgb(int red, int green, int blue)
{
	return ((red % 256) << 16 | (green % 256) << 8 | (blue % 256));
}

int	is_num(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	if (i > 3)
		return (0);
	return (1);
}

int	get_color(char *line)
{
	char	**tmp;
	int		vals[3];

	tmp = ft_split(line, " ,()\n");
	if (tmp && tmp[0] && tmp[1] && tmp[2] && !tmp[3]
		&& (is_num(tmp[0]) && is_num(tmp[1]) && is_num(tmp[2])))
	{
		vals[0] = ft_atoi(tmp[0]);
		vals[1] = ft_atoi(tmp[1]);
		vals[2] = ft_atoi(tmp[2]);
		ft_freepp((void *)tmp);
	}
	else
	{
		ft_freepp((void *)tmp);
		return (ft_error("cub3d", "invalid color or malloc fail", -1, NULL));
	}
	if ((vals[0] < 0 || vals[0] > 255) || (vals[1] < 0 || vals[1] > 255)
		|| (vals[2] < 0 || vals[2] > 255))
		return (ft_error("cub3d", "invalid color format", -1, NULL));
	return (encode_rgb(vals[0], vals[1], vals[2]));
}
