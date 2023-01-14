/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 01:17:46 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/14 05:48:15 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

static int dead_check_philo(t_philo *ph)
{
	pthread_mutex_lock(ph->data->print);
	if(time_present() - ph->data->_1970 - ph->present_time >= ph->data->time_dead)
	{
		printf("%lld %d died\n", time_present() - ph->data->_1970, ph->p_id);
		ph->tf_die = 1;
		return (0);
	}
	pthread_mutex_unlock(ph->data->print);
	return (1);
}

static int	eat_philo(t_philo *ph)
{
	long long time;

	pthread_mutex_lock(ph->data->print);
	time = time_present() - ph->data->_1970;
	printf("%lld %d is eating\n", time_present() - ph->data->_1970, ph->p_id);
	pthread_mutex_unlock(ph->data->print);
	while(1 && dead_check_philo(ph))
	{
		if(ph->data->time_eat == time_present() - ph->data->_1970 - time
			&& ph->tf_die != 1)
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
	pthread_mutex_lock(ph->data->print);
	printf("%lld %d is sleeping\n", time_present() - ph->data->_1970, ph->p_id);
	pthread_mutex_unlock(ph->data->print);
	while(1 && dead_check_philo(ph))
	{
		if(time_present() - ph->data->_1970 - ph->present_time == ph->data->time_sleep &&
			ph->tf_die != 1)
				return (1);
		usleep(50);
	}
	return (0);
}

static int	thinking_philo(t_philo *ph)
{
	if(dead_check_philo(ph))
	{
		pthread_mutex_lock(ph->data->print);
		printf("%lld %d is thinking\n", time_present() - ph->data->_1970, ph->p_id);
		pthread_mutex_unlock(ph->data->print);
		return (1);
	}
	return (0);
}

void	*eating(void *incoming)
{
	t_philo *ph;

	ph = (t_philo *)incoming;
	while(1 && ph->tf_die != 1 && ph->eat_count != ph->data->time_eat)
	{
		pthread_mutex_lock(ph->r);
		pthread_mutex_lock(ph->l);
		pthread_mutex_lock(ph->data->print);
		printf("%lld %d has taken a fork\n",
		time_present() - ph->data->_1970, ph->p_id);
		pthread_mutex_unlock(ph->data->print);
		eat_philo(ph);
		if(ph->tf_die == 1)
			return (0);
		pthread_mutex_unlock(ph->r);
		pthread_mutex_unlock(ph->l);
		sleeping_philo(ph);
		if(ph->tf_die == 1)
			return (0);
		thinking_philo(ph);
		if(ph->tf_die == 1)
			return (0);
	}
	return (0);
}