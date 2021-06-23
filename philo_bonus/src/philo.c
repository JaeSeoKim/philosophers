/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:51:22 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/23 21:02:19 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pickup_fork(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_philo_msg(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_philo_msg(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->check);
	gettimeofday(&philo->last_time_to_eat, NULL);
	print_philo_msg(philo, "is eating");
	philo->num_of_eat += 1;
	if (philo->num_of_eat == philo->info->num_of_must_eat)
		sem_post(philo->info->num_of_eat_finish_philo);
	usleep(philo->info->time_to_eat * 1000);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	sem_post(philo->check);
}

static void	sleeping(t_philo *philo)
{
	print_philo_msg(philo, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	print_philo_msg(philo, "is thinking");
}

void	philo(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitor, philo);
	if (philo->n % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);
	while (1)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	exit(0);
}
