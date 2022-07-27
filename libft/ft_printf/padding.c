/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:47:41 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/12/09 17:47:42 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	left_padding(int *len, t_print *tab)

{
	if (!tab->minus && !tab->zero && !tab->is_str && !tab->is_char)
		while (tab->width-- - tab->prec >= *len + tab->plus)
			tab->tl += write(1, " ", 1);
	if (tab->plus && tab->sign > -1)
	{
		tab->tl += write(1, "+", 1);
		(*len)++;
	}
	if (!tab->plus && tab->sign > -1 && tab->space)
	{
		tab->tl += write(1, " ", 1);
		(*len)++;
	}
	if (tab->sign == -1)
	{
		tab->tl += write(1, "-", 1);
		(*len)++;
	}
}

void	zero_padding(int len, t_print *tab)
{
	int	precision;

	precision = tab->prec;
	if (tab->dot)
	{
		if (!tab->is_str)
		{
			precision += (tab->sign == -1);
			while (--precision >= len)
				tab->tl += write(1, "0", 1);
		}
	}
	if (!tab->minus && tab->zero)
		while (--tab->width - tab->prec >= len + tab->plus)
			tab->tl += write(1, "0", 1);
}

void	right_padding(int len, t_print *tab)
{
	if (tab->width > len && tab->minus)
		while (tab->width-- - tab->prec >= len + tab->plus + 1)
			tab->tl += write(1, " ", 1);
}
