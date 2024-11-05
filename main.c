/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:55 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/05 16:07:29 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	// t_wrapper	wrapper[NUM_THREADS];
	// t_mlx		mlx;
	t_scene		scene;
	t_obj		*lst;

	if (ac < 2 || ac > 3)
		error_message("To run ./miniRT scenes/The scene \n");
	parse_scene(&mlx, &scene, &lst, av);
	return (0);
}