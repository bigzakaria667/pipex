/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:14:19 by zel-ghab          #+#    #+#             */
/*   Updated: 2024/12/07 17:43:07 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexadecimal(unsigned int n, const char *hexdigit)
{
	char	buffer[32];
	int		rest;
	int		i;
	int		count;

	if (n == 0)
		return (write(1, "0", 1), 1);
	i = 0;
	while (n > 0)
	{
		rest = n % 16;
		buffer[i++] = hexdigit[rest];
		n = n / 16;
	}
	count = i;
	while (--i >= 0)
	{
		if (write(1, &buffer[i], 1) == -1)
			return (-1);
	}
	return (count);
}

static int	ft_unsigned(unsigned int n)
{
	char	digit;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_unsigned(n / 10);
	digit = '0' + (n % 10);
	count += write (1, &digit, 1);
	return (count);
}

static int	ft_address(void *ptr)
{
	unsigned long long	address;
	int					count;

	if (ptr == NULL)
		return (write(1, "0x0", 3), 3);
	address = (unsigned long long) ptr;
	count = write(1, "0x", 2);
	count += ft_hexadecimalong(address);
	return (count);
}

static int	ft_check(char a, va_list args)
{
	if (a == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (a == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (a == 'p')
		return (ft_address(va_arg(args, void *)));
	else if (a == 'd' || a == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (a == 'u')
		return (ft_unsigned(va_arg(args, unsigned int)));
	else if (a == 'x')
		return (ft_hexadecimal(va_arg(args, int), "0123456789abcdef"));
	else if (a == 'X')
		return (ft_hexadecimal(va_arg(args, int), "0123456789ABCDEF"));
	else if (a == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_check(format[i], args);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
static int	main(void)
{
	char *a = "9876asds5";
	char *z = "Coucou";

	ft_printf("%c, %s, %p, %p, %d, %i, %u, %x, %X, %%, 
	Zakaria", 'a', "Ekip", z, a, 12, 12, 1222, 1731, 1731);
	write (1, "\n", 1);
	printf("%c, %s, %p, %p, %d, %i, %u, %x, %X, %%, 
	Zakaria", 'a', "Ekip", z, a, 12, 12, 1222, 1731, 1731);
}
*/
