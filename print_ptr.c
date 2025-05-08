/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	addr_size(unsigned long addr)
{
	int	size;

	size = 0;
	if (!addr)
		return (1);
	while (addr)
	{
		++size;
		addr /= 16;
	}
	return (size);
}

int	print_addr(unsigned long nb, char *base, int first)
{
	int	i;

	i = 0;
	if (first)
		i += ft_putstr("0x");
	if (nb > 15)
		i += print_addr(nb / 16, base, 0);
	return (i + ft_putchar(base[nb % 16]));
}

int	align_ptr(unsigned long nb, char *base, t_flags flags)
{
	int		i;
	char	pad;

	pad = ' ';
	if (flags.zero)
		pad = '0';
	i = print_addr(nb, base, 1);
	while (i < flags.width)
		i += ft_putchar(pad);
	return (i);
}

int	no_align_ptr(unsigned long nb, char *base, t_flags flags)
{
	int		i;

	if (flags.zero)
	{
		i = ft_putstr("0x");
		while (i < flags.width - addr_size(nb))
			i += ft_putchar('0');
		return (i + print_addr(nb, base, 0));
	}
	else
	{
		i = 0;
		while (i + addr_size(nb) + ft_strlen("0x") < flags.width)
			i += ft_putchar(' ');
		i += ft_putstr("0x");
	}
	return (i + print_addr(nb, base, 0));
}

int	print_ptr(void *ptr, t_flags flags)
{
	if (flags.align)
		flags.zero = 0;
	if (flags.align)
		return (align_ptr((unsigned long) ptr, "0123456789abcdef", flags));
	return (no_align_ptr((unsigned long) ptr, "0123456789abcdef", flags));
}
