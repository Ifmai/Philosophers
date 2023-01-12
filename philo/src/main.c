/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:31 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/12 15:43:37 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ifmai.h"

void	*deneme(void *arg)
{
	t_philo *p = arg;

	pthread_mutex_lock(p->l);
	pthread_mutex_lock(p->r);
	printf("%d has taken a fork\n", p->p_id);
	printf("%d has taken a fork\n", p->p_id);
	usleep(1000 * 800);
	pthread_mutex_unlock(p->l);
	pthread_mutex_unlock(p->r);
	printf("%d bıraktı \n", p->p_id);
	printf("%d bıraktı \n", p->p_id);
	return (0);
}

static int	creat_thread(t_arg *arg)
{
	size_t			i;
	size_t			j;
	int				error;
	pthread_mutex_t	*forks;

	j = -1;
	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * arg->p_cnt); // çatal için mutex oluşumu
	while(++j < arg->p_cnt)
		pthread_mutex_init(&forks[j], NULL);//mutex init alıyoruz.
	j = -1;
	while(++j < arg->p_cnt) // mutexlerin adreslerini atama işlemi yapıyoruz.
	{
		arg->id[j].p_id = j + 1;
		arg->id[j].r = &forks[j];
		arg->id[j].l = &forks[((j + 1) % arg->p_cnt)];
	}
	while(++i < arg->p_cnt)// filozof sayısı kadar oluşturmak için döngü
	{
		error = pthread_create(&arg->id[i].phio, NULL, deneme, &arg->id[i]);//thread oluşturma
		if(error)
			return (0);
	}
	i = -1;
	while(++i < arg->p_cnt)
		pthread_join(arg->id[i].phio, NULL);//join oluşmasını bekleme.
	return (0);
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
	creat_thread(arg);
	while(1);
}