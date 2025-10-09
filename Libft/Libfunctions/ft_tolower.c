/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:38:39 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/11 12:45:07 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 65 && c <= 90))
		return (c + 32);
	return (c);
}

/* int main()
{
	int a = 'a';
	int b = 'A';
	int c = '\t';

	printf("%d\n", ft_tolower(a));
	printf("%d\n", ft_tolower(b));
	printf("%d\n", ft_tolower(c));

	printf("\n");

	printf("%d\n", tolower(a));
	printf("%d\n", tolower(b));
	printf("%d\n", tolower(c));

} */