/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:42:04 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/12/09 17:42:06 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev(char *out, int len)
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

//%[arg_index$][flags][width][.precision]conversion char
int	parse_fromat(char *f, t_print *tab)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	while (find_flags(f[i], tab))
		i++;
	i += width((char *) &f[i], tab);
	i += precision((char *) &f[i], tab);
	str = find_func(f[i++], tab, 0)(tab);
	len = ft_strlen(str);
	left_padding(&len, tab);
	zero_padding(len, tab);
	if (tab->dot && tab->is_str && ft_strlen(str) > (size_t)tab->prec)
		tab->tl += write(1, (char *)str, tab->prec);
	else
		tab->tl += write(1, (char *)str, ft_strlen(str));
	free(str);
	if (tab->minus && tab->is_char && !str[0])
		len++;
	if (tab->is_str && !str[0] && !tab->minus && !tab->dot && tab->width)
		tab->tl += write(1, " ", 1);
	right_padding(len, tab);
	reset_tab(tab);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	t_print	*tab;
	int		i;

	i = -1;
	tab = (t_print *) malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	init_tab(tab);
	va_start(tab->args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i += parse_fromat((char *) &format[i + 1], tab);
		}
		else
			tab->tl += write(1, &format[i], 1);
	}
	va_end(tab->args);
	i = tab->tl;
	destroy_tab(tab);
	return (i);
}
