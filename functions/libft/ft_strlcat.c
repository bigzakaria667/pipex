/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:39:35 by zel-ghab          #+#    #+#             */
/*   Updated: 2024/11/12 21:20:19 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	max_copy;
	size_t	i;

	src_len = 0;
	dest_len = 0;
	i = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (dest_len >= size)
		return (src_len + size);
	max_copy = size - dest_len - 1;
	while (i < max_copy && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
/*
int	main()
{
	char dest[20] = "Hello, ";
	const char src[] = "World!";
	size_t destsize = 20;

	ft_strlcat(dest, src, destsize);
	printf("%s", dest);
}
*/
