/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:21:07 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/14 21:50:49 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		find_index(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		set_player_coord(char **map, t_position *coord, t_state *state)
{
	int				x;
	int				y;
	static float	angulations[5] = {0.0, 90.0, 180.0, 270.0};

	coord->a = 0.0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (find_index(map[y][x], "NSEW") > -1)
			{
				coord->x = (float)x;
				coord->y = (float)y;
				coord->a = angulations[find_index(map[y][x], "NSEW")];
				state->init_cardinal = map[y][x];
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	map_floodfill(char **map, int x, int y, t_bool *closed_map)
{
	if (map[y][x] == '0' || map[y][x] == '2')
	{
		if (map[y][x] == '0')
			map[y][x] = 'x';
		if (map[y][x] == '2')
			map[y][x] = 's';
		if (x - 1 < 0 || y - 1 < 0 || !map[y][x + 1] || !map[y + 1])
		{
			*closed_map = false;
			return ;
		}
	}
	else if (find_index(map[y][x], "02NSEW") == -1)
	{
		if (map[y][x] == ' ')
			*closed_map = false;
		return ;
	}
	map_floodfill(map, x + 1, y, closed_map);
	map_floodfill(map, x - 1, y, closed_map);
	map_floodfill(map, x, y + 1, closed_map);
	map_floodfill(map, x, y - 1, closed_map);
}
