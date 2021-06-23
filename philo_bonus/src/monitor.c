/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 00:53:57 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/23 21:02:21 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*finish_monitor(void *arg)
{
	int		i;
	t_info	*info;

	info = arg;
	sem_wait(info->finish);
	i = 0;
	while (i < info->num_of_philo)
		kill(info->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;
	int		i;

	info = argv;
	i = 0;
	while (i++ < info->num_of_philo)
		sem_wait(info->num_of_eat_finish_philo);
	sem_post(info->finish);
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (1)
	{
		sem_wait(philo->check);
		sem_wait(philo->info->acting);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->info->time_to_die)
		{
			printf("%lld\t%d\t %s\n", \
				time_to_ms(now) - time_to_ms(philo->info->create_at), \
				philo->n + 1, "died");
			sem_post(philo->info->finish);
			return (NULL);
		}
		sem_post(philo->info->acting);
		sem_post(philo->check);
	}
	return (NULL);
}
