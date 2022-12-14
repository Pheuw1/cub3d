/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:34:13 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:27:58 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int n)
{
	return (n * (((n > 0) << 1) - 1));
}

double	ft_abs_d(double d)
{
	if (d < 0)
		return (d * -1);
	return (d);
}
