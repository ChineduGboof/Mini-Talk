/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cegbulef <cegbulef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:50:50 by cegbulef          #+#    #+#             */
/*   Updated: 2022/12/19 11:50:05 by cegbulef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	i being static should increment each time a bit is sent till it forms the byte
	bit also being static should increment each time a bit is sent till becomes 8bit
	printout the character using the binary stored in i when the bit count equals 8
	reset the bit to 0 and i to 0 to restart the process and get the next character
	The sig handler receives the bits and calculates 
		using the first digit as the least significant bit 
		(1, 2, 4, 8, 16, 32, 64, 128)
		i = i | (0x01 << bit); => when you see a one, 
			move the bit to that line and get the value
*/

#include "minitalk.h"

void	sig_handler(int signalnbr)
{
	static int	i;
	static int	bit;

	if (signalnbr == SIGUSR1)
		i = i | (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &i, 1);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		write(1, "Error: Wrong input format\n", 26);
		write(1, "Try: ./server\n", 14);
		return (0);
	}
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (argc == 1)
	{
		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
		pause();
	}
	return (0);
}
