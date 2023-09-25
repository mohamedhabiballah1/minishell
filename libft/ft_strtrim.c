/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:13 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/17 15:48:13 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*dst;
	int		i;
	int		start;
	int		end;
	int		newlen;

	start = 0;
	while (str[start] && check(str[start], set))
		start++;
	end = strlen(str);
	while ((end > start) && check(str[end - 1], set))
		end--;
	newlen = (end - start);
	dst = malloc(sizeof(char) * newlen + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dst[i] = str[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}
