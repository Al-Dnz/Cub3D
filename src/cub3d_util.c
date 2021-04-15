/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:06:19 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 18:21:26 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_right_dimension(char *str, int target)
{
	char	**tab;
	int		n;

	tab = NULL;
	n = 0;
	tab = ft_split(str, " ,");
	while (tab[n])
		n++;
	free_tab(tab);
	if (n == target)
		return (1);
	else
		return (0);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	tab = NULL;
}

void	exit_parse(t_state *state, int fd, char *str)
{
	ft_putstr_fd("Error\n", fd);
	ft_putstr_fd(str, fd);
	if (state->str)
		free(state->str);
	if (state->tab)
		free_tab(state->tab);
	destroy_overlay(state);
	close(state->fd);
	exit(0);
}

int		check_full_line(char *str, char *set)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (find_index(str[i], set) == -1)
			return (0);
		i++;
	}
	return (1);
}
