/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:04:43 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/28 15:04:43 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_matriz(char **matriz)
{
    size_t i;

    i = 0;
    while (matriz[i])
        free(matriz[i++]);
    free(matriz);
}