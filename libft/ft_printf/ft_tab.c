/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:42:11 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/12/09 17:42:12 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_tab(t_print *tab)
{
	int	i;
	int	*set;

	i = -1;
	set = &(tab->tl) + 1;
	while (++i < 9)
		*(set + i) = 0;
	tab->is_str = 0;
	tab->is_char = 0;
}

void	destroy_tab(t_print *tab)
{
	free(tab->specifiers);
	free(tab->ptr_lowhex_set);
	free(tab->upphex_set);
	free(tab);
}

void	init_tab(t_print *tab)
{
	int	i;
	int	*set;

	i = -1;
	set = &(tab->tl);
	while (++i < 10)
		*(set + i) = 0;
	tab->ft_print_putstr = ft_print_putstr;
	tab->ft_print_putchar = ft_print_putchar;
	tab->ft_print_putptr = ft_print_putptr;
	tab->ft_print_putnbr = ft_print_putnbr;
	tab->ft_print_u_putnbr = ft_print_u_putnbr;
	tab->ft_print_puthex_lower = ft_print_puthex_lower;
	tab->ft_print_puthex_upper = ft_print_puthex_upper;
	tab->ft_write_percent = ft_write_percent;
	tab->specifiers = ft_strdup("cspdiuxX%");
	tab->ptr_lowhex_set = ft_strdup("0123456789abcdef");
	tab->upphex_set = ft_strdup("0123456789ABCDEF");
	tab->is_str = 0;
	tab->is_char = 0;
}
