/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifmai_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 07:23:52 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/25 20:27:28 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IFMAI_H
# define IFMAI_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define ARGERROR "PLS -> \"./philo philo_count time_dead\
time_eat time_sleep time_eat_count\"."
# define ARGGWRONG "All arguments must be numbers."
# define MINERR "Eat count min 1."

typedef struct s_philo
{
	int				p_id;
	pthread_t		phio;
	long long		eat_count;
	struct s_data	*data;
	long long		present_time;
	int				control;
}					t_philo;

typedef struct s_data
{
	t_philo			*id;
	int				p_cnt;
	long long		time_dead;
	long long		time_eat;
	long long		time_sleep;
	long long		time_eat_count;
	int				tf_die;
	int				error;
	int				*pid;
	int				time;
	long long		_1970;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;

}					t_arg;

int			ft_atoi(const char *s);
int			ft_isdigit(char *str);
long long	time_present(void);
void		philo_struct_fill(t_arg *arg, int i);
void		reset_struct(t_arg *d);
void		eating_philo(t_philo *incoming);
int			dead_check_philo(t_philo *ph);
#endif