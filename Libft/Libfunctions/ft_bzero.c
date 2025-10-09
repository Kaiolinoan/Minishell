/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:51:08 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/03 13:00:23 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_pointer;
	size_t			i;

	if (s)
	{
		s_pointer = (unsigned char *)s;
		i = 0;
		while (i < n)
		{
			s_pointer[i] = 0;
			i++;
		}
	}
}
/* int main()
{
  char buffer[] = {1, 2, 3, 4 ,5 ,6 ,7 , 8, 9, 10};
   // char *str2 = "isto e uma string";
    size_t size = 10;
	size_t i;

	i = 0;
	 printf("Antes:\n");
	while (i < size)
	{
		printf("%d ", buffer[i]);
		i++;
	}
	i = 0;
    bzero(buffer, size);
    printf("\nDepois:\n");
	while (i < size)
	{
		printf("%d ", buffer[i]);
		i++;
	}

} */