/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:13:57 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/22 19:43:25 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i++]);
	}
	free(str);
}

void	free_strings(char *pwd1, char *pwd, char *shlvl, char *envp)
{
	free(pwd1);
	free(pwd);
	free(shlvl);
	free(envp);
}

int	file_error(t_cmd *cmds, t_pip *p, char *file)
{
	p->sign_out = 1;
	if (!cmds->envflag)
		return (ft_error("No such file or directory", 1, file, NULL));
	else
		return (ft_error("ambiguous redirect", 1, file, NULL));
}
