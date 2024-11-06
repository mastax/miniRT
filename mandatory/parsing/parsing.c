/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:56:01 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/06 16:05:34 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void parse_light(t_scene *data, char **str) {
    if (data->l != NULL)
        report_error("Error only one light allowed\n");
    
    t_light *light = malloc(sizeof(t_light));
    if (!light)
        report_error("Error malloc failure in parse light\n");
    
    // next(str);
    light->next = NULL;
    light->o = parse_p3(str);
    light->ratio = stof(str);
    in_range(light->ratio, 0, 1, "light");
    light->color = parse_color(str);
    
    data->l = light;
}

void	parse_res(t_scene *data, char **str)
{
	if (data->res_init > 0)
		report_error("(R) can only be declared once in the scene\n");
	else
		data->res_init = 1;
	next(str);
	data->xres = stoi(str);
	in_range(data->xres, 1, INFINITY, "resolution");
	data->yres = stoi(str);
	in_range(data->yres, 1, INFINITY, "resolution");
}

void parse_mandatory(t_mlx *mlx, t_scene *scene, t_obj_array *obj_array, char **str) {
    char *ret = *str;
    
    if (*ret == 'R' && *(ret++))
        parse_res(scene, &ret);
    else if (*ret == 'A' && *(ret++))
        parse_ambient_light(scene, &ret);
    else if (*ret == 'C' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
        parse_camera(mlx, scene, &ret);
    else if (*ret == 'c' && *(ret + 1) == 'y' && *(ret++) && *(ret++))
        parse_cylinder(obj_array, &ret);
    else if (*ret == 'L' && (*(ret + 1) == 32 || *(ret + 1) == 9) && *(ret++))
        parse_light(scene, &ret);
    else if (*ret == 's' && *(ret + 1) == 'p' && *(ret++) && *(ret++))
        parse_sphere(obj_array, &ret);
    else if (*ret == 'p' && *(ret + 1) == 'l' && *(ret++) && *(ret++))
        parse_plane(obj_array, &ret);
        
    if (*ret != '\n')
        report_error("param not valid\n");
    *str = ret;
}

void parse_elements(t_mlx *mlx, t_scene *scene, t_obj_array *obj_array, char *str) {
    scene->res_init = 0;
    scene->al_init = 0;
    scene->c_init = 0;
    
    while (*str) {
        if (*str == '#') {
            while (*str && *str != '\n')
                str++;
        }
        else
            parse_mandatory(mlx, scene, obj_array, &str);
        str++;
    }
    
    if (scene->res_init == 0 || scene->al_init == 0 || mlx->cam == NULL)
        report_error("not enough elements to render a scene\n");
}

char	*line(char *str, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	char	*ptr;
	int		retrn;

	retrn = read(fd, buff, BUFFER_SIZE);
	while (retrn > 0)
	{
		ptr = str;
		buff[retrn] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
			return (NULL);
		free(ptr);
		retrn = read(fd, buff, BUFFER_SIZE);
	}
	return (str);
}

void parse_scene(t_mlx *mlx, t_scene *scene, t_obj_array *obj_array, char **av) {
    char *str;
    char *new_line;
    int fd;
    
    // Initialize the object array
    init_obj_array(obj_array, 10); // Start with capacity for 10 objects
    scene->l = NULL;
    mlx->cam = NULL;
    
    write(1, "Initiating parsing...\n", 21);
    str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
        report_error("Error in allocating memory\n");
    
    fd = open(av[1], 0);
    if (fd == -1)
        report_error("Error opening the file given\n");
    
    str = line(str, fd);
    new_line = ft_strjoin(str, "\n");
    free(str);
    
    parse_elements(mlx, scene, obj_array, new_line);
    free(new_line);
}