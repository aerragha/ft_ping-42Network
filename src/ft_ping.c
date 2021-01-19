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
	if (getaddrinfo(av, NULL, &hints, &servinfo) != 0)
		return (0);
	g_params->rec_in = (struct sockaddr_in *)servinfo->ai_addr;
	return (1);
}

