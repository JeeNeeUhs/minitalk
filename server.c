#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	b_buf = 0;
	static unsigned int		pos = 0;

	(void)context;
	if (sig == SIGUSR1)
		b_buf = b_buf << 1;
	else if (sig == SIGUSR2)
		b_buf = (b_buf << 1) | 1;
	pos++;
	if (pos == 8)
	{
		write(1, &b_buf, 1);
		if (b_buf == '\0')
			kill(info->si_pid, SIGUSR1);
		b_buf = 0;
		pos = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	printf("Process PID: %d\n", getpid());
	while (1)
		pause();
}