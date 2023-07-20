/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:39:26 by lailah            #+#    #+#             */
/*   Updated: 2023/07/20 03:22:01 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(EXIT_FAILURE);
}

// void ft_error(char *str, int exit_code)
// {
//     perror(str);
//     if (exit_code == 1)
//         exit(exit_code);
//     else if (exit_code == 0)
//         exit(EXIT_SUCCESS);
// }
