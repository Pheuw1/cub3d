/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:51:04 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/04/09 18:33:18 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_print
{
	int		tl;
	int		width;
	int		prec;
	int		zero;
	int		dot;
	int		minus;
	int		plus;
	int		space;
	int		hashtag;
	int		sign;
	char	*(*ft_print_putstr)(struct s_print *);
	char	*(*ft_print_putchar)(struct s_print *);
	char	*(*ft_print_putptr)(struct s_print *);
	char	*(*ft_print_putnbr)(struct s_print *);
	char	*(*ft_print_u_putnbr)(struct s_print *);
	char	*(*ft_print_puthex_upper)(struct s_print *);
	char	*(*ft_print_puthex_lower)(struct s_print *);
	char	*(*ft_write_percent)(struct s_print *);
	va_list	args;
	char	*specifiers;
	char	*ptr_lowhex_set;
	char	*upphex_set;
	int		is_str;
	int		is_char;
}	t_print;

typedef char	*(*t_fct_ptr)(t_print *);
t_fct_ptr	find_func(char c, t_print *tab, int i);
void		reset_tab(t_print *tab);
void		destroy_tab(t_print *tab);
void		init_tab(t_print *tab);
char		*ft_print_putchar(t_print *tab);
char		*ft_print_putstr(t_print *tab);
char		*ft_print_putptr(t_print *tab);
char		*ft_print_putnbr(t_print *tab);
char		*ft_print_u_putnbr(t_print *tab);
char		*ft_print_puthex_lower(t_print *tab);
char		*ft_print_puthex_upper(t_print *tab);
char		*ft_write_percent(t_print *tab);
int			ft_printf(const char *format, ...);
int			find_flags(char c, t_print *tab);
int			width(char *n, t_print *tab);
int			precision(char *prec, t_print *tab);
void		left_padding(int *len, t_print *tab);
void		right_padding(int len, t_print *tab);
void		zero_padding(int len, t_print *tab);
char		*ft_strrev(char *out, int len);
#endif
