#include <signal.h>
#include <unistd.h>

static int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (res);
}

static int	send_char(int pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		usleep(250);
	}
	return (0);
}

static void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Signal received.", 16);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (1);
	while (*argv[2])
		if (send_char(pid, *argv[2]++) == -1)
			return (1);
	if (send_char(pid, '\n') == -1)
		return (1);
	if (send_char(pid, '\0') == -1)
		return (1);
	usleep(1000);
}