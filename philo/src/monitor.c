/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 00:53:57 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/19 02:06:40 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;
	int		i;
	int		cnt;

	info = argv;
	while (!info->finish)
	{
		cnt = 0;
		i = 0;
		while (i < info->num_of_philo)
		{
			if (info->philos[i].num_of_eat >= info->num_of_must_eat)
				++cnt;
			pthread_mutex_lock(&info->finish_mutex);
			if (cnt == info->num_of_philo)
				info->finish = 1;
			pthread_mutex_unlock(&info->finish_mutex);
			++i;
		}
	}
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (!philo->info->finish)
	{
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->info->finish_mutex);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->info->time_to_die && philo->info->finish == 0)
		{
			printf("%lld\t%d\t %s\n", ms, philo->n + 1, "died");
			philo->info->finish = 1;
		}
		pthread_mutex_unlock(&philo->info->finish_mutex);
		pthread_mutex_unlock(&philo->check_mutex);
	}
	return (NULL);
}
