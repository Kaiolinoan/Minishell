/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:04:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 11:01:57 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

/* int main()
{
	t_list *lst;
	t_list *new;
	t_list *head;
	t_list *temp;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (1);
	new = malloc(sizeof(t_list));
	if (!new)
		return (1);

	lst->content = "2";
	new->content = "1";

	lst->next = new;
	new->next = NULL;

	head = lst;
	temp = head;
	printf("Before function:\n");
	while (temp)
	{
		printf("%s ", (char*)temp->content);
		temp = temp->next;
	}
	lst->next = NULL;
	ft_lstadd_front(&head, new);
	temp = head;
	printf("\nAfter function:\n");
	while (temp)
	{
		printf("%s ", (char*)temp->content);
		temp = temp->next;
	}
	free(lst);
	free(new);
} */