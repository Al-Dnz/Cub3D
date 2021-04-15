/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:22:57 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/14 14:23:40 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_key(t_state *state)
{
	state->key.forward = 0;
	state->key.back = 0;
	state->key.left = 0;
	state->key.right = 0;
	state->key.rot_right = 0;
	state->key.rot_left = 0;
}

void	init_ray_adjustement(t_state *state)
{
	if (state->init_cardinal == 'W' || state->init_cardinal == 'E')
	{
		state->ray.dir_x += 0.001;
		state->ray.dir_y += 0.001;
		state->ray.plane_x += 0.001;
		state->ray.plane_y += 0.001;
	}
	if (state->init_cardinal == 'W')
		state->ray.pos_y += 0.001;
}

void	init_ray(t_state *state)
{
	state->ray.movespeed = 0.1;
	state->ray.rotspeed = 0.06;
	state->ray.pos_x = (double)state->player_coord.y;
	state->ray.pos_y = (double)state->player_coord.x;
	state->ray.dir_x = 0;
	state->ray.dir_y = 0;
	state->ray.plane_x = 0;
	state->ray.plane_y = 0;
	init_ray_adjustement(state);
	if (state->init_cardinal == 'N')
		state->ray.dir_x = -1;
	if (state->init_cardinal == 'S')
		state->ray.dir_x = 1;
	if (state->init_cardinal == 'E')
		state->ray.dir_y = 1;
	if (state->init_cardinal == 'W')
		state->ray.dir_y = -1;
	if (state->init_cardinal == 'N')
		state->ray.plane_y = 0.66;
	if (state->init_cardinal == 'S')
		state->ray.plane_y = -0.66;
	if (state->init_cardinal == 'E')
		state->ray.plane_x = 0.66;
	if (state->init_cardinal == 'W')
		state->ray.plane_x = -0.66;
}

void	set_raydir(t_state *state)
{
	if (state->ray.ray_dir_y == 0)
		state->ray.delta_dist_x = 0;
	else
	{
		if (state->ray.ray_dir_x == 0)
			state->ray.delta_dist_x = 1;
		else
			state->ray.delta_dist_x =
sqrt(1 + (state->ray.ray_dir_y * state->ray.ray_dir_y) /
(state->ray.ray_dir_x * state->ray.ray_dir_x));
	}
	if (state->ray.ray_dir_x == 0)
		state->ray.delta_dist_y = 0;
	else
	{
		if (state->ray.ray_dir_y == 0)
			state->ray.delta_dist_y = 1;
		else
			state->ray.delta_dist_y =
sqrt(1 + (state->ray.ray_dir_x * state->ray.ray_dir_x) /
(state->ray.ray_dir_y * state->ray.ray_dir_y));
	}
}

void	init_ray_2(t_state *state)
{
	state->ray.hit = 0;
	state->ray.perp_wall_dist = 0;
	state->ray.camera_x = 2 * state->ray.pix_line /
(double)state->win_width - 1;
	state->ray.ray_dir_x = state->ray.dir_x +
state->ray.plane_x * state->ray.camera_x;
	state->ray.ray_dir_y = state->ray.dir_y +
state->ray.plane_y * state->ray.camera_x;
	state->ray.map_x = (int)state->ray.pos_x;
	state->ray.map_y = (int)state->ray.pos_y;
	set_raydir(state);
}
