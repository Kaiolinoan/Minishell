/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:51:07 by klino-an          #+#    #+#             */
/*   Updated: 2025/06/02 17:28:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (NULL);
	i = 0;
	str = ft_strdup(s);
	if (str)
	{
		while (s[i])
		{
			str[i] = (f)(i, s[i]);
			i++;
		}
	}
	return (str);
}
/*
static char	sla_function(unsigned int n, char c)
{
	c += n;
	return (c);
}

 int main ()
{
	char str[] = "ola";
	printf ("%s", ft_strmapi(str, sla_function));
} */