/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:15:10 by zel-ghab          #+#    #+#             */
/*   Updated: 2024/11/16 18:39:57 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(char *str, long countunit, long signe)
{
	long	i;
	long	temp;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < countunit - 1)
	{
		temp = str[i + signe];
		str[i + signe] = str[countunit - 1 + signe];
		str[countunit - 1 + signe] = temp;
		i++;
		countunit--;
	}
	return (str);
}

static int	ft_count(long n)
{
	int	countunit;

	countunit = 0;
	while (n != 0)
	{
		n = n / 10;
		countunit++;
	}
	return (countunit);
}

static char	*ft_exeption(void)
{
	char	*str;

	str = malloc(2);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_conversion(char *str, long countunit, int signe, long n)
{
	long	i;
	long	temp;

	if (str == NULL)
		return (NULL);
	i = 0;
	if (signe == 1)
	{
		str[i] = '-';
		i++;
	}
	while (i < countunit + signe)
	{
		temp = n % 10;
		str[i] = temp + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	countunit;
	long	negatif;
	long	nb;

	nb = (long) n;
	negatif = 0;
	if (nb == 0)
		return (ft_exeption());
	if (nb < 0)
	{
		negatif = 1;
		nb = nb * -1;
	}
	countunit = ft_count(nb);
	str = malloc(countunit + 1 + negatif);
	if (str == NULL)
		return (NULL);
	str = ft_conversion(str, countunit, negatif, nb);
	if (str == NULL)
		return (NULL);
	str = ft_convert(str, countunit, negatif);
	if (str == NULL)
		return (NULL);
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-586));
}
*/
