/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:43:05 by slazar            #+#    #+#             */
/*   Updated: 2023/06/14 07:53:09 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include <stdlib.h>
int main (int ac, char **av)
{
    if (ac == 4)
    {
        int a =atoi(av[1]);
        int b = atoi(av[3]);
        if(av[2][0] == '+')
            printf("%d",(a+b));
        else if (av[2][0] == '-')
            printf("%d",(a-b));
        else if (av[2][0] == '*')
            printf("%d",(a*b));
        else if (av[2][0] == '/')
            printf("%d",(a/b));
        else if (av[2][0] == '%')
            printf("%d",(a%b));
    }
    printf("\n");
}