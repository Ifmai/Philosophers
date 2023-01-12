#ifndef IFMAI_H
# define IFMAI_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define ARGERROR "PLS -> ./philo philo_count time_dead time_eat time_sleep time_eat_count"
# define ARGGWRONG "All arguments must be numbers"

typedef struct s_philo
{
	int				p_id;
	pthread_t		phio;
	size_t			eat_count;
	size_t			tf_die;
	pthread_mutex_t	*l;
	pthread_mutex_t	*r;
}					t_philo;

typedef struct s_data
{
	t_philo		*id;
	pthread_t	phio;
	size_t		p_cnt;
	size_t		time_dead;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		time_eat_count;
}			t_arg;

int		ft_atoi(const char *s);
int		ft_isdigit(char *str);
void	reset_struct(t_arg *d);

# endif