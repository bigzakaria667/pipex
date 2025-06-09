/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:10:37 by zel-ghab          #+#    #+#             */
/*   Updated: 2024/12/07 13:45:09 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;
	int	count;

	if (s == NULL)
		return (write (1, "(null)", 6));
	count = 0;
	i = 0;
	while (s[i])
	{
		count += write(1, &s[i], 1);
		i++;
	}
	return (count);
}
