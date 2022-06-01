#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"

void goster(int signal);
void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}
void ft_putnbr_fd(int nb, int fd)
{
    unsigned int nbr;

    if (nb < 0)
    {
        ft_putchar_fd('-', fd);
        nbr = (unsigned int)(nb * -1);
    }
    else
        nbr = (unsigned int)nb;
    if (nbr >= 10)
        ft_putnbr_fd(nbr / 10, fd);
    ft_putchar_fd((char)(nbr % 10 + 48), fd);
}
int main(int argc, char const *argv[])
{

    struct sigaction act;

    act.sa_handler = &goster;

    ft_putnbr_fd(getpid(), 1);
    printf("%d",getpid());

    while (1)
    ;

    return 0;
}

void goster(int signal)
{
    printf("%d", signal);
}
