/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:17:46 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/18 16:22:58 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

void	print_tables(t_philo *ph, long long time_s, char *str)
{
	if (ph->control != 1)
	{
		pthread_mutex_lock(ph->data->print);
		printf("%lld %d %s\n", time_s, ph->p_id, str);
		pthread_mutex_unlock(ph->data->print);
	}
}

int	dead_check_philo(t_philo *ph)
{
	static int	printtable = 1;

	pthread_mutex_lock(ph->data->print);
	if (ph->control == 0)
	{
		if (time_present() - ph->data->_1970 - ph->present_time >= \
				ph->data->time_dead)
		{
			if (printtable)
			{
				printf("%lld %d died\n", time_present() - \
					ph->data->_1970, ph->p_id);
				printtable = 0;
			}
			pthread_mutex_lock(ph->data->tf_dies);
			ph->data->tf_die = 1;
			pthread_mutex_unlock(ph->data->tf_dies);
			pthread_mutex_unlock(ph->data->print);
			return (0);
		}
	}
	pthread_mutex_unlock(ph->data->print);
	return (1);
}

static int	eat_philo(t_philo *ph)
{
	long long	time;

	time = time_present() - ph->data->_1970;
	print_tables(ph, time_present() - ph->data->_1970, "is eating");
	while (1 && dead_check_philo(ph) && ph->control != 1 && \
		ph->eat_count != ph->data->time_eat_count)
	{
		if (ph->data->time_eat == time_present() - ph->data->_1970 - time
			&& ph->control != 1)
		{
			ph->present_time = time_present() - ph->data->_1970;
			ph->eat_count++;
			return (1);
		}
		usleep(50);
	}
	return (0);
}

static int	sleeping_philo(t_philo *ph)
{
	print_tables(ph, time_present() - ph->data->_1970, "is sleeping");
	while (1 && dead_check_philo(ph) && ph->control != 1)
	{
		if (time_present() - ph->data->_1970 - \
				ph->present_time == ph->data->time_sleep && \
					ph->control != 1)
			return (1);
		usleep(50);
	}
	return (0);
}

void	*eating(void *incoming)
{
	t_philo	*ph;

	ph = (t_philo *)incoming;
	while (1 && ph->control != 1 && ph->eat_count != ph->data->time_eat_count)
	{
		pthread_mutex_lock(ph->r);
		pthread_mutex_lock(ph->l);
		check_control(ph);
		print_tables(ph, time_present() - ph->data->_1970, "has taken a fork");
		eat_philo(ph);
		check_control(ph);
		pthread_mutex_unlock(ph->r);
		pthread_mutex_unlock(ph->l);
		if (ph->control == 1)
			break ;
		sleeping_philo(ph);
		check_control(ph);
		if (ph->control == 1)
			break ;
		print_tables(ph, time_present() - ph->data->_1970, "is thinking");
		check_control(ph);
		if (ph->control == 1)
			break ;
	}
	return (0);
}
