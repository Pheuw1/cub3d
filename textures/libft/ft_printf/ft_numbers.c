/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:41:57 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/12/09 17:42:35 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_print_putptr(t_print *tab)
{
	int				i;
	unsigned long	dec;
	char			out[20];

	i = -1;
	dec = va_arg(tab->args, unsigned long);
	while (dec > 15)
	{
		out[++i] = tab->ptr_lowhex_set[dec % 16];
		dec /= (unsigned long)16;
	}
	out[++i] = tab->ptr_lowhex_set[dec % 16];
	out[++i] = 'x';
	out[++i] = '0';
	out[++i] = 0;
	return (ft_strrev(ft_strdup(out), ft_strlen(out)));
}

char	*ft_print_putnbr(t_print *tab)
{
	int		n;

	n = va_arg(tab->args, int);
	if (n >= 0 && tab->sign)
		tab->sign = 1;
	else if (tab->sign)
		tab->sign = -1;
	return (ft_itoa(n));
}

char	*ft_print_u_putnbr(t_print *tab)
{
	unsigned int	n;

	n = va_arg(tab->args, unsigned int);
	tab->sign = 1;
	return (ft_itoa_u(n));
}

char	*ft_print_puthex_upper(t_print *tab)
{
	int				i;
	unsigned int	dec;
	char			out[11];

	i = -1;
	dec = va_arg(tab->args, unsigned int);
	while (dec > 15)
	{
		out[++i] = tab->upphex_set[dec % 16];
		dec = dec / 16;
	}
	out[++i] = tab->upphex_set[dec % 16];
	if (tab->hashtag && dec)
	{
		out[++i] = 'X';
		out[++i] = '0';
	}
	out[++i] = 0;
	return (ft_strrev(ft_strdup(out), ft_strlen(out)));
}

char	*ft_print_puthex_lower(t_print *tab)
{
	int				i;
	unsigned int	dec;
	char			out[9];

	i = -1;
	dec = va_arg(tab->args, unsigned int);
	while (dec > 15)
	{
		out[++i] = tab->ptr_lowhex_set[dec % 16];
		dec = dec / 16;
	}
	out[++i] = tab->ptr_lowhex_set[dec % 16];
	if (tab->hashtag && dec)
	{
		out[++i] = 'x';
		out[++i] = '0';
	}
	out[++i] = 0;
	return (ft_strrev(ft_strdup(out), ft_strlen(out)));
}
