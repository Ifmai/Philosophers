#ifndef IFMAI_H
# define IFMAI_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

# define ARGERROR "PLS -> ./philo philo_count time_dead time_eat time_sleep time_eat_count"
# define ARGGWRONG "All arguments must be numbers"

typedef struct s_philo
{
	int				p_id;
	pthread_t		phio;
	long long			eat_count;
	long long			tf_die;
	struct s_data	*data;
	long long		present_time;
	pthread_mutex_t	*l; // sol
	pthread_mutex_t	*r; // sağ
}					t_philo;

typedef struct s_data
{
	t_philo			*id;
	pthread_t		phio;
	long long		p_cnt;
	long long		time_dead;
	long long		time_eat;
	long long		time_sleep;
	long long		time_eat_count;
	pthread_mutex_t	*print;
	int				error;
	long long		_1970;
	pthread_mutex_t	*forks;
}					t_arg;

int			ft_atoi(const char *s);
int			ft_isdigit(char *str);
void		reset_struct(t_arg *d);
void		philo_struct_fill(t_arg *data, int i);
void		*eating(void *p);
long long	time_present();

# endif