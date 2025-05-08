/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_first_flag(char c)
{
	if (c == '#' || c == '+' || c == '0' || c == '-' || c == ' ')
		return (1);
	return (0);
}

int	handle_hex(unsigned int nb, t_flags flags, char *base)
{
	if (flags.zero && flags.dot)
		flags.zero = 0;
	if (flags.align)
		return (print_hex_left(nb, flags, base, 0));
	return (print_hex_right(nb, flags, base, 0));
}

int	handle_int(long long nb, t_flags flags)
{
	int					sign;
	int					num_len;
	unsigned long long	nbr;

	nbr = (unsigned long long)(nb * (nb >= 0)) - (nb * (nb < 0));
	num_len = find_mag(nbr);
	if (nb == 0 && flags.dot && flags.precision == 0)
		num_len = 0;
	sign = (nb < 0 || flags.plus || flags.space);
	if (flags.zero && flags.dot)
		flags.zero = 0;
	if (flags.align)
		return (print_padded_left(nb, flags, num_len, sign));
	return (print_padded_right(nb, flags, num_len, sign));
}
