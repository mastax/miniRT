/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/01 16:06:07 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>

# define EPSILON 0.00001

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//=-=-=-=-=-=-VECTORS=-=-=-=-=-=-// PART1
double	v_magnitude_2(t_vec vector);
double	v_magnitude(t_vec vector);
t_vec	vec_plus(t_vec v1, t_vec v2);
t_vec	vec_plus_direct(t_vec v1, double x, double y, double z);
t_vec	vec_minus(t_vec v1, t_vec v2);
t_vec	vec_minus_direct(t_vec v1, double x, double y, double z);
t_vec	vec_multiplication_scale(t_vec v1, double m);
t_vec	vec_mutiplication_wise(t_vec v1, t_vec v2);
t_vec	vec_division(t_vec v1, double m);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);


#endif
