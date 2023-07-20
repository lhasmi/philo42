/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:23:47 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 02:47:40 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_argv(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr && arr[i])
		{
			if (arr[i] != NULL)
				free(arr[i]);
			arr[i++] = NULL;
		}
		free(arr);
		arr = NULL;
	}
}
