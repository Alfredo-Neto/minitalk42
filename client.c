/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:51:45 by ade-agui          #+#    #+#             */
/*   Updated: 2021/10/28 22:45:48 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

static char g_done;

void send_str(int pid, const char *str)
{
	kill(pid, SIGUSR1);
	(void)str;
}

void sig_handler(int signal)
{
	printf("Recebi o sinal: %d\n", signal);
	g_done = 1;
}

int main(int argc, char const *argv[])
{
	struct sigaction action;
	int pid;
	if (argc != 3)
		exit(EXIT_FAILURE);
	bzero(&action, sizeof(struct sigaction));
	action.sa_handler = sig_handler;
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	pid = atoi(argv[1]);
	send_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}

// siginfo_t sigset_t SA_SIGINFO EXIT_FAILURE

