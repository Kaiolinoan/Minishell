/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:23:16 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 17:29:20 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_pointer;
	unsigned char	chr;
	size_t			i;

	if (!s)
		return (NULL);
	s_pointer = (unsigned char *)s;
	chr = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s_pointer[i] == chr)
			return ((unsigned char *)&s_pointer[i]);
		i++;
	}
	return (NULL);
}

/* int main()
{
   char str[] = "eu vou procurar uma letra nessa string";

	printf("%s\n", (char *)memchr(str, 'v', strlen(str)));
	printf("%s\n", (char *)ft_memchr(str, 'v', strlen(str)));
}
} */