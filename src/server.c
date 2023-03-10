/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:01:03 by mbelouar          #+#    #+#             */
/*   Updated: 2023/02/19 14:46:45 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_pow2(int base, int puiss)
{
	int	pow;
	int	i;

	pow = 1;
	i = 0;
	while (i < puiss)
	{
		pow *= base;
		i++;
	}
	return (pow);
}

char	create_char(int *tab, int i)
{
	char	c;

	c = 0;
	while (i)
	{
		if (tab[i - 1] == 1)
			c += ft_pow2(2, 8 - i);
		i--;
	}
	return (c);
}

void	handle_sig(int sig, siginfo_t *info, void *message)
{
	static int	stock_bits[8];
	static int	i;
	static int	clientpid;
	char		c;

	(void) message;
	if (clientpid != info->si_pid)
	{
		clientpid = info->si_pid;
		i = 0;
	}
	stock_bits[i++] = (sig == SIGUSR1);
	if (i == 8)
	{
		c = create_char(stock_bits, i);
		write (1, &c, 1);
		i = 0;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sigact;

	(void)av;
	sigact.sa_sigaction = &handle_sig;
	sigact.sa_flags = SA_SIGINFO;
	if (ac != 1)
	{
		ft_printf("There's something wrong with the number of arguments\n");
		return (EXIT_FAILURE);
	}
	pid = getpid();
	ft_printf("Server PID : %d\n", pid);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
}
