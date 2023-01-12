#include "../includes/ifmai.h"

void	*deneme(void *arg)
{
	printf("DENEMEEEE");//basic bir deneme.
}

static int	creat_thread(t_arg *arg)
{
	int	i;

	i = 0;
	while(i < arg->p_cnt)// filozof sayısı kadar oluşturmak için döngü
	{
		pthread_create(&arg->id[i].phio, NULL, deneme, arg);//thread oluşturma
		pthread_join(arg->id[i].phio, NULL);//join oluşmasını bekleme.
		i++;
	}
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
}