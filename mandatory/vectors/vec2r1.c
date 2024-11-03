/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2r1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:34:23 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/02 11:53:44 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_vec	normalise(t_vec v)
{
	t_vec	new;
	double	modulo;

	modulo = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	new.x = v.x / modulo;
	new.y = v.y / modulo;
	new.z = v.z / modulo;
	return (new);
}

double	vcos(t_vec x, t_vec y)
{
	return (vec_dot(x, y) / (mod(x) * mod(y)));
}

double	vsin(t_vec x, t_vec y)
{
	return (sqrt(1 - pow(vcos(x, y), 2)));
}

t_vec	scal_x_vec(double n, t_vec p)
{
	t_vec	v;

	v.x = n * p.x;
	v.y = n * p.y;
	v.z = n * p.z;
	return (v);
}
