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
#include <signal.h>

typedef struct      s_packet
{
    char        buf[84];
    struct      iphdr *ip;
    struct      icmphdr *hdr;
}                   t_packet;

typedef struct      s_signals
{
    int     send;
    int     end;
}                   t_signals;

typedef struct	s_time
{
	struct timeval	time_start;
	struct timeval	time_end;
	struct timeval	s;
	struct timeval	r;
	long double		rtt;
	long double		min;
	long double		max;
	long double		avg;
	long double		sum_square;
}				t_time;

typedef struct	s_res
{
	struct iovec	iov[1];
	struct msghdr	msg;
}				t_res;

typedef struct      s_params 
{
    struct sockaddr_in	*rec_in;
    int     verbose;
    char	*host;
    char	addr_str[INET_ADDRSTRLEN];
    int     sockfd;
    int     daddr;
    pid_t	pid;
    int		seq;
    int		bytes;
    t_res		        res;
    t_time				time;
    t_signals			signals;
}                   t_params;

extern t_params *g_params;

void    print_error(char *error);
void    parse(int ac, char **av);
void    init_params();
void    ft_bzero(void *s, size_t n);
int     get_infos(char *av);
void    handle_signal(int sig);
void	ping();
void	init_socket();
unsigned short	checksum(unsigned short *data, int len);
void    send_ping()

