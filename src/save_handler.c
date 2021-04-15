/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:47:09 by adenhez           #+#    #+#             */
/*   Updated: 2021/04/13 19:48:17 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_bmp(t_state *state, int fd)
{
	int tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * state->win_width * state->win_height;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &state->win_width, 4);
	write(fd, &state->win_height, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &state->img.bpp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	save(t_state *state)
{
	int fd;
	int	x;
	int	y;

	y = state->win_height;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		exit_process(state, 1);
	init_bmp(state, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < state->win_width)
		{
			write(fd, &state->img.addr[y * state->img.line_len / 4 + x], 4);
			x++;
		}
		y--;
	}
	system("chmod 777 image.bmp");
	ft_putstr_fd("PICTURE IS SHOOT !\n", 1);
	close(fd);
}
