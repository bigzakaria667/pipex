/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:51:08 by zel-ghab          #+#    #+#             */
/*   Updated: 2024/10/29 18:24:00 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	while (len >= 0)
	{
		if (s[len] == (unsigned char) c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
/*#include <stdio.h>
int	main()
{
	printf("%s", ft_strrchr("hello", '\0'));
}*/
