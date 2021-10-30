/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:13:31 by ade-agui          #+#    #+#             */
/*   Updated: 2021/10/30 05:20:18 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

static int count;

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
    if (signal == SIGUSR1)
      write(1, "1", 1);
    if (signal == SIGUSR2)
      write(1, "0", 1);
    kill(siginfo->si_pid, SIGUSR1);
	(void)context;
}

int save_actions(void){
    struct sigaction action;
    bzero(&action, sizeof(struct sigaction));
    sigemptyset(&action.sa_mask);
    action.sa_sigaction = sig_handler;
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &action, NULL))
        exit(EXIT_FAILURE);
    if (sigaction(SIGUSR2, &action, NULL))
		exit(EXIT_FAILURE);
    return (0);
}
    
int main(void)
{
    printf("Server running... [PID]: %d\n", getpid());
    save_actions();
    while (1)
        pause();
    return (0);
}
