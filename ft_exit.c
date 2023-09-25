/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:43:02 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/23 11:01:53 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit1(char *nb, int i)
{
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	if (nb[i] == '\0')
		return (1);
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_exit(char *nb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!nb)
		return (0);
	if (ft_strlen(nb) == 20 && nb[0] == '-')
	{
		if (!check_min(nb))
			return (1);
	}
	if (ft_strlen(nb) > 19 && nb[0] != '-')
	{
		if (!all_zero(nb))
			return (1);
	}
	if (ft_strlen(nb) == 19)
	{
		if (!check_max(nb))
			return (1);
	}
	return (check_exit1(nb, i));
	return (0);
}

void	ft_exit2(t_pip *p, t_cmd *cmds, int i)
{
	if (i == 2)
	{
		p->if_exit = 1;
		g_global.status = ft_atoi(cmds->args[1]);
		write(2, "exit\n", 6);
	}
	else
	{
		p->if_exit = 1;
		write(2, "exit\n", 6);
	}
}

void	ft_exit(t_pip *p, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds->args[i])
		i++;
	if (check_exit(cmds->args[1]))
	{
		p->if_exit = 1;
		write(2, "exit\n", 6);
		ft_error("numeric argument required", 255, cmds->args[1], "exit");
		return ;
	}
	if (i > 2)
	{
		write(2, "exit\n", 6);
		ft_error("too many arguments", 1, NULL, "exit");
		return ;
	}
	ft_exit2(p, cmds, i);
}
