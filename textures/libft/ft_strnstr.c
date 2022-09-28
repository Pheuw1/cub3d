/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:05:07 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/02/24 17:26:54 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	o;

	i = 0;
	if (!ft_strlen(needle) || haystack == needle)
		return ((char *)haystack);
	while (haystack[i] && (i < len || len < 1))
	{
		o = 0;
		while ((i + o) < len && haystack[i + o] == needle[o]
			&& haystack[i + o] && needle[o])
			o++;
		if (o == ft_strlen(needle))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
