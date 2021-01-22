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

void	print_statistics()
{
	struct timeval	start;
	struct timeval	end;
	double			loss;
	long double		time;
	long double		mdev;

	gettimeofday(&g_params->time.time_end, NULL);
	start = g_params->time.time_start;
	end = g_params->time.time_end;
	loss = (g_params->sended - g_params->received)
	/ g_params->sended * 100.0;
	time = (end.tv_usec - start.tv_usec) / 1000000.0;
	time += (end.tv_sec - start.tv_sec);
	time *= 1000.0;
	g_params->time.avg /= g_params->sended;
	mdev = sqrt((g_params->time.sum_square / g_params->sended) -
		g_params->time.avg * g_params->time.avg);
	printf("\n--- %s ping statistics ---\n", g_params->host);
	printf("%d packets transmitted, %d received, ",
	g_params->sended, g_params->received);
	printf("%.0f%% packet loss, time %.0Lfms\n", loss, time);
	if (g_params->received != 0)
		printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n",
		g_params->time.min, g_params->time.avg,
		g_params->time.max, mdev);
}


void handle_signal(int sig) {
    if (sig == SIGINT)
    {
		print_statistics();
		g_params->signals.end = 1;
	}
    else if (sig == SIGALRM)
        g_params->signals.send = 1;
}

void ping() {
	init_socket();
	printf("PING %s (%s) 56(84) bytes of data.\n", g_params->host, g_params->addr_str);
	while (!g_params->signals.end)
	{
		if (g_params->signals.send)
		{
			send_ping();
			alarm(1);
			receive_packet();
		}
	}
}

