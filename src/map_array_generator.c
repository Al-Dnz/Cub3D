/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array_generator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:18:29 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 19:18:30 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

char	**array_generator(t_state *state)
{
	char	**arr;
	int		i;
	int		j;

	if ((arr = malloc(sizeof(char*) * (state->map_height + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < state->map_height)
	{
		if ((arr[i] = malloc(sizeof(char) * (state->map_width + 1))) == NULL)
			return (NULL);
		j = 0;
		while (j < state->map_width)
		{
			arr[i][j] = ' ';
			j++;
		}
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = 0;
	return (arr);
}

void	free_map(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
