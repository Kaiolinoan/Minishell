/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:23:04 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 17:29:41 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (!dest || !src)
		return (NULL);
	i = 0;
	pdest = (unsigned char *)dest;
	psrc = (const unsigned char *)src;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
/* int main()
{
 char src[]= "esse texto vai ser copiado.";
	char dest[] = "askjdhkasjhdkjashdkjashdkjashdkas";

	ft_memcpy(dest, src, ft_strlen(src));
	printf("%s", dest);
} */