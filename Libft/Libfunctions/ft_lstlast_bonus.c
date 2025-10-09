/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:14:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 12:52:01 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}
/* int main()
{
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *node4;
	t_list *node5;
	t_list *head;

	node1 = ft_lstnew("Node 1");
	node2 = ft_lstnew("Node 2");
	node3 = ft_lstnew("Node 3");
	node4 = ft_lstnew("Node 4");
	node5 = ft_lstnew("Node 5");

	node1->next = node2;
	node1->next->next = node3;
	node1->next->next->next = node4;
	node1->next->next->next->next = node5;

	head = node1;
	printf ("%p\n", ft_lstlast(head));
	printf ("%p\n", node5);
} */