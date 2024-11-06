/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/06 18:01:25 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>


# define EPSILON 0.00001

# define BUFFER_SIZE 32

# define SP 0
# define PL 1
# define CY 4
# define NUM_THREADS 4

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_cam
{
	int				idx;
	t_vec			o;
	t_vec			nv;
	int				fov;
	void			*img_ptr;
	int				*px_img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	struct s_cam	*next;
}					t_cam;
typedef struct s_mlx
{
	void *mlx;
	void *win;
	t_cam *cam;
	t_cam *begin;
}   t_mlx;


typedef struct s_sphere
{
	t_vec	c;
	double	r;
	int		inside;
}			t_sphere;

typedef struct s_plane
{
	t_vec	p;
}			t_plane;

typedef struct s_cylinder
{
	t_vec	c;
	t_vec	nv;
	double	r;
	double	h;
	double	dist1;
	double	dist2;
}			t_cylinder;

typedef struct s_light
{
	t_vec			o;
	double			br;
	int				color;
	double			ratio;
	struct s_light	*next;
}					t_light;

union	u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};
typedef struct s_obj
{
	int				flag;
	union u_figures	fig;
	int				color;
	int				texture;
	t_vec			normal;
	struct s_obj	*next;
}					t_obj;
// Structure definitions
typedef struct s_obj_array {
	int capacity;
	int count;
	t_obj *objects;
} t_obj_array;

typedef struct s_light_array {
	int capacity;
	int count;
	t_light *lights;
} t_light_array;


typedef struct s_scene
{
	int				res_init;
	int				xres;
	int				yres;
	int				cam_nb;
	t_light			*l;
	int				al_init;
	int				c_init;
	double			ambient_light;
	int				al_color;
	int				bgr;
}					t_scene;


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

t_vec	normalise(t_vec v);
double	vcos(t_vec x, t_vec y);
double	vsin(t_vec x, t_vec y);
t_vec	scal_x_vec(double n, t_vec p);
void	next(char **str);
void	in_range(double nb, double min, double max, char *function);
char	*line(char *str, int fd);

char	*ft_strjoin(char *s1, char *s2);

//=-=-=-=-=-=-=-=COLORS=-=-=-=-=-=-=-

void	color_definition(double red, double green, double blue, double color[3]);

//=-=-=-=-=-=-=-=-PARSING=-=-=-=-=-=-
void	report_error(char *str);
t_vec	parse_p3(char **str);
double	stof(char **str);
int	stoi(char **str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strcat(char *dest, char *src);

void    init_obj_array(t_obj_array *array, int initial_capacity);
void    add_object(t_obj_array *array, t_obj obj);
void    parse_plane(t_obj_array *array, char **str);
void    parse_cylinder(t_obj_array *array, char **str);
void    parse_camera(t_mlx *mlx, t_scene *data, char **str);
void    parse_light(t_scene *data, char **str);
void    parse_res(t_scene *data, char **str);
void    parse_mandatory(t_mlx *mlx, t_scene *scene, t_obj_array *obj_array, char **str);
void    parse_elements(t_mlx *mlx, t_scene *scene, t_obj_array *obj_array, char *str);
void    parse_scene(t_mlx *mlx, t_scene *scene, t_obj_array *obj_array, char **av);
void	parse_ambient_light(t_scene *data, char **str);
void	parse_sphere(t_obj_array *obj_array, char **str);
int	parse_color(char **str);

#endif
