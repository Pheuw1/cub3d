/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:09:07 by chchao            #+#    #+#             */
/*   Updated: 2022/09/29 15:58:51 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	vec_equal(double *v1, double *v2)
{
	v1[0] = v2[0];
	v1[1] = v2[1];
}

int	m_x(t_map *map, char *file)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(file, "/n");
	if (!split)
	{
		ft_freepp((void *)split);
		return (ft_error("cub3d", "malloc failed", -1, NULL));
	}
	while (split[++i])
		map->m_x = ft_max(ft_strlen(split[i]), map->m_x);
	ft_freepp((void *)split);
	return (0);
}

int	valid_size(t_map *map, char *file)
{
	int	i;
	int	len;
	int	pos;

	len = 0;
	pos = 0;
	while (file && file[++i])
	{
		if (file[i] == '\n' && ++map->m_y)
			map->m_x = ft_max(map->m_x, len);
		if (file[i] == '\n')
			len = -1;
		if (file[i] == 'N' || file[i] == 'S' || file[i] == 'W'
			|| file[i] == 'E')
			pos++;
		else if (file[i] == ' ')
			file[i] = '0';
		else if (file[i] != '0' && file[i] != '1' && file[i] != '\n')
			return (ft_error("cub3d", "invalid map format", -1, file));
		len++;
	}
	map->m_y++;
	if (pos < 1 || pos > 1)
		return (ft_error("cub3d", "can only 1 player in map", -1, file));
	return (0);
}

//dfs serche
int	search(t_map *map, int **vis, int x, int y)
{
	if (vis[x][y] || map->layout[x][y])
		return (0);
	vis[x][y] = 1;
	if (!((x + 1) < map->m_x) || !((x - 1) >= 0) || !((y + 1) < map->m_y)
		|| !((y - 1) >= 0))
		return (-1);
	if ((search(map, vis, x + 1, y)) || (search(map, vis, x - 1, y))
		|| (search(map, vis, x, y + 1)) || (search(map, vis, x, y - 1)))
		return (-1);
	return (0);
}

int	break_free(t_map *map)
{
	int	i;
	int	j;
	int	**vis;
	int	ret;

	vis = (int **)malloc(map->m_x * sizeof(int *));
	i = -1;
	while (++i < map->m_x)
		vis[i] = (int *)malloc(map->m_y * sizeof(int));
	i = -1;
	j = -1;
	while (++i < map->m_x)
	{
		j = -1;
		while (++j < map->m_y)
			vis[i][j] = 0;
	}
	ret = search(map, vis, map->c_pos[0], -map->c_pos[1]);
	i = -1;
	while (++i < map->m_x)
		free(vis[i]);
	free(vis);
	return (ret);
}
