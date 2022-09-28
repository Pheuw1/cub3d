/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:43:16 by chchao            #+#    #+#             */
/*   Updated: 2022/09/28 14:10:31 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	encode_rgb(int red, int green, int blue)
{
	return ((red % 256) << 16 | (green % 256) << 8 | (blue % 256));
}

int	get_color(char *line)
{
	char	**tmp;
	int		vals[3];

	tmp = ft_split(line, " ,()\n");
	if (tmp && tmp[0] && tmp[1] && tmp[2] && !tmp[3])
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
