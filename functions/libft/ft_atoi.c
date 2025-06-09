/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:15:32 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/04/01 15:17:37 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(int n)
{
	if (n < 0)
		return (0);
	else
		return (-1);
}

long	ft_atoi(const char *str)
{
	int					i;
	int					signe;
	unsigned long long	result;

	result = 0;
	i = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		if (result >= 9223372036854775807)
			return (ft_overflow(signe));
		result += str[i] - 48;
		i++;
	}
	return (result * (long)signe);
}

/*
#include <stdio.h>
int main()
{
	char str[] = "    -214748364714135354531353113513135153";
	printf("%d", ft_atoi(str));
	return (0);
}
*/
