/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:31 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/14 05:47:23 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

static int	creat_thread(t_arg *arg)
{
	long long			i;

	i = -1;
	arg->forks = malloc(sizeof(pthread_mutex_t) * arg->p_cnt); // çatal için mutex oluşumu
	while(++i < arg->p_cnt)
		pthread_mutex_init(&arg->forks[i], NULL);//mutex init alıyoruz.
	i = -1;
	while(++i < arg->p_cnt) // mutexlerin adreslerini atama işlemi yapıyoruz.
	{
		philo_struct_fill(arg, i);
		arg->id[i].r = &arg->forks[i];
		arg->id[i].l = &arg->forks[((i + 1) % arg->p_cnt)];
	}
	i = -1;
	while(++i < arg->p_cnt)// filozof sayısı kadar oluşturmak için döngü
	{
		arg->error = pthread_create(&arg->id[i].phio, NULL, eating, &arg->id[i]);//thread oluşturma
		if(arg->error)
			return (0);
	}
	i = -1;
	while(++i < arg->p_cnt)
		pthread_join(arg->id[i].phio, NULL);//join oluşmasını bekleme.
	return (1);
}

static int	check_arg(t_arg *arg, char **av, int ac)// check fonksiyonu.
{
	int	i;

	i = 1;
	while(av[i])
	{
		if(!(ft_isdigit(av[i])))// içinde sayı dışında bir şey var mı ?
			return (0);
		i++;
	}
	arg->p_cnt = ft_atoi(av[1]); // argüman değerlerini alıyorum.
	arg->time_dead = ft_atoi(av[2]);
	arg->time_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	if(ac == 6)
		arg->time_eat_count = ft_atoi(av[5]); // 6. argüman varsa değerini alıyorum yoksa -1 kalıyor reset_struct'tan.
	return (1);
}

int main(int ac, char **av)
{
	t_arg	*arg;

	if(ac < 5 || ac > 6) // arg count kontrolü.
	{
		printf("%s",ARGERROR);
		return (0);
	}
	arg = malloc(sizeof(t_arg));
	reset_struct(arg);
	if(!check_arg(arg, av, ac)) // gelen argümanları kontrol et
		return (0);
	arg->id = malloc(sizeof(t_philo) * arg->p_cnt); // filizof kadar struct oluştur.
	arg->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(arg->print, NULL);
	creat_thread(arg);
}