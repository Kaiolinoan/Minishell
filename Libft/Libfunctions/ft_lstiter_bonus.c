/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:29:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 10:54:44 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			(f)(lst->content);
			lst = lst->next;
		}
	}
}
/* void put_a(void *content)
{
	char	*str;

	str = (char *)content;
	str[0] = 'a';
}

int	main(void)
{
		while (s[i])
		{
			str[i] = (f)(i, s[i]);
			i++;
		}
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;
	t_list *temp;

	node1 = malloc(sizeof(t_list));
	node2 = malloc(sizeof(t_list));
	node3 = malloc(sizeof(t_list));
	node4 = malloc(sizeof(t_list));

	node1->content = ft_strdup("1");
	node2->content = ft_strdup("2");
	node3->content = ft_strdup("3");
	node4->content = ft_strdup("4");

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;;

	temp = node1;
	printf("Antes\n");
	while(temp)
	{
		printf("\n%s\n",  (char *)temp->content);
		temp = temp->next;
	}
	ft_lstiter(node1, put_a);
	temp = node1;
	printf("Depois:\n");
	while(temp)
	{
		printf("\n%s\n",  (char *)temp->content);
		temp = temp->next;
	}
} */