/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:21:09 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 23:56:47 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	longitdinal_move(t_state *state)
{
	if (state->key.forward == 1)
	{
		if (state->map[(int)(state->ray.pos_x + state->ray.dir_x *
state->ray.movespeed)][(int)state->ray.pos_y] != '1')
			state->ray.pos_x += state->ray.dir_x * state->ray.movespeed;
		if (state->map[(int)(state->ray.pos_x)]
[(int)(state->ray.pos_y + state->ray.dir_y * state->ray.movespeed)] != '1')
			state->ray.pos_y += state->ray.dir_y * state->ray.movespeed;
		render_graphic(state);
	}
	if (state->key.back == 1)
	{
		if (state->map[(int)(state->ray.pos_x - state->ray.dir_x *
state->ray.movespeed)]
[(int)(state->ray.pos_y)] != '1')
			state->ray.pos_x -= state->ray.dir_x * state->ray.movespeed;
		if (state->map[(int)(state->ray.pos_x)]
[(int)(state->ray.pos_y - state->ray.dir_y * state->ray.movespeed)] != '1')
			state->ray.pos_y -= state->ray.dir_y * state->ray.movespeed;
		render_graphic(state);
	}
}

void	horizontal_move(t_state *state)
{
	if (state->key.right == 1)
	{
		if (state->map[(int)(state->ray.pos_x + state->ray.dir_y *
	state->ray.movespeed)][(int)state->ray.pos_y] != '1')
			state->ray.pos_x += state->ray.dir_y * state->ray.movespeed;
		if (state->map[(int)state->ray.pos_x]
[(int)(state->ray.pos_y - state->ray.dir_x * state->ray.movespeed)] != '1')
			state->ray.pos_y -= state->ray.dir_x * state->ray.movespeed;
		render_graphic(state);
	}
	if (state->key.left == 1)
	{
		if (state->map[(int)(state->ray.pos_x -
state->ray.dir_y * state->ray.movespeed)][(int)state->ray.pos_y] != '1')
			state->ray.pos_x -= state->ray.dir_y * state->ray.movespeed;
		if (state->map[(int)state->ray.pos_x]
[(int)(state->ray.pos_y + state->ray.dir_x * state->ray.movespeed)] != '1')
			state->ray.pos_y += state->ray.dir_x * state->ray.movespeed;
		render_graphic(state);
	}
}

void	rotation_move(t_state *state)
{
	double	old_dir_x;
	double	old_plane_x;
	int		k;

	if (state->key.rot_right == 1)
		k = -1;
	if (state->key.rot_left == 1)
		k = 1;
	if (state->key.rot_left || state->key.rot_right)
	{
		old_dir_x = state->ray.dir_x;
		state->ray.dir_x =
	state->ray.dir_x * cos(k * state->ray.rotspeed / 2) -
	state->ray.dir_y * sin(k * state->ray.rotspeed / 2);
		state->ray.dir_y = old_dir_x * sin(k * state->ray.rotspeed / 2) +
	state->ray.dir_y * cos(k * state->ray.rotspeed / 2);
		old_plane_x = state->ray.plane_x;
		state->ray.plane_x =
	state->ray.plane_x * cos(k * state->ray.rotspeed / 2) -
	state->ray.plane_y * sin(k * state->ray.rotspeed / 2);
		state->ray.plane_y = old_plane_x * sin(k * state->ray.rotspeed / 2) +
	state->ray.plane_y * cos(k * state->ray.rotspeed / 2);
		render_graphic(state);
	}
}
