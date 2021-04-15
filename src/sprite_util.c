/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:46:22 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 23:00:38 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_dist_order2(t_state *state)
{
	int i;

	i = -1;
	while (++i < state->s.n)
	{
		state->s.order[i] = i;
		state->s.dist[i] = ((state->ray.pos_y - state->s.coord[i].x) *
(state->ray.pos_y - state->s.coord[i].x) +
(state->ray.pos_y - state->s.coord[i].y) *
(state->ray.pos_y - state->s.coord[i].y));
	}
}

void	set_dist_order(t_state *state)
{
	int		i;
	int		j;
	double	tmp;

	set_dist_order2(state);
	i = -1;
	while (++i < state->s.n)
	{
		j = -1;
		while (++j < state->s.n - 1)
		{
			if (state->s.dist[j] < state->s.dist[j + 1])
			{
				tmp = state->s.dist[j];
				state->s.dist[j] = state->s.dist[j + 1];
				state->s.dist[j + 1] = tmp;
				tmp = state->s.order[j];
				state->s.order[j] = state->s.order[j + 1];
				state->s.order[j + 1] = (int)tmp;
			}
		}
	}
}

void	init_sprite(t_state *state)
{
	state->s.z_buffer = malloc(sizeof(double) * state->win_width);
	get_sprite_number(state);
	set_sprites(state, 0);
	set_dist_order(state);
}

void	sprite_operation_1(t_state *state, int i)
{
	state->s.sprite_x =
state->s.coord[state->s.order[i]].y - state->ray.pos_x;
	state->s.sprite_y =
state->s.coord[state->s.order[i]].x - state->ray.pos_y;
	state->s.inv_det = 1.0 / (state->ray.plane_x *
state->ray.dir_y - state->ray.dir_x * state->ray.plane_y);
	state->s.transform_x = state->s.inv_det * (state->ray.dir_y *
state->s.sprite_x - state->ray.dir_x * state->s.sprite_y);
	state->s.transform_y = state->s.inv_det * (-state->ray.plane_y *
state->s.sprite_x + state->ray.plane_x * state->s.sprite_y);
	state->s.sprite_screen_x = (int)((state->win_width / 2) *
(1 + state->s.transform_x / state->s.transform_y));
	state->s.sprite_height =
abs((int)(state->win_height / (state->s.transform_y)));
	state->s.draw_start_y = -state->s.sprite_height / 2 + state->win_height / 2;
}

void	sprite_operation(t_state *state, int i)
{
	sprite_operation_1(state, i);
	if (state->s.draw_start_y < 0)
		state->s.draw_start_y = 0;
	state->s.draw_end_y = state->s.sprite_height / 2 + state->win_height / 2;
	if (state->s.draw_end_y >= state->win_height)
		state->s.draw_end_y = state->win_height;
	state->s.sprite_width =
abs((int)(state->win_height / (state->s.transform_y)));
	state->s.draw_start_x =
-state->s.sprite_width / 2 + state->s.sprite_screen_x;
	if (state->s.draw_start_x < 0)
		state->s.draw_start_x = 0;
	state->s.draw_end_x = state->s.sprite_width / 2 + state->s.sprite_screen_x;
	if (state->s.draw_end_x >= state->win_width)
		state->s.draw_end_x = state->win_width;
}
