/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parameters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 20:00:31 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/15 14:09:38 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_resolution(t_state *state, char *str)
{
	char **tab;

	tab = NULL;
	if (!check_full_line(str, " 0123456789R"))
		exit_parse(state, 1, "WRONG CHARACTER IN RESOLUTION DESCRIPTION\n");
	if (!check_right_dimension(str, 3))
		exit_parse(state, 1, "WRONG NUMBER ARG IN RESOLUTION DESCRIPTION\n");
	tab = ft_split(str, " ");
	state->win_width = ft_atoi(tab[1]);
	state->win_height = ft_atoi(tab[2]);
	free_tab(tab);
	if (state->win_width < 10 || state->win_height < 10)
		exit_parse(state, 1, "RESOLUTION VALUE IS TOO EXTREME\n");
}

void	set_floor_ceil(t_state *state, t_overlay *overlay, char *str)
{
	int		n;
	char	**tab;

	n = 0;
	tab = ft_split(str, " ,");
	while (tab[n])
		n++;
	free_tab(tab);
	if (n == 4)
		set_color(state, overlay, str);
	else if (n == 2)
		set_texture(state, overlay, str);
	else
		exit_parse(state, 1, "FLOOR OR CEIL DESCRIPTION ARE INCORRECT\n");
}

void	set_texture(t_state *state, t_overlay *overlay, char *str)
{
	char	**tab;
	int		fd;

	tab = NULL;
	if (check_right_dimension(str, 2) == 0)
	{
		exit_parse(state, 1, "WRONG NUMBER ARG IN TEXTURE DESCRIPTION\n");
		return ;
	}
	tab = ft_split(str, " ,");
	fd = open(tab[1], O_RDONLY);
	if (fd < 0)
	{
		free_tab(tab);
		exit_parse(state, 1, "WRONG PATH FOR A TEXTURE DESCRIPTION\n");
	}
	close(fd);
	overlay->address = ft_strdup(tab[1]);
	overlay->type = 1;
	overlay->checked = true;
	free_tab(tab);
}

void	set_color(t_state *state, t_overlay *overlay, char *str)
{
	char **tab;

	tab = NULL;
	if (check_full_line(str, " 0123456789FC,") == 0)
	{
		exit_parse(state, 1, "FLOOR OR CEIL DESCRIPTION ARE INCORRECT\n");
		return ;
	}
	tab = ft_split(str, " ,");
	overlay->r = ft_atoi(tab[1]);
	overlay->g = ft_atoi(tab[2]);
	overlay->b = ft_atoi(tab[3]);
	if (overlay->r < 0 || overlay->r > 255)
		exit_parse(state, 1, "FLOOR OR CEIL COLOR VALUE IS INCORRECT\n");
	if (overlay->g < 0 || overlay->g > 255)
		exit_parse(state, 1, "FLOOR OR CEIL COLOR VALUE IS INCORRECT\n");
	if (overlay->b < 0 || overlay->b > 255)
		exit_parse(state, 1, "FLOOR OR CEIL COLOR VALUE IS INCORRECT\n");
	overlay->type = 0;
	overlay->address = ft_strdup("./textures/regular/default.xpm");
	overlay->color = (overlay->r << 16 | overlay->g << 8 | overlay->b);
	overlay->checked = true;
	free_tab(tab);
}
