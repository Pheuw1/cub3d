/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_from_strarr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:29:30 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:30:15 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_remove_from_strarr(char **strings, int idx)
{
	int		j;
	int		i;
	char	**ret;

	if (ft_strarrsize(strings) < idx)
		return (NULL);
	ret = (char **)malloc((ft_strarrsize(strings)) * sizeof(char *));
	i = -1;
	j = -1;
	while (++i < ft_strarrsize(strings))
		if (i != idx)
			ret[++j] = ft_strdup(strings[i]);
	ret[j + 1] = NULL;
	ft_freepp((void *)strings);
	return (ret);
}
