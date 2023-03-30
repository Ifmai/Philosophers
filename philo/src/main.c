/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:31 by hozdemir          #+#    #+#             */
/*   Updated: 2023/03/30 22:29:11 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

void	check_control(t_philo *ph)
{
	pthread_mutex_lock(ph->data->tf_dies);
	ph->control = ph->data->tf_die;
	pthread_mutex_unlock(ph->data->tf_dies);
}

void	*one_philo(void *incoming)
{
	t_philo		*ph;
	long long	time;

	ph = (t_philo *)incoming;
	pthread_mutex_lock(ph->r);
	print_tables(ph, time_present() - ph->data->_1970, "has taken a fork");
	time = time_present() - ph->data->_1970;
	while (1 && dead_check_philo(ph))
	{
		if (ph->data->time_dead == time_present() - ph->data->_1970 - time)
		{
			printf("%lld %d died\n", time_present() - \
					ph->data->_1970, ph->p_id);
			pthread_mutex_unlock(ph->r);
			return (0);
		}
		usleep(50);
	}
	pthread_mutex_unlock(ph->r);
	return (0);
}

static int	creat_thread(t_arg *arg)
{
	long long			i;

	i = -1;
	while (++i < arg->p_cnt)
		pthread_mutex_init(&arg->forks[i], NULL);
	i = -1;
	while (++i < arg->p_cnt)
	{
		philo_struct_fill(arg, i);
		arg->id[i].r = &arg->forks[i];
		arg->id[i].l = &arg->forks[((i + 1) % arg->p_cnt)];
	}
	i = -1;
	while (++i < arg->p_cnt)
	{
		arg->error = pthread_create(&arg->id[i].phio,
				NULL, eating, &arg->id[i]);
		if (arg->error)
			return (0);
	}
	i = -1;
	while (++i < arg->p_cnt)
		pthread_join(arg->id[i].phio, NULL);
	return (1);
}

static int	check_arg(t_arg *arg, char **av, int ac)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!(ft_isdigit(av[i])))
			return (0);
		i++;
	}
	arg->p_cnt = ft_atoi(av[1]);
	arg->time_dead = ft_atoi(av[2]);
	arg->time_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->time_eat_count = ft_atoi(av[5]);
	arg->id = malloc(sizeof(t_philo) * arg->p_cnt);
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->p_cnt);
	return (1);
}

int	main(int ac, char **av)
{
	t_arg			*arg;

	if (ac < 5 || ac > 6)
	{
		printf("%s", ARGERROR);
		return (0);
	}
	arg = malloc(sizeof(t_arg));
	reset_struct(arg);
	if (!check_arg(arg, av, ac))
		return (0);
	if (arg->p_cnt > 1)
		creat_thread(arg);
	else
	{
		pthread_mutex_init(&arg->forks[0], NULL);
		philo_struct_fill(arg, 0);
		arg->id[0].r = &arg->forks[0];
		arg->error = pthread_create(&arg->id[0].phio,
				NULL, one_philo, &arg->id[0]);
		if (arg->error)
			return (0);
		pthread_join(arg->id[0].phio, NULL);
	}
}
