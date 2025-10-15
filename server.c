/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:27:19 by bavirgil          #+#    #+#             */
/*   Updated: 2025/10/15 14:06:19 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	putnbr_pid(pid_t n)
{
	char	buf[20];
	int		i;

	if (n == 0)
		return ((void)write(1, "0", 1));
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	i = 0;
	while (n)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (i--)
		write(1, &buf[i], 1);
}

static struct s_state
{
	volatile sig_atomic_t	bit;
	unsigned char			byte;
} g_state = {0, 0};

static void	handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	unsigned char	incoming_bit;

	(void)info;
	(void)ucontext;
	incoming_bit = (sig == SIGUSR2);
	g_state.byte |= (incoming_bit << g_state.bit);
	g_state.bit++;
	if (g_state.bit == 8)
	{
		if (g_state.byte == '\0')
			write(1, "\n", 1);
		else
			write(1, &g_state.byte, 1);
		g_state.byte = 0;
		g_state.bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID: ");
	putnbr_pid(getpid());
	write(1, "\n", 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sig;
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
