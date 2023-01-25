/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 07:26:15 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/25 20:02:13 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includesb/ifmai_bonus.h"

void	free_sem(t_arg *arg)
{
	int i;
    int ret;
    i = 0;
    while (i < arg->p_cnt)
    {
        waitpid(-1, &ret, 0);
        if (ret != 0)
        {
            i = -1;
            while (++i < arg->p_cnt)
                kill(arg->pid[i], 15);
            break ;
        }
        i++;
    }
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_close(arg->forks);
	sem_close(arg->print);
	sem_close(arg->dead);
}

void	create_sem(t_arg *arg)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/dead");
	arg->forks = sem_open("/fork", O_CREAT, S_IRWXU, arg->p_cnt);
	arg->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	arg->dead = sem_open("/dead", O_CREAT, S_IRWXU, 1);
}

void	open_forks(t_arg *arg)
{
	int	i;
	
	i = -1;
	while(++i < arg->p_cnt)
	{
		arg->_1970 = time_present();
		arg->pid[i] = fork();
		if (arg->pid[i] < 0)
			return ;
		else if (arg->pid[i] == 0)
		{
			arg->id = malloc(sizeof(t_philo *));
			philo_struct_fill(arg, i);
			eating_philo(arg->id);
		}
		usleep(100);
	}
	free_sem(arg);
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
	if(arg->p_cnt < 1)
		return (0);
	create_sem(arg);
	open_forks(arg);
	return (0);
}