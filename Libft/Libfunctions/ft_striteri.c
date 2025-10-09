/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:19:32 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 17:28:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s != NULL && f)
	{
		while (s[i])
		{
			(f)(i, &s[i]);
			i++;
		}
	}
}

/* static void	sla_function(unsigned int n, char *c)
{
	*c = *c + n;
}

 int main ()
{
	char	str[] = "ola";

	printf ("Antes: %s\n", str);
	ft_striteri(str, sla_function);
	printf ("Depois: %s\n", str);
} */
