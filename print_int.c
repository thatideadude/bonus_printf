/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_mag(long long nb)
{
	int	mag;

	if (!nb)
		return (1);
	mag = 0;
	while (nb)
	{
		nb /= 10;
		mag++;
	}
	return (mag);
}

int	put_nbr(unsigned long long nb)
{
	int	count;

	count = 0;
	if (nb > 9)
		count += put_nbr(nb / 10);
	return (count + ft_putchar("0123456789"[nb % 10]));
}

int	print_precision(long long n, t_flags flags)
{
	int					count;
	int					digits;
	unsigned long long	nb;

	count = 0;
	nb = (unsigned long long) n;
	if (n < 0)
		nb = -(unsigned long long) n;
	digits = find_mag(nb);
	while (digits < flags.precision)
	{
		count += ft_putchar('0');
		digits++;
	}
	count += put_nbr(nb);
	return (count);
}

int	print_padded_right(long long n, t_flags flags, int num_len, int sign)
{
	int					count;
	int					wpad;

	count = 0;
	if (flags.precision > num_len)
		num_len = flags.precision;
	wpad = flags.width - num_len - sign;
	if (!flags.zero || flags.dot)
		while (wpad-- > 0)
			count += ft_putchar(' ');
	if (n < 0)
		count += ft_putchar('-');
	else if (flags.plus)
		count += ft_putchar('+');
	else if (flags.space)
		count += ft_putchar(' ');
	if (flags.zero && !flags.dot)
		while (wpad-- > 0)
			count += ft_putchar('0');
	if (!(n == 0 && flags.dot && flags.precision == 0))
		count += print_precision(n, flags);
	return (count);
}

int	print_padded_left(long long n, t_flags flags, int num_len, int sign)
{
	int					count;
	int					wpad;

	count = 0;
	if (n == 0 && flags.dot && flags.precision == 0)
		num_len = 0;
	if (flags.precision > num_len)
		num_len = flags.precision;
	wpad = flags.width - num_len - (sign == 1);
	if (n < 0)
		count += ft_putchar('-');
	else if (flags.plus)
		count += ft_putchar('+');
	else if (flags.space)
		count += ft_putchar(' ');
	if (!(n == 0 && flags.dot && flags.precision == 0))
		count += print_precision(n, flags);
	while (wpad-- > 0)
		count += ft_putchar(' ');
	return (count);
}
