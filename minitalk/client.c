/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cegbulef <cegbulef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:50:53 by cegbulef          #+#    #+#             */
/*   Updated: 2022/12/19 10:29:17 by cegbulef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The sig argument specifies which signal was received.
	The func procedure allows a user to choose the action upon receipt of a signal.
	SIGUSR1 => 30   SIGUSR2 => 31
	If signalnbr == 30 | 31 activates any of the two signals
	The kill utility sends a signal to the processes specified by the pid operands.
	The kill utility exits 0 on success, and >0 if an error occurs.
	kill(sigusr, pid).. SIGUSR1 => 1 | SIGUSR2 => 0
	The sender function sends the bits in reverse order 
		to the server(eg: 01001000 as 00010010)
*/

#include "minitalk.h"

void	sender(int pid, char c)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if ((c & (0x01 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep (100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			sender(pid, argv[2][i]);
			i++;
		}
		sender(pid, '\n');
	}
	else
	{
		write (1, "Error: Wrong Format\n", 20);
		write (1, "Try: ./client <PID> <MESSAGE>\n", 30);
		return (1);
	}
	return (0);
}
