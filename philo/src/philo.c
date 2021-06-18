/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:51:22 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/18 17:32:47 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philos(void *argv)
{
	t_philo	*philo;

	philo = argv;
	printf("%d\n", philo->n);
	sleep(1);
	return (NULL);
}

int	create_philos(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_create(&info->philos[i].thread, NULL, \
			philos, &info->philos[i]);
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
