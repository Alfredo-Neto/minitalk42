/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:13:31 by ade-agui          #+#    #+#             */
/*   Updated: 2021/10/31 01:05:39 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

void print_array(int **arr_bits)
{
  while (*arr_bits)
  {
    printf("%d", *arr_bits);
    arr_bits++;
  }
}

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
    int bit;
    static int *arr_bits;
    static int index;

    if (arr_bits == NULL)
      arr_bits = calloc(16, sizeof(int));
    bit = signal == SIGUSR1;
    arr_bits[index++] = bit;
    if (index == 8)
      print_array(&arr_bits);
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
