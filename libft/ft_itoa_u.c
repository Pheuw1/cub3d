/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:37 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/11/27 16:13:16 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reverse(char *out, int len)
{
	int		i;
	char	tmp;

	i = -1;
	while (++i < len / 2)
	{
		tmp = out[i];
		out[i] = out[len - i - 1];
		out[len - i - 1] = tmp;
	}
	out[len] = '\0';
	return (out);
}

static char	*nlen(char *out, unsigned int n)
{
	int	i;

	if (!n)
	{
		out = (char *)malloc(sizeof(char) * (2));
		if (!out)
			return (NULL);
		return (out);
	}
	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	out = (char *)malloc(sizeof(char) * (i + 1));
	return (out);
}

char	*ft_itoa_u(unsigned int n)
{
	char	*out;
	int		i;

	out = NULL;
	out = nlen(out, n);
	if (!n)
	{
		out[0] = '0';
		out[1] = 0;
		return (out);
	}
	if (!out)
		return (NULL);
	i = -1;
	while (n)
	{
		out[++i] = (n % 10) + '0';
		n /= 10;
	}
	return (reverse(out, i + 1));
}
