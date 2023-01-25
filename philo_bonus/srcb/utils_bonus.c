/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozdemir <hozdemir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 07:27:12 by hozdemir          #+#    #+#             */
/*   Updated: 2023/01/25 20:13:43 by hozdemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includesb/ifmai_bonus.h"

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
	return (((tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	philo_struct_fill(t_arg *arg, int i)
{
	arg->id->p_id = i + 1;
	arg->id->data = arg;
	arg->id->eat_count = 0;
	arg->id->control = 0;
	arg->id->present_time = 0;
}

void	reset_struct(t_arg *d)
{
	d->p_cnt = 0;
	d->time_dead = 0;
	d->time_eat = 0;
	d->time_sleep = 0;
	d->time_eat_count = -1;
	d->tf_die = 0;

}
