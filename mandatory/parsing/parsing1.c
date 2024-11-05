/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:29 by elel-bah          #+#    #+#             */
/*   Updated: 2024/11/05 17:26:40 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// Helper functions for array management
void init_obj_array(t_obj_array *array, int initial_capacity)
{
    array->capacity = initial_capacity;
    array->count = 0;
    array->objects = malloc(sizeof(t_obj) * initial_capacity);
    if (!array->objects)
        report_error("Error malloc failure in object array initialization\n");
}

void add_object(t_obj_array *array, t_obj obj) {
    if (array->count >= array->capacity) {
        array->capacity *= 2;
        t_obj *new_array = realloc(array->objects, sizeof(t_obj) * array->capacity);
        if (!new_array)
            report_error("Error realloc failure in add_object\n");
        array->objects = new_array;
    }
    array->objects[array->count++] = obj;
}

void parse_plane(t_obj_array *array, char **str) {
    t_obj obj;
    
    obj.flag = PL;
    next(str);
    obj.fig.pl.p = parse_p3(str);
    obj.normal = normalise(parse_p3(str));
    obj.texture = 0;
    obj.color = parse_color(str);
    
    add_object(array, obj);
}

void parse_cylinder(t_obj_array *array, char **str) {
    t_obj obj;
    
    obj.flag = CY;
    next(str);
    obj.fig.cy.c = parse_p3(str);
    obj.fig.cy.nv = normalize(parse_p3(str));
    obj.fig.cy.r = stof(str) / 2;
    in_range(obj.fig.cy.r, 0, INFINITY, "cylinder");
    obj.fig.cy.h = stof(str);
    in_range(obj.fig.cy.h, 0, INFINITY, "cylinder");
    obj.texture = 0;
    obj.color = parse_color(str);
    
    add_object(array, obj);
}

void parse_camera(t_mlx *mlx, t_scene *data, char **str) {
    if (data->c_init > 0)
        report_error("(C) can only be declared once in the scene\n");
    
    data->c_init = 1;
    t_cam cam;
    
    next(str);
    data->cam_nb = 0; // Since we're only using one camera
    cam.o = parse_p3(str);
    cam.nv = normalise(parse_p3(str));
    cam.fov = stoi(str);
    in_range(cam.fov, 0, 180, "camera");
    
    mlx->cam = malloc(sizeof(t_cam));
    if (!mlx->cam)
        report_error("Error malloc failure in camera allocation\n");
    *mlx->cam = cam;
}