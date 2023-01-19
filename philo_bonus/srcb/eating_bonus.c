/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:00 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/19 13:49:01 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includesb/ifmai_bonus.h"

void	print_tables(t_philo *ph, long long time_s, char *str)
{
	if (ph->data->tf_die != 1)
	{
		sem_wait(ph->data->print);
		printf("%lld %d %s\n", time_s, ph->p_id, str);
		sem_post(ph->data->print);
	}
}

int	dead_check_philo(t_philo *ph)
{
	sem_wait(ph->data->dead);
	if (time_present() - ph->data->_1970 - ph->present_time >= \
			ph->data->time_dead)
	{
		sem_wait(ph->data->print);
		printf("%lld %d died\n", time_present() - \
		ph->data->_1970, ph->p_id);
		ph->data->tf_die = 1;
		exit(1);
	}
	sem_post(ph->data->dead);
	return (1);
}

static void eat_philo(t_philo *ph)
{
	long long	time;

	time = time_present() - ph->data->_1970;
	print_tables(ph, time_present() - ph->data->_1970, "is eating");
	while (1 && dead_check_philo(ph) && ph->data->tf_die != 1 && \
		ph->eat_count != ph->data->time_eat_count)
	{
		if (ph->data->time_eat == time_present() - ph->data->_1970 - time
			&& ph->data->tf_die != 1)
		{
			ph->eat_count++;
			ph->present_time = time_present() - ph->data->_1970;
			break ;
		}
		usleep(50);
	}
}

static void sleeping_philo(t_philo *ph)
{
	print_tables(ph, time_present() - ph->data->_1970, "is sleeping");
	while (1 && dead_check_philo(ph) && ph->data->tf_die != 1)
	{
		if (time_present() - ph->data->_1970 - \
				ph->present_time == ph->data->time_sleep && \
					ph->data->tf_die != 1)
			break ;
		usleep(50);
	}
}

void	eating_philo(t_philo *ph)
{
	while (1 && ph->data->tf_die != 1 && ph->eat_count != ph->data->time_eat_count)
	{
		sem_wait(ph->data->forks);
		sem_wait(ph->data->forks);
		print_tables(ph, time_present() - ph->data->_1970, "has taken a forks");
		eat_philo(ph);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);
		sleeping_philo(ph);
		print_tables(ph, time_present() - ph->data->_1970, "is thinking");
	}
	if(ph->eat_count == ph->data->time_eat_count)
		exit(1);
}
