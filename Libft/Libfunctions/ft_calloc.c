/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:25:57 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 14:35:57 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*p;

	if (num == 0 || size == 0)
		p = malloc(0);
	else if (num <= ((size_t)-1) / size)
		p = malloc(num * size);
	else
		return (NULL);
	if (!p)
		return (NULL);
	ft_bzero(p, num * size);
	return (p);
}

/* int	main(void)
{
 int temp = 5;
	printf ("Calloc\n");
	int i = 0;
	int *arr = (int *)calloc(temp, 0);
	if (!arr)
		return (1);
	while (i < 5)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
	printf ("ft_calloc\n");
	int *arr2 = (int *)ft_calloc(0, 0);
	if (!arr2)
		return (1);
	i = 0;
	while (i < 5)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
	printf ("Comparacao:\n");
	if (memcmp(arr, arr2, 5) == 0)
		printf ("certo!");
	else
		printf("errado!");
	free(arr);

} */
