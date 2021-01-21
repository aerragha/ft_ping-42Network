/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <aerragha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:13:16 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/12 18:49:25 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

unsigned short	checksum(unsigned short *data, int len)
{
	unsigned long	checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(unsigned short);
	}
	if (len)
		checksum = checksum + *(unsigned char*)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
}

int get_infos(char *av)
{
	struct addrinfo hints;
    struct addrinfo *servinfo;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(av, NULL, &hints, &servinfo) != 0)
		return (0);
	g_params->rec_in = (struct sockaddr_in *)servinfo->ai_addr;
	return (1);
}


void handle_signal(int sig) {
    if (sig == SIGINT)
        {
			printf("SIGINT signal\n");
			g_params->signals.end = 1;
		}
    if (sig == SIGALRM)
        g_params->signals.send = 1;
}

void ping() {
	init_socket();
	printf("PING %s (%s) 56(84) bytes of data.\n", g_params->host,
	g_params->addr_str);
	while (!g_params->signals.end)
	{
		if (g_params->signals.send) 
		{
			send_ping()
			alarm(1);
			get_packet();
		}
	}
}

