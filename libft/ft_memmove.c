/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:50:16 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/07/29 11:21:20 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sr;

	dst = (unsigned char *) dest;
	sr = (unsigned char *) src;
	if (dst == NULL && sr == NULL)
		return (NULL);
	if (dst < sr)
	{
		ft_memcpy(dst, sr, n);
	}
	else
	{
		while (n > 0)
		{
			dst[n - 1] = sr[n - 1];
			n--;
		}
	}
	return (dst);
}
