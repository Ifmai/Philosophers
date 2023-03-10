/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 03:37:53 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/18 18:23:08 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

int	ft_atoi(const char *s)
{
	int		i;
	long	back;
	int		np;

	back = 0;
	np = 1;
	i = 0;
	while ((s[i] <= 13 && s[i] >= 9) || s[i] == 32)
		i++;
	if (s[i] == 43 || s[i] == 45)
	{
		if (s[i] == 45)
			np *= -1;
		i++;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		back = back * 10 + (s[i] - 48) * np;
		if (back > 2147483647)
			return (-1);
		if (back < -2147483648)
			return (0);
		i++;
	}
	return ((int)back);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!(str[i] >= 48 && str[i] <= 57))
		{
			printf("%s | Error ARG : %s", ARGGWRONG, str);
			return (0);
		}
		i++;
	}
	return (1);
}

long long	time_present(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	philo_struct_fill(t_arg *arg, int i)
{
	arg->id[i].p_id = i + 1;
	arg->id[i].data = arg;
	arg->id[i].present_time = time_present() - arg->_1970;
	arg->id[i].eat_count = 0;
	arg->id[i].control = 0;
}

void	reset_struct(t_arg *d)
{
	d->p_cnt = 0;
	d->time_dead = 0;
	d->time_eat = 0;
	d->time_sleep = 0;
	d->time_eat_count = -1;
	d->tf_die = 0;
	d->_1970 = time_present();
	d->print = malloc(sizeof(pthread_mutex_t));
	d->tf_dies = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(d->print, NULL);
	pthread_mutex_init(d->tf_dies, NULL);
}
