#include <signal.h>
#include "../libft/libft.h"

static void handler(int sig)
{
	static int count = 0;

	if (sig == SIGUSR1)
	{
		ft_putchar_fd('.', 1);
		count++;
	}
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("\nSending Data Complieted\n", 1);
		exit(0);
	}
}

static void ft_kill(int pid, char *str)
{

	static int i;
	char c;
	i = 11;

	while (*str)
	{
		c = *str++;

		while (--i > -1)
		{
			if (c >> i & 1)
			{
				kill(pid, SIGUSR2);
			}
			else
			{
				kill(pid, SIGUSR1);
			}
			usleep(100);
		}
		i = 11;
	}
	i = 11;
	while (--i > -1)
	{
		kill(pid, SIGUSR1);

		usleep(100);
	}
}

int main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	if (ft_atoi(argv[1]) == 0)
	{
		ft_putstr_fd("Please entry correct PID\n", 1);
		return (1);
	}
	ft_putstr_fd("Client PID:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR2, handler);
	signal(SIGUSR1, handler);
	ft_kill(ft_atoi(argv[1]), argv[2]);

	while (1)
	{
		pause();
	}

	return 0;
}
