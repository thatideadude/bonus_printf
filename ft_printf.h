/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcemon <marcemon@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:30:02 by marcemon          #+#    #+#             */
/*   Updated: 2025/04/27 19:58:54 by marcemon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct s_flags
{
	int		hash;
	int		plus;
	int		zero;
	int		align;
	int		space;
	int		width;
	int		dot;
	int		precision;
	char	type;
}	t_flags;

int		ft_printf(const char *format, ...);
int		get_flags(va_list args, const char *format, t_flags flags, int i);
int		is_valid_flag(char c);
int		get_function(va_list args, t_flags flags);
t_flags	set_to_zero(void);

int		print_char(char c, t_flags flags);
int		ft_putchar(char c);
int		align_char(char c, t_flags flags);

int		print_str(char *str, t_flags flags);
int		ft_putstr(char *str);
int		ft_strlen(char *str);
int		align_str(char *str, t_flags flags);

int		print_ptr(void *ptr, t_flags flags);

int		handle_int(long long nb, t_flags flags);
int		handle_hex(unsigned int nb, t_flags flags, char *base);
int		is_first_flag(char c);

int		find_mag(long long nb);
int		put_nbr(unsigned long long nb);
int		print_precision(long long n, t_flags flags);
int		print_padded_right(long long n, t_flags flags, int num_len, int sign);
int		print_padded_left(long long n, t_flags flags, int num_len, int sign);

int		find_hex_mag(unsigned long long nb);
int		put_hex(unsigned long long nb, char *base);
int		print_hex_precision(unsigned long long nb, t_flags flags, char *base);
int		print_hex_right(unsigned long long nb, t_flags flags, char *b, int ox);
int		print_hex_left(unsigned long long nb, t_flags flags, char *b, int ox);

#endif
