/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:58:49 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 11:42:00 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	strclr(char **str)
{
	free(*str);
	*str = NULL;
}

void	file_descritption_switch(t_state *state)
{
	if (find_index(state->tab[0][0], "012RNSWEFC") == -1)
		exit_parse(state, 1, "WRONG INFORMATION IN FILE DESCRIPTON\n");
	if (ft_strcmp(state->tab[0], "R") == 0)
		set_resolution(state, state->str);
	if (ft_strcmp(state->tab[0], "NO") == 0)
		set_texture(state, &state->no, state->str);
	if (ft_strcmp(state->tab[0], "SO") == 0)
		set_texture(state, &state->so, state->str);
	if (ft_strcmp(state->tab[0], "EA") == 0)
		set_texture(state, &state->ea, state->str);
	if (ft_strcmp(state->tab[0], "WE") == 0)
		set_texture(state, &state->we, state->str);
	if (ft_strcmp(state->tab[0], "S") == 0)
		set_texture(state, &state->sp, state->str);
	if (ft_strcmp(state->tab[0], "F") == 0)
		set_floor_ceil(state, &state->f, state->str);
	if (ft_strcmp(state->tab[0], "C") == 0)
		set_floor_ceil(state, &state->c, state->str);
}

void	description_checker(t_state *state)
{
	if ((state->no.checked == false) || (state->so.checked == false)
		|| (state->ea.checked == false) || (state->we.checked == false)
		|| (state->f.checked == false) || (state->c.checked == false)
		|| (state->sp.checked == false))
	{
		exit_parse(state, 1, "MISSING ELEMENTS IN TEXTURE DESCRIPTON\n");
	}
	if (state->win_width < 1 || state->win_height < 1)
		exit_parse(state, 1, "RESOLUTION VALUE IS NOT SET \n");
	if (state->map_width <= 1 || state->map_height <= 1)
		exit_parse(state, 1, "2DMAP IS NOT CORRECTLY SET IN DESCRIPTION\n");
}

void	file_parser(t_state *state, char *path)
{
	int	ret;
	int	count;

	ret = 1;
	count = 0;
	state->fd = open(path, O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(state->fd, &state->str);
		state->tab = ft_split(state->str, " ,");
		if (state->tab[0] != NULL)
		{
			file_descritption_switch(state);
			free_tab(state->tab);
		}
		if (map_line_authentification(state->str))
			count++;
		strclr(&state->str);
	}
	close(state->fd);
	if (count > 0)
		map_dimension(state, path);
	if (state->map_width > 1 && state->map_height > 1)
		set_map(state, path);
	description_checker(state);
}
