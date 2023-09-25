/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:33:03 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/20 10:22:30 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_p(t_pip *p, t_cmd *cmds)
{
	g_global.status = 0;
	p->sign_in = 0;
	p->sign_out = 0;
	cmds->in = 0;
	cmds->out = 1;
	g_global.status = open_files(p, cmds, 0);
}
