/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:41:53 by jaeskim           #+#    #+#             */
/*   Updated: 2021/06/20 23:55:03 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FT_ERROR		1
# define FT_SUCCESS		0

typedef struct s_philo
{
	int				n;
	int				num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	struct s_info	*info;
	struct timeval	last_time_to_eat;

}					t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				num_of_eat_finish_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	create_at;
}			t_info;

int			init(t_info *info, int argc, char *argv[]);
void		*philo(void *argv);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);

/* ========================================================================== */
/*                                  UTILE                                     */
/* ========================================================================== */

int			ft_strlen(char *str);
int			ft_atoi(const char *nptr);
int			ft_puterror(char *str);
int			ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void		print_philo_msg(t_philo *philo, char *str);

#endif
