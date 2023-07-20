/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:28:33 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 17:18:28 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if (c >= '\t' && c <= '\r')
		return (1);
	return (0);
}

static int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	output;
	char	*s;

	s = ((char *)str);
	i = 0;
	while (s[i] == (' ') || is_space(s[i]))
		i++;
	sign = 1;
	if (s[i] == ('-') || s[i] == ('+'))
	{
		if (s[i] == ('-'))
			sign = -1;
		i++;
	}
	output = 0;
	while (is_digit (s[i]))
	{
		output = output * 10 + s[i] - '0';
		i++;
	}
	output = sign * output;
	return (output);
}
