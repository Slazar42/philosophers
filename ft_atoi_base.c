/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:24:45 by slazar            #+#    #+#             */
/*   Updated: 2023/06/14 10:25:56 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
int ft_power(int nbr, int power)
{
    int t = 1;
    if(power == 0)
        return(1);
    while (power)
    {
        t *= nbr;
        power--;
    }
    return(t);
}
int	ft_atoi_base(const char *str, int str_base)
{
    char s[200] = {0};
    int j = 0;

    int i = -1;
    while (str[++i])
        s[i]= str[i];
    i = -1;
    while (s[++i])
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    }
    char *b = "0123456789abcdef";
    i= 0;
    while (s[j])
        j++;
    int k = 0;
    int t;
    while (s[i])
    {
        k = 0;
        while (b[k] && k <= str_base)
        {
            if (b[k] == s[i])
                break;
            k++;
        }
        t += k*ft_power(str_base,j-1); 
        j--;
        i++;
    }
    return(t);
}


int main()
{
    printf("%d\n",ft_atoi_base("100010100",2));
}