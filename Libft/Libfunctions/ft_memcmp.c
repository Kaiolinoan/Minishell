/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:19:53 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/03 13:00:58 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1_pointer;
	unsigned char	*str2_pointer;
	size_t			i;

	if (!s1 || !s2)
		return (-1);
	str1_pointer = (unsigned char *)s1;
	str2_pointer = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1_pointer[i] != str2_pointer[i])
			return (str1_pointer[i] - str2_pointer[i]);
		i++;
	}
	return (0);
}

/* int main()
{
	char str1[] = "ola";
	char str2[] = "olaaa";

	printf("%d\n", ft_memcmp(str1, str2, 3));
	printf("%d\n", memcmp(str1, str2, 3));
} */