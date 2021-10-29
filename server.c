/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:13:31 by ade-agui          #+#    #+#             */
/*   Updated: 2021/10/29 02:46:45 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

static void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
    printf("Sinal recebido! Confirmando para client [PID]: %d\n", siginfo->si_pid);
	kill(siginfo->si_pid, SIGUSR1);
	(void)signal;
	(void)context;
}

int main(void)
{
    struct sigaction action;
    printf("PID do server: %d\n", getpid());
    bzero(&action, sizeof(struct sigaction));
    sigemptyset(&action.sa_mask);
    action.sa_sigaction = sig_handler;
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &action, NULL))
        exit(EXIT_FAILURE);
    while (1)
        pause();
    return (0);
}
