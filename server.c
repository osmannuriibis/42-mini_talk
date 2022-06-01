#include <signal.h>
#include "../libft/libft.h"

void printBits(char c, int size)
{
	if (size == 0)
		return;
	printBits(c >> 1, size - 1);
	if ((c & 1))
	{
		ft_putchar_fd('1', 1);
	}
	else
	{
		ft_putchar_fd('0', 1);
	}
}

static void handler(int sig, siginfo_t *sig_info, void *func)
{
	static int i = 0;
	static int client_pid;
	static char c = 0;

	client_pid = sig_info->si_pid;
	c |= (sig == SIGUSR2);

	if (i++ < 10)
		c <<= 1;
	else
	{
		if (c)
		{
			ft_putchar_fd(c, 1);
			kill(client_pid, SIGUSR1);
		}
		else
		{
			kill(client_pid, SIGUSR2);
			ft_putstr_fd("\n^\nRecieved data from ", 1);
			ft_putnbr_fd(client_pid, 1);
			ft_putstr_fd(" PID adress\n\n", 1);
		}
		i = 0;
		c = 0;
	}
}
int main()
{
	struct sigaction act;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);

	while (1)
	{
		pause();
	}

	/* code */
	return 0;
}
