/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:40:08 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/22 11:49:01 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params *g_params;

void	print_error(char *error)
{
	printf("%s\n", error);
	exit(0);
}

void	print_verbose(void)
{
	char		str[50];

	printf("%d bytes from %s: type=%d code=%d\n",
			g_params->bytes - (int)sizeof(struct iphdr),
			inet_ntop(AF_INET, (void*)&g_params->packet.ip->saddr, str, 100),
			g_params->packet.hdr->type, g_params->packet.hdr->code);
	g_params->ttl = 64;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buffer;
	size_t			i;

	buffer = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		buffer[i] = 0;
		i++;
	}
}

void	init_params(void)
{
	g_params = malloc(sizeof(t_params));
	ft_bzero(g_params, sizeof(t_params));
	g_params->packet.ip = (struct iphdr *)g_params->packet.buf;
	g_params->packet.hdr = (struct icmphdr *)(g_params->packet.ip + 1);
	g_params->time.min = 0.0;
	g_params->time.max = 0.0;
	g_params->signals.send = 1;
	g_params->signals.end = 0;
	g_params->ttl = 15;
	g_params->pid = getpid();
	g_params->seq = 1;
}

void	parse(int ac, char **av)
{
	int i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == 'v')
				g_params->verbose = 1;
			else
				print_error("Usage: ft_ping [-v verbose] [-h help] hostname");
		}
		else
		{
			g_params->host = av[i];
			if (!get_infos(av[i]))
			{
				printf("ft_ping: %s: ", g_params->host);
				print_error("Name or service not known");
			}
			inet_ntop(AF_INET, (void *)&g_params->rec_in->sin_addr,
					g_params->addr_str, INET_ADDRSTRLEN);
			return ;
		}
	}
}
