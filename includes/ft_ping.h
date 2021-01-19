/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <aerragha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:13:16 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/16 17:41:18 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>



typedef struct      s_params 
{
    struct sockaddr_in	*rec_in;
    int     verbose;
    char	*host;
    char	addr_str[INET_ADDRSTRLEN];
}                   t_params;

extern t_params *g_params;

void    print_error(char *error);
void    parse(int ac, char **av);
void    init_params();
void    ft_bzero(void *s, size_t n);
int     get_infos(char *av);