/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	get_function(va_list args, t_flags flags)
{
	char	*base;
	char	*base2;

	base = "0123456789abcdef";
	base2 = "0123456789ABCDEF";
	if (flags.type == 'c')
		return (print_char(va_arg(args, int), flags));
	if (flags.type == 's')
		return (print_str(va_arg(args, char *), flags));
	if (flags.type == 'p')
		return (print_ptr(va_arg(args, void *), flags));
	if (flags.type == 'd' || flags.type == 'i')
		return (handle_int((long long) va_arg(args, int), flags));
	if (flags.type == 'u')
		return (handle_int((long long) va_arg(args, unsigned int), flags));
	if (flags.type == 'x')
		return (handle_hex(va_arg(args, unsigned int), flags, base));
	if (flags.type == 'X')
		return (handle_hex(va_arg(args, unsigned int), flags, base2));
	if (flags.type == '%')
		return (print_char('%', flags));
	return (-1);
}

t_flags	set_to_zero(void)
{
	t_flags	flags;

	flags.hash = 0;
	flags.plus = 0;
	flags.zero = 0;
	flags.align = 0;
	flags.space = 0;
	flags.width = 0;
	flags.dot = 0;
	flags.precision = 0;
	flags.type = 0;
	return (flags);
}

int	get_flags(va_list args, const char *f, t_flags flags, int i)
{
	while (is_first_flag(f[i]))
	{
		if (f[i] == '#')
			flags.hash = 1;
		else if (f[i] == '+')
			flags.plus = 1;
		else if (f[i] == '0')
			flags.zero = 1;
		else if (f[i] == '-')
			flags.align = 1;
		else if (f[i] == ' ')
			flags.space = 1;
		++i;
	}
	if (f[i] < '0' || f[i] > '9')
		flags.width = -1;
	while (f[i] >= '0' && f[i] <= '9')
		flags.width = flags.width * 10 + f[i++] - '0';
	flags.dot = (f[i] == '.');
	i += flags.dot;
	while (f[i] >= '0' && f[i] <= '9')
		flags.precision = flags.precision * 10 + f[i++] - '0';
	flags.type = f[i];
	return (get_function(args, flags));
}

int	is_valid_flag(char c)
{
	char	*flags;
	int		i;

	flags = " #+0-123456789.";
	i = -1;
	while (flags[++i])
		if (c == flags[i])
			return (1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	t_flags	flags;
	va_list	args;
	int		i;
	int		count;

	flags = set_to_zero();
	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += get_flags(args, &format[++i], flags, 0);
			while (is_valid_flag(format[i]))
				++i;
		}
		else
			count += ft_putchar(format[i]);
		++i;
	}
	return (va_end(args), count);
}
