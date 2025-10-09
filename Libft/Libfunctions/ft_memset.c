/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:48:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 17:28:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	c_pointer;
	unsigned char	*s_pointer;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	c_pointer = (unsigned char)c;
	s_pointer = (unsigned char *)s;
	while (i < n)
	{
		s_pointer[i] = c_pointer;
		i++;
	}
	return (s);
}

/* int main()
{
	char str[] = "string";
	int c = 'a';

	printf("Antes: %s\n", str);
	ft_memset(str, c, 3);
	printf("Depois: %s\n", str);
} */