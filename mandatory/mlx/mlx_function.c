/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:58 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/08 17:09:24 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	init_mlx(t_mlx *mlx, t_scene *data)
{
	t_cam	*cam_begin;

	mlx->mlx = mlx_init();
	cam_begin = mlx->cam;
	mlx->begin = mlx->cam;
	while (mlx->cam)
	{
		mlx->cam->img_ptr = mlx_new_image(mlx->mlx, data->xres, data->yres);
		mlx->cam->px_img = (int *)mlx_get_data_addr(mlx->cam->img_ptr, \
			&mlx->cam->bits_per_pixel, &mlx->cam->size_line, &mlx->cam->endian);
		mlx->cam = mlx->cam->next;
	}
	mlx->cam = cam_begin;
}
int	next_cam(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		exit(0);
	if (keycode != 49)
		return (0);
	if (mlx->cam->next)
	{
		mlx->cam = mlx->cam->next;
		mlx_put_image_to_window(\
				mlx->mlx, mlx->win, mlx->cam->img_ptr, 0, 0);
	}
	else
	{
		mlx->cam = mlx->begin;
		mlx_put_image_to_window(\
				mlx->mlx, mlx->win, mlx->cam->img_ptr, 0, 0);
	}
	return (1);
}

int	close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

void	graphic_loop(t_mlx mlx, t_scene data)
{
	mlx.win = mlx_new_window(mlx.mlx, data.xres, data.yres, \
															"miniRT");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.cam->img_ptr, 0, 0);
	mlx_hook(mlx.win, 17, 131072, close_program, 0);
	mlx_hook(mlx.win, 2, 1, next_cam, &mlx);
	mlx_loop(mlx.mlx);
}