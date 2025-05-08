/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_hex_mag(unsigned long long nb)
{
	int	mag;

	mag = 1;
	while (nb >= 16)
	{
		nb /= 16;
		++mag;
	}
	return (mag);
}

int	put_hex(unsigned long long nb, char *base)
{
	int		count;

	count = 0;
	if (nb > 15)
		count += put_hex(nb / 16, base);
	return (count + ft_putchar(base[nb % 16]));
}

int	print_hex_precision(unsigned long long nb, t_flags flags, char *base)
{
	int	nmag;
	int	count;

	count = 0;
	nmag = find_hex_mag(nb);
	while (nmag < flags.precision)
	{
		count += ft_putchar('0');
		++nmag;
	}
	count += put_hex(nb, base);
	return (count);
}

int	print_hex_right(unsigned long long nb, t_flags flags, char *base, int ox)
{
	int	count;
	int	len;
	int	wpad;

	count = 0;
	ox = (flags.hash && nb);
	len = find_hex_mag(nb);
	if (!nb && flags.dot && !flags.precision)
		len = 0;
	if (flags.precision > len)
		len = flags.precision;
	wpad = flags.width - len - ox * 2;
	if (!flags.zero || flags.dot)
		while (wpad-- > 0)
			count += ft_putchar(' ');
	if (ox && (base[15] == 'F'))
		count += ft_putstr("0X");
	if (ox && (base[15] == 'f'))
		count += ft_putstr("0x");
	if (flags.zero && !flags.dot)
		while (wpad-- > 0)
			count += ft_putchar('0');
	if (!(nb == 0 && flags.dot && !flags.precision))
		count += print_hex_precision(nb, flags, base);
	return (count);
}

int	print_hex_left(unsigned long long nb, t_flags flags, char *base, int ox)
{
	int	count;
	int	len;
	int	wpad;

	count = 0;
	ox = (flags.hash && nb);
	len = find_hex_mag(nb);
	if (!nb && flags.dot && !flags.precision)
		len = 0;
	if (flags.precision > len)
		len = flags.precision;
	wpad = flags.width - len - ox * 2;
	if (ox && (base[15] == 'F'))
		count += ft_putstr("0X");
	if (ox && (base[15] == 'f'))
		count += ft_putstr("0x");
	if (!(nb == 0 && flags.dot && !flags.precision))
		count += print_hex_precision(nb, flags, base);
	while (wpad-- > 0)
		count += ft_putchar(' ');
	return (count);
}
