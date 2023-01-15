/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:31 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/15 03:53:58 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

void	check_control(t_philo *ph)
{
	pthread_mutex_lock(ph->data->tf_dies);
	ph->control = ph->data->tf_die;
	pthread_mutex_unlock(ph->data->tf_dies);
}

void	print_tables(t_philo *ph, long long time_s, char *str)
{
	if (ph->control != 1)
	{
		pthread_mutex_lock(ph->data->print);
		printf("%lld %d %s\n", time_s, ph->p_id, str);
		pthread_mutex_unlock(ph->data->print);
	}
}

static int	creat_thread(t_arg *arg)
{
	long long			i;

	i = -1;
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->p_cnt);
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
	arg->id = malloc(sizeof(t_philo) * arg->p_cnt);
	arg->print = malloc(sizeof(pthread_mutex_t));
	arg->tf_dies = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(arg->print, NULL);
	pthread_mutex_init(arg->tf_dies, NULL);
	creat_thread(arg);
}
