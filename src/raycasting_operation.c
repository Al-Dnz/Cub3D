/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_operation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:29:59 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 22:27:02 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_stepside_dist(t_state *state)
{
	if (state->ray.ray_dir_x < 0)
	{
		state->ray.step_x = -1;
		state->ray.side_dist_x =
(state->ray.pos_x - state->ray.map_x) * state->ray.delta_dist_x;
	}
	else
	{
		state->ray.step_x = 1;
		state->ray.side_dist_x =
(state->ray.map_x + 1.0 - state->ray.pos_x) * state->ray.delta_dist_x;
	}
	if (state->ray.ray_dir_y < 0)
	{
		state->ray.step_y = -1;
		state->ray.side_dist_y =
(state->ray.pos_y - state->ray.map_y) * state->ray.delta_dist_y;
	}
	else
	{
		state->ray.step_y = 1;
		state->ray.side_dist_y =
(state->ray.map_y + 1.0 - state->ray.pos_y) * state->ray.delta_dist_y;
	}
	ft_incrementray(state);
}

void	ft_incrementray(t_state *state)
{
	while (state->ray.hit == 0)
	{
		if (state->ray.side_dist_y <= 0 ||
(state->ray.side_dist_x >= 0 &&
state->ray.side_dist_x < state->ray.side_dist_y))
		{
			state->ray.side_dist_x += state->ray.delta_dist_x;
			state->ray.map_x += state->ray.step_x;
			state->ray.side = 0;
		}
		else
		{
			state->ray.side_dist_y += state->ray.delta_dist_y;
			state->ray.map_y += state->ray.step_y;
			state->ray.side = 1;
		}
		if (state->map[state->ray.map_x][state->ray.map_y] == '1')
			state->ray.hit = 1;
	}
	ft_draw_start_end(state);
}

void	ft_draw_start_end(t_state *state)
{
	if (state->ray.side == 0)
		state->ray.perp_wall_dist =
((double)state->ray.map_x - state->ray.pos_x +
(1 - (double)state->ray.step_x) / 2) / state->ray.ray_dir_x;
	else
		state->ray.perp_wall_dist =
((double)state->ray.map_y -
state->ray.pos_y + (1 - (double)state->ray.step_y) / 2) / state->ray.ray_dir_y;
	state->ray.line_height =
(int)(state->win_height / state->ray.perp_wall_dist);
	state->ray.draw_start = -state->ray.line_height / 2 + state->win_height / 2;
	if (state->ray.draw_start < 0)
		state->ray.draw_start = 0;
	state->ray.draw_end = state->ray.line_height / 2 + state->win_height / 2;
	if (state->ray.draw_end >= state->win_height || state->ray.draw_end < 0)
		state->ray.draw_end = state->win_height - 1;
}

void	ft_line_render(int pix_line, t_state *state)
{
	draw_wall(state, pix_line, 0);
}
