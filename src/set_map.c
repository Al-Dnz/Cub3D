/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:52:46 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 19:53:54 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	increase_dimension(t_state *state)
{
	if (state->map_width < (int)ft_strlen(state->str))
		state->map_width = (int)ft_strlen(state->str);
	state->map_height++;
}

void	map_dimension(t_state *state, char *path)
{
	int	ret;
	int	i;

	ret = 1;
	state->map_width = 0;
	state->map_height = 0;
	state->fd = open(path, O_RDONLY);
	while (ret != 0)
	{
		if (state->str && map_line_authentification(state->str))
			break ;
		get_next_line(state->fd, &state->str);
	}
	i = 0;
	while (ret != 0)
	{
		increase_dimension(state);
		ret = get_next_line(state->fd, &state->str);
	}
	increase_dimension(state);
	free(state->str);
	state->str = NULL;
	close(state->fd);
}

int		map_line_authentification(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (find_index(str[i], " 012NSEW") == -1)
			return (0);
		if (find_index(str[i], "012NSEW") >= 0)
			count++;
		i++;
	}
	if (count > 0)
		return (1);
	return (0);
}

void	set_line(t_state *state, int line)
{
	int j;

	j = -1;
	if (state->str)
	{
		while (state->str[++j])
			state->map[line][j] = state->str[j];
		state->map[line][j] = 0;
	}
}

void	set_map(t_state *state, char *path)
{
	int	ret;
	int	i;

	state->fd = open(path, O_RDONLY);
	if ((state->map = array_generator(state)) == NULL)
		exit_parse(state, 1, "BUG IN 2DMAP CREATION\n");
	ret = 1;
	while (ret != 0)
	{
		if (state->str && map_line_authentification(state->str))
			break ;
		get_next_line(state->fd, &state->str);
	}
	i = 0;
	while (ret != 0)
	{
		set_line(state, i++);
		ret = get_next_line(state->fd, &state->str);
	}
	set_line(state, i);
	free(state->str);
	state->str = NULL;
	close(state->fd);
}
