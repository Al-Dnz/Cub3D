/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:23:03 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 18:26:50 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	img->addr[y * img->line_len / 4 + x] = color;
}

void	draw_pix(t_state *state, int x, int y, int color)
{
	img_pix_put(&state->img2, x, y, color);
}

void	draw_heart(t_state *state, int x, int y)
{
	int i;
	int j;

	j = 0;
	while (j++ < state->texture[7].height)
	{
		i = 0;
		while (i++ < state->texture[7].width)
			state->img2.addr[(y + j / state->heart_ratio) *
	state->img2.line_len / 4 + (x + i / state->heart_ratio)] =
	state->texture[7].addr[j * state->texture[7].line_len / 4 + i];
	}
}
