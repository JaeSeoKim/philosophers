/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:41:24 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/19 00:31:19 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	struct timeval	last_time_to_eat;
	long long		ms;

	philo = argv;
	usleep(100);
	while (!philo->info->finish)
	{
		pthread_mutex_lock(&philo->check_mutex);
		last_time_to_eat = philo->last_time_to_eat;
		gettimeofday(&now, NULL);
		ms = now.tv_sec * 1000;
		ms += now.tv_usec / 1000;
		ms -= last_time_to_eat.tv_sec * 1000;
		ms -= last_time_to_eat.tv_usec / 1000;
		if (ms >= philo->info->time_to_die)
		{
			print_philo_msg(philo, "died");
			philo->info->finish = 1;
		}
		pthread_mutex_unlock(&philo->check_mutex);
	}
	return (NULL);
}

static int	create_philos(t_info *info)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].last_time_to_eat = info->create_at;
		pthread_create(&info->philos[i].thread, NULL, \
			philo, &info->philos[i]);
		pthread_create(&thread, NULL, monitor, &info->philos[i]);
		pthread_detach(thread);
		++i;
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_join(info->philos[i].thread, NULL))
			return (ft_puterror("ERROR: pthread_join fail.\n"));
		++i;
	}
	return (FT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (ft_puterror("ERROR: wrong argc\n"));
	if (init(&info, argc, argv))
		return (1);
	if (create_philos(&info))
		return (1);
	return (0);
}
