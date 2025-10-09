/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:38:39 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/11 12:45:07 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 97 && c <= 122))
		return (c - 32);
	return (c);
}
/*
int	main(void)
{
	int a = 'a';
	int b = 'A';
	int c = '\t';

	printf("%d\n", ft_toupper(a));
	printf("%d\n", ft_toupper(b));
	printf("%d\n", ft_toupper(c));

	printf("\n");

	printf("%d\n", toupper(a));
	printf("%d\n", toupper(b));
	printf("%d\n", toupper(c));

} */