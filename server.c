/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahekinci <ahekinci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:10:32 by ahekinci          #+#    #+#             */
/*   Updated: 2024/12/25 16:52:20 by ahekinci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

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
		b_buf = 0;
		pos = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar('0' + n);
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
	write(1, "Process PID: ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
