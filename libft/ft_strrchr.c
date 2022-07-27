/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:10:04 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/11/23 20:10:45 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	i = -1;
	last = NULL;
	while (s[++i])
		if (s[i] == (char)c)
			last = ((char *)s) + i;
	if (s[i] == (char)c)
		last = ((char *)s) + i;
	return (last);
}
