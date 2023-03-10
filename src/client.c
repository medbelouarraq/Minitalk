/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:02:09 by mbelouar          #+#    #+#             */
/*   Updated: 2023/02/19 15:53:58 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	main(int ac, char **av)
{
	int	i;
	int	bit;

	i = 0;
	if (ac == 3 && ft_atoi(av[1]) > 0)
	{
		while (av[2][i])
		{
			bit = 8;
			while (--bit >= 0)
			{
				if ((av[2][i] >> bit) & 1)
					kill(ft_atoi(av[1]), SIGUSR1);
				else
					kill(ft_atoi(av[1]), SIGUSR2);
				usleep(250);
			}
		i++;
		}
	}
	else
	{
		ft_printf("There's something wrong with the arguments\n");
		return (EXIT_FAILURE);
	}
}
