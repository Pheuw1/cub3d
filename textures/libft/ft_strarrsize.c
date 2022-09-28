/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:30:24 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:30:36 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarrsize(char **strings)
{
	int	i;

	if (!strings)
		return (0);
	i = 0;
	while (strings && strings[i])
		i++;
	return (i);
}
