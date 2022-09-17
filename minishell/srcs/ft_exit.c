/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 23:44:25 by memam             #+#    #+#             */
/*   Updated: 2022/09/17 11:35:52 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int _get_err_code(int err_code, bool set_err_code)
{
    static int static_err_code = 0;
    if (set_err_code)
        static_err_code = err_code;
    return (static_err_code);
}

int get_err_code(void)
{
    return (_get_err_code(0, false));
}

int ft_is_sign(char c)
{
    if (c == '+' || c == '-')
        return (true);
    return (false);
}
/*
*@ here we check the codes error is valid or not
    0 -> sucessfully(true -> (0))
    1 - 255 -> unsucessfuly (false -> (1, 3 .... 255, (256 = 1)))
*/
static bool ft_is_valid_exit_arg(char *args[])
{
    int i;
    int j;

    i = 0;
    while (args && args[i])
    {
        j = 0;
        while (args[i][j])
        {
            if (ft_is_sign(args[i][i]))
                j++;
            if (!ft_isdigit(args[i][j]))
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}

int ft_exit(char *args[])
{
    int exit_code;
    int i;

    i = 0;
    if (ft_strncmp(args[i], "exit", ft_strlen(args[i])) != 0)
        return (1);
    i++;
    if (args[i])
        exit_code = ft_atoi(args[i]);
    else
        exit_code = get_err_code();
    if (!ft_is_valid_exit_arg(args + i) || ft_strlen(args[i]) > 11)
    {
        ft_putendl_fd("exit: not valid arguments", 2);
        exit_code = 255;
    }
    else if (args[i] && args[++i])
    {
        ft_putendl_fd("exit: too many arguments", 2);
        ft_putendl_fd("exit", 2);
        return (1);
    }
    ft_putendl_fd("exit /n me", 2);
    exit(exit_code);
    return (exit_code);
}