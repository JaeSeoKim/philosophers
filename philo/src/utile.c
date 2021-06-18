/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:46:19 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/19 00:17:36 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_msg(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	ms -= philo->info->create_at.tv_sec * 1000;
	ms -= philo->info->create_at.tv_usec / 1000;
	if (!philo->info->finish)
		printf("%lld\t%d\t%s\n", ms, philo->n + 1, str);
}

int	ft_puterror(char *str)
{
	write(2, str, ft_strlen(str));
	return (FT_ERROR);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	flag;

	result = 0;
	flag = 1;
	if (*nptr == '-')
		flag *= -1;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result *= 10;
		result += *nptr++ - '0';
	}
	return (result * flag);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (FT_ERROR);
	memset(*(void **)dst, 0, size);
	return (FT_SUCCESS);
}
