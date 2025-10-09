/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:38:39 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/03 13:01:49 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;

	if (!dst || !src)
		return (0);
	i = 0;
	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (size_src);
}

/* int	main(void)
{
	char	src[] = "ola tudo bem";
	char	dst[] = "";
	size_t	i;

	i = 12;
	printf("%zu\n", ft_strlcpy(dst, src, i));
	// printf("%zu\n", strlcpy(dst, src, i));
	ft_strlcpy(dst, src, i);
	// strlcpy(dst, src, i);
	printf("%s\n", dst);
	// printf("%s\n", dst);
} */
