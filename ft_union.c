/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_union.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:17:10 by slazar            #+#    #+#             */
/*   Updated: 2023/06/13 23:22:38 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int ac, char **av)
{
    int i,j,k;
    i = 0;
    j = i;
    char str[20000];
    if (ac == 3)
    {
        while (av[1][i])
        {
            str[i] = av[1][i];
            i++;
        }
        while (av[2][j])
        {
            str[i+j] = av[2][j];
            j++;
        }
        str[i+j] = '\0';
        i = -1;
        while(str[++i])
        {
            k = i;
            while(k >= 1)
            {
                if(str[i] == str[k-1])
                    break;
                k--;
            }
            if(k == 0)
                write(1,&str[i],1);
        }
    }
    write(1,"\n",1);
}