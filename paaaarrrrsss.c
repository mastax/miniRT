#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <math.h>

# define EPSILON 0.00001

//=-=-=-=-


typedef struct s_sphere
{
    t_vec   center;     // Center point
    double  diameter;   // Diameter
    int     color;      // RGB color
} t_sphere;

typedef struct s_plane
{
    t_vec   point;      // Point on plane
    t_vec   normal;     // Normal vector (normalized)
    int     color;      // RGB color
} t_plane;

typedef struct s_square
{
    t_vec   center;     // Center point
    t_vec   normal;     // Normal vector
    double  side;       // Side length
    int     color;      // RGB color
} t_square;

typedef struct s_cylinder
{
    t_vec   center;     // Center of the base
    t_vec   normal;     // Direction vector (normalized)
    double  diameter;   // Diameter
    double  height;     // Height
    int     color;      // RGB color
} t_cylinder;

typedef struct s_triangle
{
    t_vec   p1;         // First point
    t_vec   p2;         // Second point
    t_vec   p3;         // Third point
    int     color;      // RGB color
} t_triangle;

// Add this structure to manage all objects
typedef struct s_object
{
    int     type;       // Object type (SP, PL, CY, etc.)
    union u_figures fig;// Union of all possible figures
    struct s_object *next;  // Linked list of objects
} t_object;

// Object type identifiers
enum e_obj_type
{
    SP = 0,     // Sphere
    PL = 1,     // Plane
    SQ = 2,     // Square
    CY = 3,     // Cylinder
    TR = 4      // Triangle
};

//==-=-=-=-

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

void    parse_sphere(t_scene *scene, t_object **obj_list, char **tokens)
{
    t_object *new_obj;

    if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
        ft_err("Invalid sphere parameters!");
        
    new_obj = malloc(sizeof(t_object));
    if (!new_obj)
        ft_err("Memory allocation failed for sphere");
    
    new_obj->type = SP;
    new_obj->fig.sp.center = get_vec(tokens[1]);
    new_obj->fig.sp.diameter = ft_atod(tokens[2]);
    
    if (new_obj->fig.sp.diameter <= 0)
        ft_err("Sphere diameter must be positive");
        
    new_obj->fig.sp.color = get_color(tokens[3]);
    
    // Add to object list
    new_obj->next = *obj_list;
    *obj_list = new_obj;
}

void    parse_plane(t_scene *scene, t_object **obj_list, char **tokens)
{
    t_object *new_obj;

    if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
        ft_err("Invalid plane parameters!");
        
    new_obj = malloc(sizeof(t_object));
    if (!new_obj)
        ft_err("Memory allocation failed for plane");
    
    new_obj->type = PL;
    new_obj->fig.pl.point = get_vec(tokens[1]);
    new_obj->fig.pl.normal = get_vec(tokens[2]);
    
    // Validate normal vector
    if (new_obj->fig.pl.normal.x > 1 || new_obj->fig.pl.normal.y > 1 || 
        new_obj->fig.pl.normal.z > 1 || new_obj->fig.pl.normal.x < -1 || 
        new_obj->fig.pl.normal.y < -1 || new_obj->fig.pl.normal.z < -1)
        ft_err("Plane normal vector components must be in range [-1,1]");
        
    new_obj->fig.pl.color = get_color(tokens[3]);
    
    // Add to object list
    new_obj->next = *obj_list;
    *obj_list = new_obj;
}

void    parse_cylinder(t_scene *scene, t_object **obj_list, char **tokens)
{
    t_object *new_obj;

    if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || 
        !tokens[4] || !tokens[5] || tokens[6])
        ft_err("Invalid cylinder parameters!");
        
    new_obj = malloc(sizeof(t_object));
    if (!new_obj)
        ft_err("Memory allocation failed for cylinder");
    
    new_obj->type = CY;
    new_obj->fig.cy.center = get_vec(tokens[1]);
    new_obj->fig.cy.normal = get_vec(tokens[2]);
    
    // Validate normal vector
    if (new_obj->fig.cy.normal.x > 1 || new_obj->fig.cy.normal.y > 1 || 
        new_obj->fig.cy.normal.z > 1 || new_obj->fig.cy.normal.x < -1 || 
        new_obj->fig.cy.normal.y < -1 || new_obj->fig.cy.normal.z < -1)
        ft_err("Cylinder normal vector components must be in range [-1,1]");
    
    new_obj->fig.cy.diameter = ft_atod(tokens[3]);
    new_obj->fig.cy.height = ft_atod(tokens[4]);
    
    if (new_obj->fig.cy.diameter <= 0 || new_obj->fig.cy.height <= 0)
        ft_err("Cylinder diameter and height must be positive");
        
    new_obj->fig.cy.color = get_color(tokens[5]);
    
    // Add to object list
    new_obj->next = *obj_list;
    *obj_list = new_obj;
}

// Update the main parse_line function to include the new objects:
void parse_line(char *id, char **tokens, t_scene *scene, t_cam **cam, t_object **obj_list)
{
    if (id[0] == 'A' && id[1] == '\0')
        parse_ambient(scene, tokens);
    else if (id[0] == 'C' && id[1] == '\0')
        parse_camera(scene, cam, tokens);
    else if (id[0] == 'L' && id[1] == '\0')
        parse_light(scene, tokens);
    else if (id[0] == 's' && id[1] == 'p' && id[2] == '\0')
        parse_sphere(scene, obj_list, tokens);
    else if (id[0] == 'p' && id[1] == 'l' && id[2] == '\0')
        parse_plane(scene, obj_list, tokens);
    else if (id[0] == 'c' && id[1] == 'y' && id[2] == '\0')
        parse_cylinder(scene, obj_list, tokens);
    else
        ft_err("Invalid identifier");
}

// And update the main parse function:
void parse(t_scene *scene, t_cam **cam, t_object **obj_list, int fd)
{
    char **tokens;
    
    // Initialize scene
    scene->res_init = 0;
    scene->cam_nb = 0;
    scene->l = NULL;
    scene->al_init = 0;
    scene->bgr = 0;
    *obj_list = NULL;  // Initialize object list
    
    while (1)
    {
        tokens = ft_split(gnl(fd), ' ');
        if (!tokens)
            break;
        if (*tokens)
            parse_line(*tokens, tokens, scene, cam, obj_list);
        free_split(tokens);
    }
    close(fd);
    
    if (!scene->al_init || !scene->cam_nb)
        ft_err("Missing required elements (ambient light or camera)");
}


//=-=-=-=-=-=--=-

// New structure to hold all parsing context
typedef struct s_parse_ctx
{
    t_scene     *scene;
    t_cam       **cam;
    t_object    **obj_list;
} t_parse_ctx;

// Helper function to validate vector normalization
static int is_normalized_vector(t_vec v)
{
    double magnitude;
    
    magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (fabs(magnitude - 1.0) < EPSILON);
}

// Helper function to validate vector components are in [-1,1]
static int is_valid_direction(t_vec v)
{
    return (v.x >= -1 && v.x <= 1 && 
            v.y >= -1 && v.y <= 1 && 
            v.z >= -1 && v.z <= 1 &&
            !(v.x == 0 && v.y == 0 && v.z == 0));
}

void parse_ambient(t_parse_ctx *ctx, char **tokens)
{
    double ratio;
    
    if (!tokens || !tokens[1] || !tokens[2] || tokens[3])
        ft_err("Ambient lighting requires exactly 3 parameters");
    if (ctx->scene->al_init)
        ft_err("Duplicate ambient lighting definition");
    ratio = ft_atod(tokens[1]);
    if (ratio < 0.0 - EPSILON || ratio > 1.0 + EPSILON)
        ft_err("Ambient lighting ratio must be between 0.0 and 1.0");
    ctx->scene->ambient_light = ratio;
    ctx->scene->al_color = get_color(tokens[2]);
    ctx->scene->al_init = 1;
}

void parse_camera(t_parse_ctx *ctx, char **tokens)
{
    t_cam *new_cam;
    t_vec orientation;
    
    if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
        ft_err("Camera requires exactly 4 parameters");
    if (!(new_cam = (t_cam *)malloc(sizeof(t_cam))))
        ft_err("Memory allocation failed for camera");
    new_cam->o = get_vec(tokens[1]);
    orientation = get_vec(tokens[2]);
    if (!is_valid_direction(orientation))
        ft_err("Camera orientation must be a normalized vector");
    new_cam->nv = orientation;
    new_cam->fov = ft_atoi(tokens[3]);
    if (new_cam->fov < 0 || new_cam->fov > 180)
        ft_err("Camera FOV must be between 0 and 180 degrees");
    new_cam->idx = ctx->scene->cam_nb++;
    new_cam->img_ptr = NULL;
    new_cam->px_img = NULL;
    new_cam->next = *(ctx->cam);
    *(ctx->cam) = new_cam;
}

void parse_light(t_parse_ctx *ctx, char **tokens)
{
    t_light *new_light;
    t_light *last;
    
    if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
        ft_err("Light requires exactly 4 parameters");
    if (!(new_light = (t_light *)malloc(sizeof(t_light))))
        ft_err("Memory allocation failed for light");
    new_light->o = get_vec(tokens[1]);
    new_light->br = ft_atod(tokens[2]);
    if (new_light->br < 0.0 || new_light->br > 1.0)
        ft_err("Light brightness must be between 0.0 and 1.0");
    new_light->color = get_color(tokens[3]);
    new_light->next = NULL;
    if (!ctx->scene->l)
        ctx->scene->l = new_light;
    else
    {
        last = ctx->scene->l;
        while (last->next)
            last = last->next;
        last->next = new_light;
    }
}

void parse_shapes(t_parse_ctx *ctx, char **tokens)
{
    if (!tokens[0])
        return ;
    if (strcmp(tokens[0], "sp") == 0)
        parse_sphere(ctx->obj_list, tokens);
    else if (strcmp(tokens[0], "pl") == 0)
        parse_plane(ctx->obj_list, tokens);
    else if (strcmp(tokens[0], "cy") == 0)
        parse_cylinder(ctx->obj_list, tokens);
    else
        ft_err("Unknown shape identifier");
}

void parse_line(char *line, t_parse_ctx *ctx)
{
    char **tokens;

    if (!line || !line[0])
        return ;
    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0])
    {
        free_split(tokens);
        return ;
    }
    if (tokens[0][0] == 'A')
        parse_ambient(ctx, tokens);
    else if (tokens[0][0] == 'C')
        parse_camera(ctx, tokens);
    else if (tokens[0][0] == 'L')
        parse_light(ctx, tokens);
    else if (tokens[0][0] != '#')  // Skip comments
        parse_shapes(ctx, tokens);
    free_split(tokens);
}

void parse(t_scene *scene, t_cam **cam, t_object **obj_list, int fd)
{
    char *line;
    t_parse_ctx ctx;

    // Initialize context
    ctx.scene = scene;
    ctx.cam = cam;
    ctx.obj_list = obj_list;
    
    // Initialize scene
    scene->res_init = 0;
    scene->cam_nb = 0;
    scene->l = NULL;
    scene->al_init = 0;
    scene->bgr = 0;
    *obj_list = NULL;
    *cam = NULL;
    
    // Parse file
    while ((line = gnl(fd)) != NULL)
    {
        parse_line(line, &ctx);
        free(line);
    }
    
    // Validate required elements
    if (!scene->al_init)
        ft_err("Missing ambient lighting");
    if (scene->cam_nb == 0)
        ft_err("Missing camera");
    close(fd);
}

=-=-=-==-ATOD:

static void	skip_whitespace(char **s)
{
	while (**s == ' ' || (**s >= '\t' && **s <= '\r'))
	{
		(*s)++;
	}
}

static double	atod_postdecimal(const char *s)
{
	double		res;
	double		div;

	res = 0.0;
	div = 1.0;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10.0;
		div *= 10.0;
		res += (double)(*s - '0');
		s++;
	}
	res /= div;
	return (res);
}

double	ft_atod(const char *s)
{
	double	res;
	int		is_nega;

	skip_whitespace((char **)&s);
	is_nega = 0;
	if (*s == '-')
	{
		is_nega = 1;
		s++;
	}
	else if (*s == '+')
		s++;
	res = 0.0;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10.0;
		res += (double)(*s - '0');
		s++;
	}
	if (*s == '.')
		res += atod_postdecimal(s + 1);
	if (is_nega)
		res = -res;
	return (res);
}

//=-=-=-=-=-SPLIT


static int	count(char const *s, char c)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (s[x])
	{
		if (s[x] != c)
			count++;
		while (s[x] != c && s[x])
			x++;
		if (s[x])
			x++;
	}
	return (count);
}

static int	len_wor(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			word++;
			i++;
		}
		return (word);
	}
	return (0);
}

static char	**ft_free(char **res)
{
	int	i;

	i = 0;
	if (res)
	{
		while (res[i])
		{
			free(res[i]);
			i++;
		}
		free(res);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		y;

	y = 0;
	if (!s)
		return (NULL);
	res = ft_calloc(count(s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			res[y] = ft_substr(s, 0, len_wor(s, c));
			if (!res[y])
				return (ft_free(res));
			s += len_wor(s, c);
			y++;
		}
		else
			s++;
	}
	res[y] = NULL;
	return (res);
}

