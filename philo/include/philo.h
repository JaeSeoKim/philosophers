/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:41:53 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/18 16:41:56 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

# define FT_ERROR		1
# define FT_SUCCESS		0

typedef struct s_philo
{
	int				n;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	pthread_t		thread;
}					t_philo;

typedef struct s_info
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_must_eat;
	t_philo	*philos;
}			t_info;

int		init(t_info *info, int argc, char *argv[]);
int		create_philos(t_info *info);

/* ========================================================================== */
/*                                  UTILE                                     */
/* ========================================================================== */

int		ft_strlen(char *str);
int		ft_atoi(const char *nptr);
int		ft_puterror(char *str);
int		ft_malloc(void *dst, size_t size);

#endif
