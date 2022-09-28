/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:41:52 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/04/09 17:55:58 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_write_percent(t_print *tab)
{
	tab->tl += 0;
	return (ft_strdup("%"));
}

char	*ft_print_putstr(t_print *tab)
{
	char	*s;

	tab->is_str = 1;
	s = (char *)va_arg(tab->args, char *);
	if (!s)
		return (ft_strdup("(null)"));
	return (ft_strdup(s));
}

char	*ft_print_putchar(t_print *tab)
{
	char	*s;
	char	c;

	tab->is_char = 1;
	c = (char)va_arg(tab->args, int);
	if (!c)
	{
		tab->tl += write(1, &c, 1);
		return (ft_strdup(""));
	}
	s = (char *)malloc(2 * sizeof(char));
	s[0] = c;
	s[1] = 0;
	return (s);
}
