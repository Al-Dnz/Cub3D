/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 22:04:42 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 11:44:26 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	load_heart_txt(t_state *state)
{
	state->texture[7].mlx_img = NULL;
	state->texture[7].mlx_img =
mlx_xpm_file_to_image(state->mlx, "./textures/regular/heart.xpm",
&(state->texture[7].width), &(state->texture[7].height));
	state->texture[7].addr =
(int*)mlx_get_data_addr(state->texture[7].mlx_img,
&(state->texture[7].bpp), &(state->texture[7].line_len),
&(state->texture[7].endian));
}

void	load_texture(t_state *state)
{
	t_overlay	arr[7];
	int			i;

	arr[0] = state->no;
	arr[1] = state->so;
	arr[2] = state->ea;
	arr[3] = state->we;
	arr[4] = state->sp;
	arr[5] = state->c;
	arr[6] = state->f;
	i = -1;
	while (++i < 7)
	{
		state->texture[i].mlx_img = NULL;
		state->texture[i].mlx_img = mlx_xpm_file_to_image(state->mlx,
arr[i].address, &(state->texture[i].width), &(state->texture[i].height));
		state->texture[i].addr =
(int*)mlx_get_data_addr(state->texture[i].mlx_img,
	&(state->texture[i].bpp),
		&(state->texture[i].line_len), &(state->texture[i].endian));
	}
	load_heart_txt(state);
}

void	ft_init_texture(t_state *state)
{
	if (state->ray.side == 0 && state->ray.ray_dir_x < 0)
		state->t.ref = 0;
	if (state->ray.side == 0 && state->ray.ray_dir_x >= 0)
		state->t.ref = 1;
	if (state->ray.side == 1 && state->ray.ray_dir_y < 0)
		state->t.ref = 2;
	if (state->ray.side == 1 && state->ray.ray_dir_y >= 0)
		state->t.ref = 3;
	if (state->ray.side == 0)
		state->t.wall_x =
state->ray.pos_y + state->ray.perp_wall_dist * state->ray.ray_dir_y;
	else
		state->t.wall_x =
state->ray.pos_x + state->ray.perp_wall_dist * state->ray.ray_dir_x;
	state->t.wall_x -= floor((state->t.wall_x));
}

void	op_skyfloor_1(t_state *state, int y)
{
	state->ray.ray_dir_x0 = state->ray.dir_x - state->ray.plane_x;
	state->ray.ray_dir_y0 = state->ray.dir_y - state->ray.plane_y;
	state->ray.ray_dir_x1 = state->ray.dir_x + state->ray.plane_x;
	state->ray.ray_dir_y1 = state->ray.dir_y + state->ray.plane_y;
	state->ray.p = y - state->win_height / 2;
	state->ray.pos_z = 0.5 * state->win_height;
	state->ray.row_distance = state->ray.pos_z / state->ray.p;
	state->ray.floor_step_x = state->ray.row_distance
		* (state->ray.ray_dir_x1 - state->ray.ray_dir_x0) / state->win_width;
	state->ray.floor_step_y = state->ray.row_distance
		* (state->ray.ray_dir_y1 - state->ray.ray_dir_y0) / state->win_width;
	state->ray.floor_x =
state->ray.pos_x + state->ray.row_distance * state->ray.ray_dir_x0;
	state->ray.floor_y =
state->ray.pos_y + state->ray.row_distance * state->ray.ray_dir_y0;
}

void	op_skyfloor_2(t_state *state, t_img texture)
{
	state->ray.cell_x = (int)state->ray.floor_x;
	state->ray.cell_y = (int)state->ray.floor_y;
	state->ray.tx = (int)(texture.width *
(state->ray.floor_x - state->ray.cell_x)) & (texture.width - 1);
	state->ray.ty = (int)(texture.height *
(state->ray.floor_y - state->ray.cell_y)) & (texture.height - 1);
	state->ray.floor_x += state->ray.floor_step_x;
	state->ray.floor_y += state->ray.floor_step_y;
}
