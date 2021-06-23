/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:43:05 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/23 20:33:46 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static sem_t	*ft_sem_init(
	const char *name,
	unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

static void	parsing_arg(t_info *info, int argc, char *argv[])
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[5]);
}

static int	check_info(t_info *info, int argc)
{
	if (argc == 6 && info->num_of_must_eat <= 0)
		return (ft_puterror("ERROR: wrong num of must eat\n"));
	if (info->num_of_philo < 0)
		return (ft_puterror("ERROR: wrong num of philo\n"));
	if (info->time_to_die < 0)
		return (ft_puterror("ERROR: wrong time to die\n"));
	if (info->time_to_eat < 0)
		return (ft_puterror("ERROR: wrong time to eat\n"));
	if (info->time_to_sleep < 0)
		return (ft_puterror("ERROR: wrong time to sleep\n"));
	return (FT_SUCCESS);
}

static int	init_philos(t_info *info)
{
	int		i;

	info->finish = ft_sem_init("finish", 0);
	info->acting = ft_sem_init("acting", 1);
	info->forks = ft_sem_init("forks", info->num_of_philo + 1);
	info->num_of_eat_finish_philo = ft_sem_init("num_of_eat_finish_philo", 0);
	if (ft_malloc(&info->philos, sizeof(t_philo) * info->num_of_philo))
		return (ft_puterror("ERROR: malloc failed\n"));
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].name = make_n_name("philo", i);
		info->philos[i].check = ft_sem_init(info->philos[i].name, 1);
		info->philos[i].n = i;
		info->philos[i].info = info;
		++i;
	}
	return (FT_SUCCESS);
}

int	init(t_info *info, int argc, char *argv[])
{
	parsing_arg(info, argc, argv);
	if (check_info(info, argc))
		return (FT_ERROR);
	if (init_philos(info))
		return (FT_ERROR);
	return (FT_SUCCESS);
}
