/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:12:19 by klino-an          #+#    #+#             */
/*   Updated: 2025/07/01 16:12:57 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_nb(int n)
{
	size_t	count;
	int		nb;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		count;

	nb = n;
	count = count_nb(nb);
	str = malloc(count + 1);
	str[count] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	else if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--count] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}
/* int main()
{
	printf("%s", ft_itoa(-2147483648));
} */