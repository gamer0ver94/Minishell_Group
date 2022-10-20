/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:35:44 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/20 14:49:37 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	termios_config(struct termios *t_config, struct termios *old_term)
{
	(void)old_term;
	tcgetattr(STDIN_FILENO, t_config);
	// t_config = old_term;
	// tcgetattr(0, t_config);
	t_config->c_lflag &= ~ECHOCTL;
	// t_config->c_lflag &= ~(ICANON);
	// t_config->c_cc[VMIN] = 1;
	// t_config->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, t_config);
	return (0);
}
