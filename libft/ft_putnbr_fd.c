/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:04:30 by gmehdevi          #+#    #+#             */
/*   Updated: 2021/11/24 17:34:35 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_digit_fd(int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	c = '0' + n % 10;
	if (n > 9)
	{
		put_digit_fd(n / 10, fd);
	}
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		put_digit_fd(n / 10, fd);
		write(fd, "8", 1);
	}
	else
		put_digit_fd(n, fd);
}
