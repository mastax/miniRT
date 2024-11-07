/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:55 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/07 10:39:22 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_obj_array obj_array;
	// t_wrapper	wrapper[NUM_THREADS];
	t_mlx		mlx;
	t_scene		scene;
	// t_obj		*lst;

	if (ac < 2 || ac > 3)
		report_error("To run ./miniRT scenes/The scene \n");
	parse_scene(&mlx, &scene, &obj_array, av);
	return (0);
}