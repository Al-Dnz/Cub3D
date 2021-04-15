/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:18:49 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 19:21:01 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_bool	cardinal_occurence(char **map)
{
	int	x;
	int	y;
	int	occurence;

	y = 0;
	occurence = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (find_index(map[y][x], "NSEW") > -1)
				occurence++;
			x++;
		}
		y++;
	}
	if (occurence != 1)
		return (0);
	return (1);
}

t_bool	valid_symbol(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (find_index(map[y][x], "012NSEW ") == -1)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int		map_validation(char **map, t_state *state)
{
	static t_position	coord = {0.0, 0.0, 0};
	t_bool				closed_map;
	t_bool				validated_symbol;
	t_bool				initial_position;

	set_player_coord(map, &coord, state);
	closed_map = true;
	validated_symbol = valid_symbol(map);
	initial_position = cardinal_occurence(map);
	map_floodfill(map, (int)coord.x, (int)coord.y, &closed_map);
	if (!validated_symbol || !initial_position || !closed_map)
	{
		if (validated_symbol == false)
			write(1, "Invalid symbol are set in the map\n", 34);
		if (initial_position == false)
			write(1, "Initial position is not correctly set\n", 38);
		if (closed_map == false)
			write(1, "Non closed map\n", 15);
		return (0);
	}
	return (1);
}
