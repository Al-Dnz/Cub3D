/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:54:44 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/14 21:51:35 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_sprite_number(t_state *state)
{
	int i;
	int j;

	state->s.n = 0;
	j = 0;
	while (state->map[j])
	{
		i = 0;
		while (state->map[j][i])
		{
			if (state->map[j][i] == 's')
				state->s.n++;
			i++;
		}
		j++;
	}
}

void	set_sprites(t_state *state, int n)
{
	int i;
	int j;

	j = -1;
	if (state->s.n > 0)
	{
		state->s.order = malloc(sizeof(int) * state->s.n);
		state->s.dist = malloc(sizeof(double) * state->s.n);
		state->s.coord = malloc(sizeof(t_position) * state->s.n);
		if (!state->s.order || !state->s.dist || !state->s.coord)
			return ;
		while (state->map[++j])
		{
			i = -1;
			while (state->map[j][++i])
			{
				if (state->map[j][i] == 's')
				{
					state->s.coord[n].x = (double)i + 0.5;
					state->s.coord[n++].y = (double)j + 0.5;
				}
			}
		}
	}
}

void	draw_sprite(t_state *state, int y, int tex_x, int stripe)
{
	int	d;
	int	tex_y;

	while (y < state->s.draw_end_y)
	{
		d = y * 256 - state->win_height * 128 + state->s.sprite_height * 128;
		tex_y = ((d * state->texture[4].height) / state->s.sprite_height) / 256;
		if (state->texture[4].addr[tex_y *
state->texture[4].line_len / 4 + tex_x] != 000)
			state->img.addr[y * state->img.line_len / 4 + stripe] =
state->texture[4].addr[tex_y * state->texture[4].line_len / 4 + tex_x];
		y++;
	}
}

void	ft_sprite(t_state *state)
{
	int i;
	int y;
	int stripe;
	int tex_x;

	i = -1;
	set_dist_order(state);
	while (++i < state->s.n)
	{
		sprite_operation(state, i);
		stripe = state->s.draw_start_x;
		while (stripe < state->s.draw_end_x)
		{
			tex_x =
(int)(256 * (stripe - (-state->s.sprite_width / 2 + state->s.sprite_screen_x)) *
state->texture[4].width / state->s.sprite_width) / 256;
			if (state->s.transform_y > 0 && stripe >= 0 &&
stripe < state->win_width && state->s.transform_y < state->s.z_buffer[stripe])
			{
				y = state->s.draw_start_y;
				draw_sprite(state, y, tex_x, stripe);
			}
			stripe++;
		}
	}
}
