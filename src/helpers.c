/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <aerragha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:38:13 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/16 17:45:58 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params *g_params;

void print_error(char *error)
{
    printf("%s\n", error);
    exit(0);
}

void ft_bzero(void *s, size_t n)
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

void init_params()
{
    g_params = malloc(sizeof(t_params));
    ft_bzero(g_params, sizeof(t_params));
}

void parse(int ac, char **av) 
{
    int i;

    i = 0;
    while (++i < ac) {
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

