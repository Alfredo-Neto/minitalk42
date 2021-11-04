/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:13:31 by ade-agui          #+#    #+#             */
/*   Updated: 2021/11/04 01:05:55 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>
#include<string.h>

void handle_str(char *arr_bits)
{
 
}

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{

  // TRANSFORMAR STRING DE BITS EM INT E CONVERTER PARA DECIMAL, QUE SERÁ PRINTADO COMO CHAR

  int bit;
  static char *arr_bits;
  static int index;

  if (arr_bits == NULL)
      arr_bits = calloc(1, sizeof(char));
  bit = signal == SIGUSR1;
  if (index <= 8)
  {
      if (bit)
          arr_bits[index] = '1';
      else
          arr_bits[index] = '0';
      index++;
  }
  if(index == 8)
  {
      handle_str(arr_bits);
      free(arr_bits);
      arr_bits = NULL;
      index = 0;
  }
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
