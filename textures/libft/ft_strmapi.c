/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:04:59 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/11/24 17:34:36 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	i = 0;
	res = (char *) malloc((ft_strlen((char *) s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	else
	{
		while (s[i])
		{
			res[i] = f(i, s[i]);
			i++;
		}
	}
	res[i] = 0;
	return (res);
}
