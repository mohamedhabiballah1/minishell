/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:48:46 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/27 08:22:31 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (strchr(envp[i], '='))
		{
			write (1, envp[i], ft_strlen(envp[i]));
			write (1, "\n", 1);
		}
		i++;
	}
	g_global.status = 0;
}

long long	ft_atoi_exit(const char *str)
{
	long long	i;
	long long	sign;
	long long	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret * sign);
}

int	all_zero(char *nb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (nb[i])
	{
		if (nb[i] == '0')
			break ;
		i++;
	}
	if (i == 0 && nb[i] == '0')
		return (1);
	return (0);
}

int	check_max(char *nb)
{
	if (ft_strcmp(nb, "9223372036854775807") > 0)
		return (0);
	return (1);
}

int	check_min(char *nb)
{
	if (ft_strcmp(nb, "-9223372036854775808") > 0)
		return (0);
	return (1);
}
