/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:23:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/29 18:12:37 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

int		ft_printf(const char *str, ...);
int		print_char(int c);
int		print_str(const char *str);
int		print_pointer(void *ptr);
int		print_numbers(int nb);
int		print_unsigned(unsigned int nb);
int		print_hex(unsigned long nb, const char *hex);
char	*itoa_printf(int n);
size_t	ft_strlen2(const char *str);

#endif