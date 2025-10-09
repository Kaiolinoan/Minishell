/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:41:09 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 12:50:19 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst)
	{
		if (*lst)
		{
			temp = ft_lstlast(*lst);
			temp->next = new;
		}
		else
			*lst = new;
	}
}
/* int main()
{
	t_list *node1;
	t_list *node2;
	t_list *new;
	t_list *head;
	t_list *temp;

	node1 = ft_lstnew("1");
	node2 = ft_lstnew("2");
	new = ft_lstnew("3");

	node1->next = node2;
	node2->next = NULL;

	head = node1;
	temp = head;
	printf("Before function:\n");
	while (temp)
	{
		printf("%s ", (char*)temp->content);
		temp = temp->next;
	}
	ft_lstadd_back(&head, new);
	temp = head;
	printf("\nAfter function:\n");
	while (temp)
	{
		printf("%s ", (char*)temp->content);
		temp = temp->next;
	}
	free(node1);
	free(new);
} */