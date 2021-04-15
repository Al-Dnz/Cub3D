/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:32:48 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 15:25:27 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	resize_window(t_state *state)
{
	int	width;
	int	height;

	mlx_get_screen_size(state->mlx, &width, &height);
	if (state->win_width > width)
		state->win_width = width - 1;
	if (state->win_height > height)
		state->win_height = height - 1;
}

void	init_parser(t_state *state)
{
	state->map_width = 0;
	state->map_height = 0;
	state->str = NULL;
	state->win_width = 0;
	state->win_height = 0;
	state->no.address = NULL;
	state->so.address = NULL;
	state->ea.address = NULL;
	state->we.address = NULL;
	state->sp.address = NULL;
	state->f.address = NULL;
	state->f.r = 0;
	state->f.g = 0;
	state->f.b = 0;
	state->c.address = NULL;
	state->c.r = 0;
	state->c.g = 0;
	state->c.b = 0;
	state->no.checked = false;
	state->so.checked = false;
	state->ea.checked = false;
	state->we.checked = false;
	state->sp.checked = false;
	state->f.checked = false;
	state->c.checked = false;
}

int		quit(t_state *state)
{
	exit_process(state, 0);
	return (1);
}

void	mlx_process(t_state *state)
{
	mlx_hook(state->win, 17, 0, quit, state);
	mlx_hook(state->win, 2, 1L << 0, &key_press, state);
	mlx_hook(state->win, 3, 1L << 1, &key_release, state);
	mlx_loop_hook(state->mlx, &game_process, state);
	mlx_loop(state->mlx);
}

void	cub_3d(t_state *state)
{
	set_player_coord(state->map, &state->player_coord, state);
	state->map[(int)state->player_coord.y][(int)state->player_coord.x] = 'x';
	state->life = 1;
	state->mlx = mlx_init();
	resize_window(state);
	state->win = mlx_new_window(state->mlx,
state->win_width, state->win_height, "adenhez's CUB3D");
	load_texture(state);
	set_hud_dimension(state);
	state->img.mlx_img = mlx_new_image(state->mlx,
state->win_width, state->win_height);
	state->img.addr =
(int*)mlx_get_data_addr(state->img.mlx_img, &state->img.bpp,
&state->img.line_len, &state->img.endian);
	state->img2.mlx_img = mlx_new_image(state->mlx,
state->win_width, state->hud_height);
	state->img2.addr = (int*)mlx_get_data_addr(state->img2.mlx_img,
&state->img2.bpp, &state->img2.line_len, &state->img2.endian);
	init_key(state);
	init_ray(state);
	init_sprite(state);
	render_graphic(state);
	if (state->save == 1)
		save(state);
	mlx_process(state);
}
