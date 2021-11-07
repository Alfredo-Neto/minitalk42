/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-agui <ade-agui@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:13:31 by ade-agui          #+#    #+#             */
/*   Updated: 2021/11/07 04:30:32 by ade-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char *put_first_char(char c)
{
  char *add;
  int index;
  
  index = 0;
  add = (char *)malloc(sizeof(char) + 1);
  if (!add)
    return (NULL);
  add[index++] = c;
  add[index] = '\0';
  return (add);
}

char *handle_str(char *str, char c)
{
  int index;
  char *add;
  
  index = 0;
  if(!str)
    return (put_first_char(c));
  if (!c)
    return (NULL);
  add = (char *)malloc(sizeof(char) * (strlen(str) + 2));
  if (!add)
    return (NULL);
  while (str[index])
  {
    add[index] = str[index];
    index++;
  }
  add[index++] = c;
  add[index] = '\0';
  return (add);
}

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
  static int bits;
  static char current = 0xFF; // 01000001 = 65 = 'A'
  static char *output;

  if (signal == SIGUSR1) // 1
    current |= 0x80 >> bits;
  else if (signal == SIGUSR2) // 0
    current ^= 0x80 >> bits;
  if (++bits == 8)
  {
    if (current)
      output = handle_str(output, current);
    else
    {
      output = print_str(output);
      free(output);
      output = NULL;
    }
    current = 0xFF;
    bits = 0;
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

// PROXIMAS TAREFAS:
// VERIFICAR INTEGRAÇÃO COM LIBFT E PRINTF
// VER LEAKS DE MEMÓRIA
// TESTAR MAIS UMA VEZ
// NORMINETTE
// ESTUDAR O MINITALK DO VINICIUS
// ADICIONAR HANDLE_STR E PUT_FIRST_CHAR NA LIBFT
// MELHORAR A FUNÇÃO DE PRINT
// IMPLEMENTAR FUNÇÃO PERSONALIZADA DE ERRO
// AO FINALIZAR A INTEGRAÇÃO DA LIBFT E A PRINTF, APAGAR INCLUDES DESNECESSÁRIOS