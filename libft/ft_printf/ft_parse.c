/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:42:01 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/12/09 17:42:40 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fct_ptr	find_func(char c, t_print *tab, int i)
{
	i = -1;
	while (tab->specifiers[++i])
	{
		if (c == tab->specifiers[i])
		{
			if (!i)
				return (tab->ft_print_putchar);
			else if (i == 1)
				return (tab->ft_print_putstr);
			else if (i == 2)
				return (tab->ft_print_putptr);
			else if (i == 3 || i == 4)
				return (tab->ft_print_putnbr);
			else if (i == 5)
				return (tab->ft_print_u_putnbr);
			else if (i == 6)
				return (tab->ft_print_puthex_lower);
			else if (i == 7)
				return (tab->ft_print_puthex_upper);
			else if (i == 8)
				return (tab->ft_write_percent);
		}
	}
	return (NULL);
}

int	find_flags(char c, t_print *tab)
{
	if (c == '-')
		tab->minus = 1;
	else if (c == '0')
		tab->zero = 1;
	else if (c == '#')
		tab->hashtag = 1;
	else if (c == ' ')
		tab->space = 1;
	else if (c == '+')
		tab->plus = 1;
	else
		return (0);
	return (1);
}

int	width(char *n, t_print *tab)
{
	int	nbr;
	int	i;

	i = 0;
	nbr = 0;
	while (n[i] >= '0' && n[i] <= '9')
	{
		nbr = nbr * 10 + n[i] - '0';
		i++;
	}
	tab->width = nbr;
	return (i);
}

int	precision(char *prec, t_print *tab)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	if (prec[i] == '.')
	{
		tab->dot = 1;
		i++;
		while (prec[i] >= '0' && prec[i] <= '9')
		{
			nbr = nbr * 10 + prec[i] - '0';
			i++;
		}
		tab->prec = nbr;
	}
	return (i);
}
