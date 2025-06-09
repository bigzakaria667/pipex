/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimalong.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:13:16 by zel-ghab          #+#    #+#             */
/*   Updated: 2024/12/07 15:47:31 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexadecimalong(unsigned long long n)
{
	int	digit;
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_hexadecimalong(n / 16);
	digit = (n % 16);
	count += ft_putchar("0123456789abcdef"[digit]);
	return (count);
}
