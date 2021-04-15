/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:11:40 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 22:39:57 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_wall(t_state *state, int x, int y)
{
	y = state->ray.draw_start - 1;
	ft_init_texture(state);
	state->t.step = 1.0 * state->texture[0].height / state->ray.line_height;
	state->t.tex_x =
(int)(state->t.wall_x * (double)state->texture[state->t.ref].width);
	if (state->ray.side == 0 && state->ray.ray_dir_x > 0)
		state->t.tex_x =
state->texture[state->t.ref].width - state->t.tex_x - 1;
	if (state->ray.side == 1 && state->ray.ray_dir_y < 0)
		state->t.tex_x =
state->texture[state->t.ref].width - state->t.tex_x - 1;
	state->t.tex_pos =
(state->ray.draw_start - state->win_height / 2 +
state->ray.line_height / 2) * state->t.step;
	while (++y <= state->ray.draw_end)
	{
		state->t.tex_y =
(int)state->t.tex_pos & (state->texture[state->t.ref].height - 1);
		state->t.tex_pos += state->t.step;
		if (y < state->win_height && x < state->win_width)
			state->img.addr[y * state->img.line_len / 4 + x] =
state->texture[state->t.ref].addr[state->t.tex_y *
state->texture[state->t.ref].line_len / 4 + state->t.tex_x];
	}
}

void	draw_sky_floor(t_state *state, t_img texture, int choice)
{
	int y;
	int x;

	y = state->win_height / 2;
	while (y < state->win_height)
	{
		op_skyfloor_1(state, y);
		x = 0;
		while (x < state->win_width)
		{
			op_skyfloor_2(state, texture);
			if (choice == 0)
				state->img.addr[(state->win_height - y) *
state->img.line_len / 4 + x] =
texture.addr[texture.width * state->ray.ty + state->ray.tx];
			else if (choice == 1)
				state->img.addr[y *
state->img.line_len / 4 + x] =
texture.addr[texture.width * state->ray.ty + state->ray.tx];
			x++;
		}
		y++;
	}
}

void	draw_sky(t_state *state, t_img texture)
{
	int	y;
	int	x;

	y = 0;
	while (y <= state->win_height / 2)
	{
		x = 0;
		while (x <= state->win_width)
		{
			state->img.addr[y * state->img.line_len / 4 + x] =
texture.addr[texture.width * y + x];
			x++;
		}
		y++;
	}
}

void	fill_color(t_state *state, t_overlay *overlay, int choice)
{
	int y;
	int x;
	int c;

	c = (overlay->r << 16 | overlay->g << 8 | overlay->b);
	if (choice == 0)
	{
		y = -1;
		while (++y < state->win_height / 2)
		{
			x = 0;
			while (x < state->win_width)
				state->img.addr[y * state->img.line_len / 4 + x++] = c;
		}
	}
	if (choice == 1)
	{
		y = state->win_height / 2 - 1;
		while (++y < state->win_height)
		{
			x = 0;
			while (x < state->win_width)
				state->img.addr[y * state->img.line_len / 4 + x++] = c;
		}
	}
}
