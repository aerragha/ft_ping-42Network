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



void print_error(char *error)
{
    printf("%s\n", error);
    exit(0);
}


void parse(int ac, char **av) 
{
    (void)ac;
    (void)av;
    int i;

    i = 0;

    while (++i < ac) {
        printf("%d\t%s\n", i, av[i]);
        if (av[i][0] == '-') 
        {
            if (av[i][1] == 'v')      
            else
                print_error("Usage: ft_ping [-v verbose] [-h help] hostname");
        }
    }
}