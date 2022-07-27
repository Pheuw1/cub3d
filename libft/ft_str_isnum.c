/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:44:46 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/04/09 16:45:18 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isnum(const char *str)
{
	int	i;

	i = -1;
	if (!str || ft_atol(str) > (__INT_MAX__) || ft_atol(str) < (1 << 31))
		return (0);
	if (!(str[++i] == '+' || str[i] == '-')
		&& !((str[i] >= '0' && str[i] <= '9')))
		return (0);
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}
