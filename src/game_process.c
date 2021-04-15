/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 23:58:25 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 11:42:40 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	process_wall(t_state *state)
{
	state->ray.pix_line = 0;
	while (state->ray.pix_line < state->win_width)
	{
		init_ray_2(state);
		ft_stepside_dist(state);
		ft_line_render(state->ray.pix_line, state);
		state->s.z_buffer[state->ray.pix_line] = state->ray.perp_wall_dist;
		state->ray.pix_line++;
	}
}

void	render_graphic(t_state *state)
{
	mlx_destroy_image(state->mlx, state->img.mlx_img);
	state->img.mlx_img =
mlx_new_image(state->mlx, state->win_width, state->win_height);
	state->img.addr = (int*)mlx_get_data_addr(state->img.mlx_img,
&state->img.bpp, &state->img.line_len, &state->img.endian);
	mlx_destroy_image(state->mlx, state->img2.mlx_img);
	state->img2.mlx_img =
mlx_new_image(state->mlx, state->win_width, state->hud_height);
	state->img2.addr = (int*)mlx_get_data_addr(state->img2.mlx_img,
&state->img2.bpp, &state->img2.line_len, &state->img2.endian);
	if (state->c.type == 1)
		draw_sky_floor(state, state->texture[5], 0);
	else if (state->c.type == 0)
		fill_color(state, &state->c, 0);
	if (state->f.type == 1)
		draw_sky_floor(state, state->texture[6], 1);
	else if (state->f.type == 0)
		fill_color(state, &state->f, 1);
	process_wall(state);
	ft_sprite(state);
	draw_life(state);
	draw_map(state, 0, 0);
	mlx_put_image_to_window(state->mlx, state->win, state->img.mlx_img, 0, 0);
	mlx_put_image_to_window(state->mlx, state->win,
state->img2.mlx_img, 0, state->win_height);
}

void	life_absorber(t_state *state)
{
	if (state->map[(int)state->ray.pos_x][(int)state->ray.pos_y] == 's' &&
state->life < 4)
	{
		state->life++;
		state->map[(int)state->ray.pos_x][(int)state->ray.pos_y] = 'x';
		get_sprite_number(state);
		set_sprites(state, 0);
		set_dist_order(state);
	}
}

int		game_process(t_state *state)
{
	longitdinal_move(state);
	horizontal_move(state);
	rotation_move(state);
	life_absorber(state);
	return (1);
}
