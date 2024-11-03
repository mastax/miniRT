/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/02 17:29:33 by elel-bah         ###   ########.fr       */
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

typedef struct s_mlx
{
    void *mlx;
    void *win;
    t_cam *cam;
    t_cam *begin;
}   t_mlx;

typedef struct s_cam
{
 int    idx;
 t_vec   o;
 t_vec   nv;
 int    fov;
 void   *img_ptr;
 int    *px_img;
 int    bits_per_pixel;
 int    size_line;
 int    endian;
 struct s_cam *next;
}   t_cam;

typedef struct s_resolution
{
	int	res_init;// Indicates whether the resolution has been initialized (1 for yes, 0 for no)
	int	xres;            // Width of the scene in pixels
    int	yres;            // Height of the scene in pixels
    int	cam_nb;          // Number of cameras in the scene
    t_light	*l;             // Pointer to a list of light sources in the scene
    int	al_init;         // Indicates whether ambient light has been initialized (1 for yes, 0 for no)
    double	ambient_light;   // Intensity of the ambient light
    int	al_color;        // Color of the ambient light (usually in RGB format)
    int    bgr;             // Background color of the scene
} t_scene;

typedef struct  s_light
{
 t_vec   o;
 double   br;
 int    color;
 struct s_light *next;
}     t_light;

union   u_figures
{
 t_sphere sp;
 t_plane  pl;
 t_square sq;
 t_cylinder cy;
 t_triangle tr;
};

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
//=-=-=-=-=-=-=-=COLORS=-=-=-=-=-=-=-
#endif
