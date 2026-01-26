/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:58:42 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/29 18:13:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_numbers(int nb)
{
	int		count;
	char	*str;

	count = 0;
	str = itoa_printf(nb);
	if (!str)
		return (-1);
	count += write(1, str, ft_strlen2(str));
	free(str);
	return (count);
}

int	print_unsigned(unsigned int nb)
{
	int		count;
	char	c;

	count = 0;
	if (nb >= 10)
		count += print_unsigned(nb / 10);
	c = nb % 10 + '0';
	count += write (1, &c, 1);
	return (count);
}
