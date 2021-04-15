/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 02:26:23 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 14:40:58 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		extension_error(char **argv)
{
	char	**tab;
	int		i;
	int		output;

	output = 0;
	i = 0;
	tab = ft_split(argv[1], ".");
	while (tab[i])
		i++;
	if (ft_strcmp(tab[i - 1], "cub"))
		output = 1;
	free_tab(tab);
	return (output);
}

int		arg_error(char argc, char **argv)
{
	int		fd;

	if (argc < 2 || argc > 3)
	{
		ft_putstr_fd("Error\nWRONG ARGUMENTS NUMBER\n", 1);
		exit(0);
	}
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
	{
		ft_putstr_fd("Error\nSECOND ARGUMENT IS NOT --save\n", 1);
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nPATH TO FILE DESCRITPION IS INVALID\n", 1);
		exit(0);
	}
	close(fd);
	if (extension_error(argv))
	{
		ft_putstr_fd("Error\nEXTENSION OF FILE DESCRITPION IS INVALID\n", 1);
		exit(0);
	}
	return (1);
}

void	set_heart_ratio(t_state *state)
{
	int r;

	r = 1;
	while ((4 * (state->texture[7].width / r) + 2 * state->hud_margin >
state->win_width / 2) || ((state->texture[7].height / r) +
2 * state->hud_margin > state->hud_height))
		r++;
	state->heart_ratio = r;
}

void	set_hud_dimension(t_state *state)
{
	int	option_1;
	int	option_2;

	state->hud_height = state->win_height / 5;
	state->win_height = 4 * state->win_height / 5;
	state->hud_margin = state->hud_height / 5;
	set_heart_ratio(state);
	option_1 = (state->hud_height - 2 * state->hud_margin) / state->map_height;
	option_2 =
(state->win_width / 2 - 2 * state->hud_margin) / state->map_width;
	state->pixel_size = option_2;
	if (state->map_height * option_2 +
2 * state->hud_margin > state->hud_height)
		state->pixel_size = option_1;
	else if (state->map_width * option_1 +
2 * state->hud_margin > state->win_width / 2)
		state->pixel_size = option_2;
}

int		main(int argc, char **argv)
{
	char	*path;
	t_state state;

	init_parser(&state);
	path = argv[1];
	arg_error(argc, argv);
	state.save = false;
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		state.save = true;
	file_parser(&state, path);
	if (!map_validation(state.map, &state))
	{
		free_map(state.map);
		exit_parse(&state, 1, "INVALID MAP\n");
	}
	cub_3d(&state);
	return (1);
}
