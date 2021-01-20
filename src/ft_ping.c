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
        printf("SIGALRM signal");
}

void ping() {
	init_socket();
	printf("PING %s (%s) 56(84) bytes of data.\n", g_params->host,
	g_params->addr_str);
	int i = 0;
	while (!g_params->signals.end)
	{
		i++;
		if (g_params->signals.send) 
		{
			printf("tesstt %d\n", i++);
		}
	}
}

