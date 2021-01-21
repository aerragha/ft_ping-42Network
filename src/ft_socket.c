/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <aerragha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:58:04 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/19 16:58:04 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_socket()
{
	int sockfd;
	// int opt_val;

	// opt_val = 1;
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		print_error("Socket file descriptor not received!");
	if (setsockopt(sockfd, SOL_IP, IP_TTL, &g_params->ttl, sizeof(g_params->ttl)) != 0)
		print_error("Setsockopt: Setting socket options to TTL failed!");
	g_params->sockfd = sockfd;
}

void send_ping()
{
	ft_bzero((void *)g_params->packet.buf, 84);
	g_params->packet.ip->version = 4;
	// g_params->pckt.ip->ihl = sizeof(*g_params->packet.ip) >> 2;
	g_params->packet.ip->ttl = g_params->ttl;
	g_params->packet.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, g_params->addr_str, &g_params->packet.ip->daddr);
	g_params->daddr = g_params->packet.ip->daddr;
	g_params->packet.hdr->type = ICMP_ECHO;
	g_params->packet.hdr->code = 0;
	g_params->packet.hdr->un.echo.id = g_params->pid;
	g_params->packet.hdr->un.echo.sequence = g_params->seq++;
	g_params->packet.hdr->checksum = checksum((unsigned short*)g_params->packet.hdr, sizeof(struct icmphdr));
	if (sendto(g_params->sockfd, (void *)&g_params->packet, 84, 0, 
	(void *)g_params->rec_in, sizeof(struct sockaddr_in)) < 0)
		print_error("Error: sendto is failed");
	if (gettimeofday(&g_params->time.s, NULL) < 0)
		print_error("Error: gettimeofday is failed");
	if (g_params->sended == 0) 
	{
		gettimeofday(&g_params->time.time_start, NULL);
		g_params->sended++;
	}
	g_params->signals.send = 0;
}

void	init_header()
{
	ft_bzero((void *)g_params->packet.buf, 84);
	ft_bzero(&g_params->res, sizeof(t_res));
	g_params->res.iov->iov_base = (void *)g_params->packet.buf;
	g_params->res.iov->iov_len = sizeof(g_params->packet.buf);
	g_params->res.msg.msg_iov = g_params->res.iov;
	g_params->res.msg.msg_iovlen = 1;
	g_params->res.msg.msg_name = NULL;
	g_params->res.msg.msg_namelen = 0;
	g_params->res.msg.msg_flags = MSG_DONTWAIT;
}

void	print_verbose()
{
	char		str[50];

	printf("%d bytes from %s: type=%d code=%d\n",
	g_params->bytes - (int)sizeof(struct iphdr),
	inet_ntop(AF_INET, (void*)&g_params->packet.ip->saddr, str, 100),
	g_params->packet.hdr->type, g_params->packet.hdr->code);
}

void	calc_rtt()
{
	long double rtt;

	if (gettimeofday(&g_params->time.r, NULL) < 0)
		print_error("Error: gettimeofday is failed");
	g_params->received++;
	rtt = (g_params->time.r.tv_usec - g_params->time.s.tv_usec) / 1000000;
	rtt += (g_params->time.r.tv_sec - g_params->time.s.tv_sec);
	rtt *= 1000;
	g_params->time.rtt = rtt;
	if (rtt > g_params->time.max)
		g_params->time.max = rtt;
	if (rtt < g_params->time.min || g_params->time.min == 0.0)
		g_params->time.min = rtt;
	g_params->time.avg += rtt;
	g_params->time.sum_square += rtt * rtt;
}

void 	receive_packet()
{
	int ret;

	init_header();
	while (!g_params->signals.end)
	{
		if ((ret = recvmsg(g_params->sockfd, &g_params->res.msg, MSG_DONTWAIT)) > 0)
		{
			g_params->bytes = ret;
			if (g_params->packet.hdr->un.echo.id == g_params->pid)
			{
				calc_rtt();
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2Lf ms\n",
				g_params->bytes - (int)sizeof(struct iphdr), g_params->addr_str,
				g_params->packet.hdr->un.echo.sequence, g_params->packet.ip->ttl,
				g_params->time.rtt);
			}
			else if (g_params->verbose == 1)
				print_verbose();
		}
	}
}
