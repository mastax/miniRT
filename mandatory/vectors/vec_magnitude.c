/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_magnitude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:07:23 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/02 09:59:03 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vec_mutiplication_wise(t_vec v1, t_vec v2)/*multiplication*/
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

t_vec	vec_division(t_vec v1, double m)/*div*/
{
	v1.x *= 1 / m;
	v1.y *= 1 / m;
	v1.z *= 1 / m;
	return (v1);
}

double	v_magnitude_2(t_vec vector)
{
	return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

double	v_magnitude(t_vec vector)
{
	return (sqrt(v_magnitude_2(vector)));
}

bool	equal(double a, double b)//from the book for exactly calculation
{
	return (fabs(a - b) < EPSILON);
}
