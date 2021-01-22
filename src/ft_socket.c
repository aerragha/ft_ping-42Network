/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:43:36 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/22 11:49:37 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_socket(void)
{
	int sockfd;
	int opt_val;

	opt_val = 1;
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		print_error("Socket file descriptor not received!");
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &opt_val, sizeof(int)) < 0)
		print_error("Setsockopt: Setting socket options to TTL failed!");
	g_params->sockfd = sockfd;
}

void	send_ping(void)
{
	ft_bzero((void *)g_params->packet.buf, 84);
	g_params->packet.ip->version = 4;
	g_params->packet.ip->ihl = 5;
	g_params->packet.ip->ttl = g_params->ttl;
	g_params->packet.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, g_params->addr_str, &g_params->packet.ip->daddr);
	g_params->daddr = g_params->packet.ip->daddr;
	g_params->packet.hdr->type = ICMP_ECHO;
	g_params->packet.hdr->code = 0;
	g_params->packet.hdr->un.echo.id = g_params->pid;
	g_params->packet.hdr->un.echo.sequence = g_params->seq++;
	g_params->packet.hdr->checksum = checksum(
			(unsigned short*)g_params->packet.hdr, sizeof(struct icmphdr));
	if (sendto(g_params->sockfd, (void *)&g_params->packet, 84, 0,
				(void *)g_params->rec_in, sizeof(struct sockaddr_in)) < 0)
		print_error("Error: sendto is failed");
	if (gettimeofday(&g_params->time.s, NULL) < 0)
		print_error("Error: gettimeofday is failed");
	g_params->sended == 1 ? gettimeofday(&g_params->time.time_start, NULL) : 0;
	g_params->sended++;
	g_params->signals.send = 0;
}

void	init_header(void)
{
	t_res	*res;

	res = &g_params->res;
	ft_bzero((void *)g_params->packet.buf, 84);
	ft_bzero(res, sizeof(t_res));
	res->iov->iov_base = (void *)g_params->packet.buf;
	res->iov->iov_len = sizeof(g_params->packet.buf);
	res->msg.msg_iov = res->iov;
	res->msg.msg_iovlen = 1;
	res->msg.msg_name = NULL;
	res->msg.msg_namelen = 0;
	res->msg.msg_flags = MSG_DONTWAIT;
}

void	calc_rtt(void)
{
	long double rtt;

	if (gettimeofday(&g_params->time.r, NULL) < 0)
		print_error("Error: gettimeofday is failed");
	g_params->received++;
	rtt = (g_params->time.r.tv_usec - g_params->time.s.tv_usec) / 1000000.0;
	rtt += (g_params->time.r.tv_sec - g_params->time.s.tv_sec);
	rtt *= 1000.0;
	g_params->time.rtt = rtt;
	if (rtt > g_params->time.max)
		g_params->time.max = rtt;
	if (rtt < g_params->time.min || g_params->time.min == 0.0)
		g_params->time.min = rtt;
	g_params->time.avg += rtt;
	g_params->time.sum_square += rtt * rtt;
}

void	receive_packet(void)
{
	int ret;

	init_header();
	while (!g_params->signals.end)
	{
		ret = recvmsg(g_params->sockfd, &g_params->res.msg, MSG_DONTWAIT);
		if (ret > 0)
		{
			g_params->bytes = ret;
			if (g_params->packet.hdr->un.echo.id == g_params->pid)
			{
				calc_rtt();
				printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.1Lf ms\n",
						g_params->bytes - (int)sizeof(struct iphdr),
						g_params->addr_str,
						g_params->packet.hdr->un.echo.sequence,
						g_params->packet.ip->ttl, g_params->time.rtt);
			}
			else if (g_params->verbose == 1)
				print_verbose();
			return ;
		}
	}
}
