/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:21:28 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/06 15:49:36 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	parse_ambient_light(t_scene *data, char **str)
{
	if (data->al_init > 0)
		error_message("(A) can only be declared once in the scene\n");
	else
		data->al_init = 1;
	next(str);
	data->ambient_light = stof(str);
	in_range(data->ambient_light, 0, 1, "ambient lightning");
	data->al_color = parse_color(str);
}

void parse_sphere(t_obj_array *obj_array, char **str)
{
    t_obj obj;

    obj.flag = SP;
    next(str);
    obj.fig.sp.c = parse_p3(str);
    obj.fig.sp.r = stof(str) / 2;
    in_range(obj.fig.sp.r, 0, INFINITY, "sphere");
    obj.texture = stoi(str);
    in_range(obj.texture, 0, 5, "sphere");
    obj.color = parse_color(str);

    add_object(obj_array, obj);
}

int	parse_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	r |= stoi(str);
	in_range(r, 0, 255, "colors must be in range [0, 255],");
	r <<= 16;
	comma(str);
	g |= stoi(str);
	in_range(g, 0, 255, "colors must be in range [0, 255],");
	g <<= 8;
	comma(str);
	b |= stoi(str);
	in_range(b, 0, 255, "colors must be in range [0, 255],");
	return (r | g | b);
}