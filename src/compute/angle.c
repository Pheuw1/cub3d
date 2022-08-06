/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:15:44 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/29 17:07:32 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

void	rot_vec(double *v, double a, double *res)
{
	double	tmp[2];

	tmp[0] = v[0];
	tmp[1] = v[1];
	res[0] = cos(a) * tmp[0] - sin(a) * tmp[1];
	res[1] = sin(a) * tmp[0] + cos(a) * tmp[1];
}

double	get_ord_angle(double *v1)
{
	double	unit_vector_1[2];
	double	unit_vector_2[2];
	int		sign;
	double	v2[2];

	v2[0] = 0;
	v2[1] = 1;
	if (hypot(v1[0], v1[1]) && hypot(v2[0], v2[1]))
	{
		vec_mult(v1, 1 / hypot(v1[0], v1[1]), unit_vector_1);
		vec_mult(v2, 1 / hypot(v2[0], v2[1]), unit_vector_2);
		if (vec_cross(v1, v2) < 0)
			return (-1 * acos(dot(unit_vector_1, unit_vector_2)));
		return (acos(dot(unit_vector_1, unit_vector_2)));
	}
	return (0);
}

double	get_abs_angle(double *v1)
{
	double	unit_vector_1[2];
	double	unit_vector_2[2];
	int		sign;
	double	v2[2];

	v2[0] = 1;
	v2[1] = 0;
	if (hypot(v1[0], v1[1]) && hypot(v2[0], v2[1]))
	{
		vec_mult(v1, 1 / hypot(v1[0], v1[1]), unit_vector_1);
		vec_mult(v2, 1 / hypot(v2[0], v2[1]), unit_vector_2);
		if (vec_cross(v1, v2) < 0)
			return (-1 * acos(dot(unit_vector_1, unit_vector_2)));
		return (acos(dot(unit_vector_1, unit_vector_2)));
	}
	return (0);
}

double	get_angle(double *v1, double *v2)
{
	double	unit_vector_1[2];
	double	unit_vector_2[2];
	int		sign;

	if (hypot(v1[0], v1[1]) && hypot(v2[0], v2[1]))
	{
		vec_mult(v1, 1 / hypot(v1[0], v1[1]), unit_vector_1);
		vec_mult(v2, 1 / hypot(v2[0], v2[1]), unit_vector_2);
		if (vec_cross(v1, v2) < 0)
			return (-1 * acos(dot(unit_vector_1, unit_vector_2)));
		return (acos(dot(unit_vector_1, unit_vector_2)));
	}
	return (0);
}

void	polar_to_cart(double *v, double *res)
{
	double	tmp[2];

	tmp[0] = v[0];
	tmp[1] = v[1];
	res[0] = tmp[0] * cos(tmp[1]);
	res[1] = tmp[0] * sin(tmp[1]);
}
