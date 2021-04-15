/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:59:46 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 14:49:07 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	verline(t_state *state, t_fig fig)
{
	while (fig.drawstart < fig.drawend)
		draw_pix(state, fig.x, fig.drawstart++, fig.color);
}

void	draw_circle(t_state *state, t_fig fig)
{
	int	i;
	int	a;

	a = 0;
	while (a <= 360)
	{
		i = 0;
		while (i++ <= fig.size)
			draw_pix(state, fig.x + i * sin(PI * a / 180),
fig.y - i * cos((PI * a / 180)), fig.color);
		a++;
	}
}

void	draw_square(t_state *state, t_fig fig)
{
	int	i;

	i = 0;
	while (i <= fig.size)
	{
		fig.x++;
		fig.drawstart = fig.y;
		fig.drawend = fig.y + fig.size;
		verline(state, fig);
		i++;
	}
}

void	draw_map(t_state *state, int x, int y)
{
	y = -1;
	while (state->map[++y])
	{
		x = -1;
		while (state->map[y][++x])
		{
			if (state->map[y][x] == '1')
			{
				draw_square(state, (t_fig)
{x * state->pixel_size + state->hud_margin,
y * state->pixel_size + state->hud_margin, state->pixel_size, GREEN, 0, 0});
			}
			if (state->map[y][x] == 's')
			{
				draw_circle(state, (t_fig)
{x * state->pixel_size + state->hud_margin + state->pixel_size / 2,
y * state->pixel_size + state->hud_margin + state->pixel_size / 2,
state->pixel_size / 4, WHITE, 0, 0});
			}
		}
	}
	if (state->hud_height > 2 * state->hud_margin + 5)
		draw_square(state, (t_fig)
{state->ray.pos_y * state->pixel_size + state->hud_margin - 2,
state->ray.pos_x * state->pixel_size + state->hud_margin - 2, 5, RED, 0, 0});
}
