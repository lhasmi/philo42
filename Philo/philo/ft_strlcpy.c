/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:52:22 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/20 03:22:46 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlcpy(char	*dst, const char	*src, size_t dstsize)
{
	size_t	i;
	char	*dest;
	char	*srce;

	dest = ((char *)dst);
	srce = ((char *)src);
	if (!dst)
		return (ft_strlen(srce));
	if (dstsize == 0)
		return (ft_strlen(srce));
	i = 0;
	while ((srce[i] != '\0') && (i < dstsize - 1))
	{
		dest[i] = srce[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(srce));
}
