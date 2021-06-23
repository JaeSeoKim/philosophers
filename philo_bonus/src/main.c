/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:41:24 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/23 21:17:02 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_and_free_philos(t_info *info)
{
	int		i;
	int		status;

	i = -1;
	while (++i < info->num_of_philo)
	{
		waitpid(info->philos[i].pid, &status, 0);
		sem_close(info->philos[i].check);
		free(info->philos[i].name);
	}
	free(info->philos);
	sem_close(info->finish);
	sem_close(info->acting);
	sem_close(info->forks);
	sem_close(info->num_of_eat_finish_philo);
}

static void	fork_philos(t_info *info)
{
	int			i;

	gettimeofday(&info->create_at, NULL);
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].last_time_to_eat = info->create_at;
		info->philos[i].pid = fork();
		if (info->philos[i].pid == 0)
			return (philo(&info->philos[i]));
		else if (info->philos[i].pid < 0)
		{
			ft_puterror("ERROR: fork failed");
			exit(1);
		}
		++i;
	}
}

int	main(int argc, char *argv[])
{
	t_info		info;
	pthread_t	thread;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (ft_puterror("ERROR: wrong argc\n"));
	if (init(&info, argc, argv))
		return (1);
	fork_philos(&info);
	if (info.num_of_must_eat != 0)
		pthread_create(&thread, NULL, monitor_each_must_eat, &info);
	pthread_create(&thread, NULL, finish_monitor, &info);
	join_and_free_philos(&info);
	return (0);
}
