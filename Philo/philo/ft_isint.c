/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:26:31 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 02:35:11 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isint(char *arg)
{
	char	*min_int_str;
	char	*max_int_str;
	size_t	len;

	min_int_str = "-2147483648";
	max_int_str = "2147483647";
	len = ft_strlen(arg);
	if (*arg == '-')
	{
		if (len > ft_strlen(min_int_str) || (len == ft_strlen(min_int_str)
				&& ft_strncmp(arg, min_int_str, ft_strlen(min_int_str)) > 0))
			return (false);
	}
	else
	{
		if (len > ft_strlen(max_int_str) || (len == ft_strlen(max_int_str)
				&& ft_strncmp(arg, max_int_str, ft_strlen(max_int_str)) > 0))
			return (false);
	}
	return (true);
}
