/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:48:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 17:28:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_pointer;
	unsigned char	*src_pointer;
	size_t			i;

	if (!dest || !src)
		return (NULL);
	dst_pointer = (unsigned char *)dest;
	src_pointer = (unsigned char *)src;
	if (dst_pointer < src_pointer)
		return (ft_memcpy(dest, src, n));
	else
	{
		i = n;
		while (i > 0)
		{
			dst_pointer[i - 1] = src_pointer[i - 1];
			i--;
		}
	}
	return (dest);
}

/* int main()
{
		char str1[] = "ABCDEF";
	char str2[] = "ABCDEF";

	printf("%s\n",(char *)memmove(str1 + 2, str1, 4));
	printf("%s\n", (char *)ft_memmove(str2 + 2, str2, 4));

} */
