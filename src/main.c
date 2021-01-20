/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerragha <aerragha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:13:16 by aerragha          #+#    #+#             */
/*   Updated: 2021/01/16 18:49:25 by aerragha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


int     main(int ac, char **av)
{
    if (getuid() != 0) 
        print_error("ft_ping: You must be root");
    if (ac < 2) 
        print_error("Usage: ft_ping [-v verbose] [-h help] hostname");
    init_params();
    parse(ac, av);
    signal(SIGALRM, handle_signal);
	signal(SIGINT, handle_signal);
    ping();
    return 0;
}