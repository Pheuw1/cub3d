/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:43:01 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:30:54 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
