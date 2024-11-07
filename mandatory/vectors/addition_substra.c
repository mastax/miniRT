/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_substra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:08:57 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/07 10:26:30 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"


t_vec	vec_plus(t_vec v1, t_vec v2)/*addition*/
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vec	vec_plus_direct(t_vec v1, double x, double y, double z)/*addition*/
{
	v1.x += x;
	v1.y += y;
	v1.z += z;
	return (v1);
}

t_vec	vec_minus(t_vec v1, t_vec v2)/*substaction*/
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vec	vec_minus_direct(t_vec v1, double x, double y, double z)/*substraction*/
{
	v1.x -= x;
	v1.y -= y;
	v1.z -= z;
	return (v1);
}

t_vec	vec_multiplication_scale(t_vec v1, double m)
{
	v1.x *= m;
	v1.y *= m;
	v1.z *= m;
	return (v1);
}
