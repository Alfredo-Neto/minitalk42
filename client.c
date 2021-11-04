/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:51:45 by ade-agui          #+#    #+#             */
/*   Updated: 2021/11/03 23:46:26 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdlib.h>
#include<strings.h>

static int	g_done;

void	wait_server_response(void)
{
	while (g_done == 0)
		;
	g_done = 0;
}

void	send_signal(int bit, int pid, const char *str)
{
	int	count;

	count = 1 << 7;
	while (count)
	{
		bit = *str & count;
		if (bit)
		{
			if (kill(pid, SIGUSR1))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2))
				exit(EXIT_FAILURE);
		}
		wait_server_response();
		count >>= 1;
	}
}

void	process_str(int pid, const char *str)
{
	int	bit;
	int	count;
	int	index;

	index = 0;
	while (*str)
	{
		send_signal(bit, pid, str);
		str++;
	}
	count = 8;
	while (count--)
	{
		if (kill(pid, SIGUSR2))
			exit(EXIT_FAILURE);
		wait_server_response();
	}
}

void	sig_handler(int signal)
{
	g_done = 1;
	(void)signal;
}

int	main(int argc, char const *argv[])
{
	struct sigaction	action;
	int					pid;

	if (argc != 3)
		exit(EXIT_FAILURE);
	bzero(&action, sizeof(struct sigaction));
	action.sa_handler = sig_handler;
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	pid = atoi(argv[1]);
	process_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}
