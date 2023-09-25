/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:47:29 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 16:09:23 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_export(t_pip *p)
{
	int	i;

	i = 0;
	if (p->export)
		while (p->export[i])
			i++;
	return (i);
}

void	ft_export_2(t_pip *p, t_cmd *cmds, int i)
{
	int	index;

	index = 0;
	while (cmds->args[++i])
	{
		g_global.status = ft_export_help(p, cmds->args[i]);
		if (g_global.status == 1)
			index = 1;
	}
	if (index == 1)
		g_global.status = 1;
}

void	ft_export(t_pip *p, t_cmd *cmds)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	if (!cmds->args[i])
		print_export(p);
	else
		ft_export_2(p, cmds, 0);
}

char	*remove_plus(char *new)
{
	int		i;
	int		k;
	char	*ret;

	i = 0;
	k = 0;
	ret = malloc(sizeof(char) * ft_strlen(new));
	if (!ret)
		return (NULL);
	while (new[i] != '+')
		ret[k++] = new[i++];
	i++;
	while (new[i])
		ret[k++] = new[i++];
	ret[k] = '\0';
	return (ret);
}
