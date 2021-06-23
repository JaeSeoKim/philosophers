/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_n_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:23:58 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/22 17:28:17 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		++i;
	return (i);
}

char	*make_n_name(char *name, int n)
{
	char	*result;
	int		num;
	int		i;

	i = 0;
	num = n;
	while (num)
	{
		num /= 10;
		++i;
	}
	result = malloc(sizeof(char) * (i + ft_strlen(name) + 1));
	if (result == NULL)
		return (NULL);
	num = -1;
	while (++num < i)
		result[num] = name[num];
	while (n)
	{
		result[i++] = n % 10 + '0';
		n /= 10;
	}
	result[i] = 0;
	return (result);
}
