/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:32:03 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 11:39:32 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

# define PI 3.14159265359

# define EXIT		53
# define ROT_LEFT	123
# define ROT_RIGHT	124
# define FORWARD	13
# define BACK		1
# define RIGHT		2
# define LEFT		0

# define HUD_HEIGHT 300
# define PIXL_SIZE 15
# define MAP_MARGIN 30

# define BLACK  0x000000
# define WHITE  0xFFFFFF
# define GREEN  0x00FF00
# define RED  0xFF0000
# define BLUE  0x3333ff
# define AZUR 0x0ae0f1
# define VIOLET 0xfa00e4

typedef enum e_bool	t_bool;
enum	e_bool
{
	false,
	true
};

typedef enum e_type	t_type;
enum	e_type
{
	color,
	path
};

typedef struct s_overlay	t_overlay;
struct	s_overlay
{
	t_type	type;
	t_bool	checked;
	char	*address;
	int		r;
	int		g;
	int		b;
	int		color;
};

typedef struct s_position	t_position;
struct	s_position
{
	double	x;
	double	y;
	float	a;
};

typedef struct s_ray	t_ray;
struct	s_ray
{
	double	movespeed;
	double	rotspeed;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	camera_x;
	int		map_x;
	int		map_y;

	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		wallcolor;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		pix_line;

	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;

	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;

	int		p;
	float	pos_z;
	float	row_distance;
};

typedef struct s_key	t_key;
struct	s_key
{
	int					forward;
	int					back;
	int					left;
	int					right;
	int					rot_left;
	int					rot_right;
};

typedef struct s_img	t_img;
struct	s_img
{
	void				*mlx_img;
	int					*addr;
	char				*addr_c;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
};

typedef struct s_text	t_text;
struct	s_text
{
	int		ref;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
};

typedef struct s_sprite	t_sprite;
struct	s_sprite
{
	int			n;
	t_position	*coord;
	int			*order;
	double		*dist;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_end_x;
	int			sprite_width;
	double		*z_buffer;
};

typedef struct s_state	t_state;
struct	s_state
{
	void		*mlx;
	void		*win;
	char		**map;
	int			screen_width;
	int			screen_height;
	char		init_cardinal;
	int			pixel_size;
	int			hud_height;
	int			hud_margin;
	int			heart_ratio;
	t_bool		save;

	int			win_width;
	int			win_height;
	int			map_width;
	int			map_height;

	int			life;
	t_position	player_coord;
	t_ray		ray;
	t_key		key;
	t_img		img;
	t_img		img2;
	t_img		texture[8];
	t_text		t;
	t_sprite	s;

	int			fd;
	char		*str;
	char		**tab;
	t_overlay	no;
	t_overlay	so;
	t_overlay	ea;
	t_overlay	we;
	t_overlay	sp;
	t_overlay	f;
	t_overlay	c;
};

typedef struct s_fig	t_fig;
struct	s_fig
{
	int	x;
	int	y;
	int	size;
	int	color;
	int	drawstart;
	int	drawend;
};

char	**array_generator(t_state *state);
void	display_map(char **arr);
int		find_index(char c, char *set);
int		set_player_coord(char **map, t_position *coord, t_state *state);
void	map_floodfill(char **map, int x, int y, t_bool *unvalidated_map);
t_bool	cardinal_occurence(char **map);
t_bool	valid_symbol(char **map);
int		map_validation(char **map, t_state *state);
void	free_map(char **arr);

void	verline(t_state *state, t_fig fig);

void	draw_square(t_state *state, t_fig fig);
void	draw_map(t_state *state, int x, int y);

int		key_press(int keycode, t_state *state);
int		key_release(int keycode, t_state *state);

void	process_wall(t_state *state);
void	life_absorber(t_state *state);
void	render_graphic(t_state *state);
int		game_process(t_state *state);

void	longitdinal_move(t_state *state);
void	horizontal_move(t_state *state);
void	rotation_move(t_state *state);
void	display_state(t_state *state);

void	init_key(t_state *state);
void	init_ray(t_state *state);
void	init_ray_2(t_state *state);

void	ft_stepside_dist(t_state *state);
void	ft_incrementray(t_state *state);
void	ft_draw_start_end(t_state *state);
void	ft_line_render(int x, t_state *state);
void	display_state(t_state *state);

void	img_pix_put(t_img *img, int x, int y, int color);
void	draw_pix(t_state *state, int x, int y, int color);
void	draw_heart(t_state *state, int x, int y);

void	ft_init_texture(t_state *state);
void	op_skyfloor_1(t_state *state, int y);
void	op_skyfloor_2(t_state *state, t_img texture);
void	draw_wall(t_state *state, int x, int y);
void	draw_sky_floor(t_state *state, t_img texture, int choice);
void	draw_sky(t_state *state, t_img texture);
void	fill_color(t_state *state, t_overlay *overlay, int choice);

void	get_sprite_number(t_state *state);
void	set_sprites(t_state *state, int n);
void	set_dist_order2(t_state *state);
void	set_dist_order(t_state *state);
void	init_sprite(t_state *state);
void	sprite_operation(t_state *state, int i);
void	draw_sprite(t_state *state, int y, int texx, int stripe);
void	ft_sprite(t_state *state);

void	save(t_state *state);

void	draw_life(t_state *state);

void	global_free(t_state *state);
void	destroy_images(t_state *state);
void	destroy_overlay(t_state *state);
void	exit_process(t_state *state, t_bool error);

void	cub_3d(t_state *state);
void	init_parser(t_state *state);

void	set_resolution(t_state *state, char *str);
void	file_parser(t_state *state, char *path);
void	free_tab(char **tab);
void	exit_parse(t_state *state, int fd, char *str);
int		check_full_line(char *str, char *set);
int		check_right_dimension(char *str, int target);

void	set_resolution(t_state *state, char *str);
void	set_floor_ceil(t_state *state, t_overlay *overlay, char *str);
void	set_texture(t_state *state, t_overlay *overlay, char *str);
void	set_color(t_state *state, t_overlay *overlay, char *str);
void	load_heart_txt(t_state *state);
void	load_texture(t_state *state);
void	ft_init_texture(t_state *state);

void	map_dimension(t_state *state, char *str);
int		map_line_authentification(char *str);
char	**array_generator(t_state *state);
void	set_map(t_state *state, char *path);

void	set_hud_dimension(t_state *state);

#endif
