/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:03:37 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/11/27 14:03:33 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*reverse(char *out, int len)
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

char	*relou(int n)
{
	char	*out;
	char	*tmp;	
	int		i;

	i = -1;
	tmp = "-2147483648";
	if (n == -2147483648)
		out = (char *)malloc(sizeof(char) * 12);
	else
		out = (char *)malloc(sizeof(char) * 2);
	if (!out)
		return (NULL);
	if (n == -2147483648)
	{
		while (++i < 11)
			out[i] = tmp[i];
		out[i] = 0;
	}
	else
	{
		out[0] = '0';
		out[1] = 0;
	}
	return (out);
}

char	*nlen(char *out, int n)
{
	int	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	out = (char *)malloc(sizeof(char) * (i + 1));
	return (out);
}

char	*ft_itoa(int n)
{
	char	*out;
	int		sign;
	int		i;

	if (n == -2147483648 || n == 0)
		return (relou(n));
	out = NULL;
	out = nlen(out, n);
	if (!out)
		return (NULL);
	i = -1;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		n *= -1;
	}
	while (n)
	{
		out[++i] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		out[++i] = '-';
	return (reverse(out, i + 1));
}
