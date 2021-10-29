/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:51:45 by ade-agui          #+#    #+#             */
/*   Updated: 2021/10/29 18:53:06 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

static int g_done;

static void send_bit(int pid, const char *str)
{
	printf("Sinal enviado!\n");
	kill(pid, SIGUSR1);
	while (g_done == 0)
		;
	g_done = 0;
	(void)str;
}

static void sig_handler(int signal)
{
	g_done = 1;
	(void)signal;
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
	printf("PID do client: %d\n", getpid());
	send_bit(pid, argv[2]);
	return (EXIT_SUCCESS);
}
