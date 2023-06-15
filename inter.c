/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:11:59 by slazar            #+#    #+#             */
/*   Updated: 2023/06/13 23:22:30 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int if_exist(char c,char *str)
{
    int i = -1;
    while (str[++i])
    {
        if(str[i] == c)
            return 0;
    }
    return(1);
}

int main(int ac, char **av)
{
    char str[20000]={0};
    int i = -1;
    int j = 0;
    int k = 0;
    if (ac == 3)
    {
        while (av[1][++i])
        {
            j = -1;
            while (av[2][++j])
            {
                if (av[1][i] == av[2][j] && if_exist(av[1][i],str))
                {
                    write(1,&av[1][i],1);
                    str[k++] = av[1][i];
                }
            }
        }
    }
    write(1,"\n",1);
}