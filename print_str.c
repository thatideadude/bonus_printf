/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(char *str)
{
	char	*start;

	start = str;
	while (*str)
		++str;
	return (str - start);
}

int	ft_putstr(char *str)
{
	char	*start;

	if (!str)
		str = "(null)";
	start = str;
	while (*str)
		ft_putchar(*str++);
	return (str - start);
}

int	no_align_str(char *str, t_flags flags)
{
	int		i;
	int		j;
	int		str_len;
	int		print_len;
	char	pad;

	i = 0;
	j = 0;
	pad = ' ';
	if (flags.zero && !flags.dot)
		pad = '0';
	str_len = ft_strlen(str);
	print_len = str_len;
	if (flags.dot && flags.precision < str_len)
		print_len = flags.precision;
	while (i < flags.width - print_len)
		i += ft_putchar(pad);
	while (j < print_len)
	{
		i += ft_putchar(str[j]);
		j++;
	}
	return (i);
}

int	align_str(char *str, t_flags flags)
{
	int		i;
	int		j;
	int		str_len;
	int		print_len;
	char	pad;

	i = 0;
	j = 0;
	pad = ' ';
	str_len = ft_strlen(str);
	print_len = str_len;
	if (flags.dot && flags.precision < str_len)
		print_len = flags.precision;
	while (j < print_len)
	{
		i += ft_putchar(str[j]);
		j++;
	}
	while (i < flags.width)
		i += ft_putchar(pad);
	return (i);
}

int	print_str(char *str, t_flags flags)
{
	if (flags.align)
		flags.zero = 0;
	if (!str)
		str = "(null)";
	if (flags.align)
		return (align_str(str, flags));
	return (no_align_str(str, flags));
}
