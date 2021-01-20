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
	// int ttl_val=64;

	// opt_val = 1;
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		print_error("Socket file descriptor not received!");
	if (setsockopt(sockfd, SOL_IP, IP_TTL, &g_params.ttl, sizeof(ttl_val)) != 0)
		print_error("Setsockopt: Setting socket options to TTL failed!");
	g_params->sockfd = sockfd;
}

void send_ping()
{
	ft_bzero((void *)g_params->packet.buf, 84);
	g_params->packet.ip->version = 4;
	g_params->packet.ip->ttl = g_params.ttl;
	g_params->packet.ip->protocol = IPPROTO_ICMP;
	inet_pton(AF_INET, g_params->addr_str, &g_params->packet.ip->dst_addr)
}

// void	send_packet(void)
// {
// 	ft_bzero((void *)g_params->pckt.buf, PACKET_PING_SIZE);
// 	g_params->pckt.ip->version = 4;
// 	g_params->pckt.ip->ihl = sizeof(*g_params->pckt.ip) >> 2;
// 	g_params->pckt.ip->ttl = g_params->ttl;
// 	g_params->pckt.ip->protocol = IPPROTO_ICMP;
// 	inet_pton(AF_INET, g_params->addrstr, &g_params->pckt.ip->daddr);
// 	g_params->daddr = g_params->pckt.ip->daddr;
// 	g_params->pckt.hdr->type = ICMP_ECHO;
// 	g_params->pckt.hdr->code = 0;
// 	g_params->pckt.hdr->un.echo.id = g_params->pid;
// 	g_params->pckt.hdr->un.echo.sequence = g_params->seq++;
// 	g_params->pckt.hdr->checksum = checksum((unsigned short*)g_params->pckt.hdr,
// 	sizeof(struct icmphdr));
// 	if (sendto(g_params->sockfd, (void *)&g_params->pckt, PACKET_PING_SIZE, 0,
// 	(void *)g_params->rec_in,
// 	sizeof(struct sockaddr_in)) < 0)
// 		errorstr("sendto Error");
// 	if (gettimeofday(&g_params->time.s, NULL) < 0)
// 		errorstr("gettimeofday Error\n");
// 	g_params->sended > 1 ? gettimeofday(&g_params->time.time_start, NULL) : 0;
// 	g_params->sended++;
// 	g_params->signals.send = 0;
// }

