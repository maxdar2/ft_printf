/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgenova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:15:57 by dgenova           #+#    #+#             */
/*   Updated: 2022/01/22 17:16:01 by dgenova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		lenght;
	char	*dest;

	lenght = ft_strlen(s1);
	dest = (char *) malloc ((lenght + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_memmove(dest, s1, lenght);
	dest[lenght] = '\0';
	return (dest);
}
