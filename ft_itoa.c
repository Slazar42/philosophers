
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:36:10 by slazar            #+#    #+#             */
/*   Updated: 2023/06/13 23:36:11 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int count_numbers(int nb)
{
    int i = 1;
    while (nb)
    {
        nb = nb / 10;
        i++;
    }
    return (i - 1);
}
char	*ft_itoa(int nb)
{
    char *str;
    int i = 0;
    int c = count_numbers(nb);
    str = malloc(sizeof(char) *(c +1));
    str[c] = 0;
    while (nb)
    {
        str[--c] = nb % 10 + '0';
        nb = nb / 10;
    }
    return(str);
}

#include<stdio.h>
int main()
{
    // printf("%d\n",count_numbers(123332));
    printf("%s\n",ft_itoa(1555));
}