/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:39:58 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/10 22:40:00 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_predict(long n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char		*ft_itoa(int number)
{
	char		*str;
	int			negative;
	int			i;
	long		n;

	n = (long)number;
	negative = n < 0 ? 1 : 0;
	n = n < 0 ? n * -1 : n;
	if (!(str = malloc(sizeof(char) * (size_predict(n) + 1 + negative))))
		return (NULL);
	i = size_predict(n) + negative;
	str[i--] = '\0';
	if (n == 0)
	{
		str[i] = '0';
		return (str);
	}
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	if (negative)
		str[i] = '-';
	return (str);
}
