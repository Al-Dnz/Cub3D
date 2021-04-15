/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:22:53 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 11:43:34 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	global_free(t_state *state)
{
	free(state->s.z_buffer);
	free(state->s.order);
	free(state->s.dist);
	free(state->s.coord);
	free_map(state->map);
	state->map = NULL;
	free(state->mlx);
	state->mlx = NULL;
}

void	destroy_overlay(t_state *state)
{
	if (state->no.address != NULL)
		free(state->no.address);
	if (state->so.address != NULL)
		free(state->so.address);
	if (state->ea.address != NULL)
		free(state->ea.address);
	if (state->we.address != NULL)
		free(state->we.address);
	if (state->f.address != NULL)
		free(state->f.address);
	if (state->c.address != NULL)
		free(state->c.address);
	if (state->sp.address != NULL)
		free(state->sp.address);
}

void	destroy_images(t_state *state)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (state->texture[i].mlx_img != NULL)
			mlx_destroy_image(state->mlx, state->texture[i++].mlx_img);
	}
	mlx_destroy_image(state->mlx, state->texture[7].mlx_img);
	mlx_destroy_image(state->mlx, state->img.mlx_img);
	mlx_destroy_image(state->mlx, state->img2.mlx_img);
	mlx_clear_window(state->mlx, state->win);
	mlx_destroy_window(state->mlx, state->win);
	state->mlx = NULL;
}

void	exit_process(t_state *state, t_bool error)
{
	destroy_images(state);
	global_free(state);
	destroy_overlay(state);
	if (error)
		ft_putstr_fd("Error\n", 1);
	else
		ft_putstr_fd("CLEAN_EXIT !\n", 1);
	exit(error);
}
