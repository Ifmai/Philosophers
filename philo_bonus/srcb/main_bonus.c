/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 07:26:15 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/18 16:12:55 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includesb/ifmai_bonus.h"

static int	open_fork(t_arg *arg)
{
	int	i;
	int	pid;

	i = 0;
	while(i < arg->p_cnt)
	{
		pid = fork();
		if(pid == 0)
		{
			arg->pid[i] = pid;
			philo_struct_fill(arg->id, i);
			eating_philo(arg->id);
		}
		else if (pid < 0)
			exit(0);
	}
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
	{
		arg->time_eat_count = ft_atoi(av[5]);
		if(arg->time_eat_count < 0)
		{
			printf("%s", MINERR);
			return (0);
		}
	}
	arg->pid = malloc(sizeof(int) * arg->p_cnt);
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
	arg->forks = sem_open("/fork", O_CREAT, S_IRWXU, arg->p_cnt);
	open_forks(arg);
	return (0);
}