/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:02:06 by memam             #+#    #+#             */
/*   Updated: 2022/09/18 23:23:11 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  @ is_valid_env_var_idVar:
*       check if the identifier is valid for evrionnment variable.
*       return true if the identifier contains only alphanumeric or '_'
*       or false if not.
*/

bool    is_valid_env_var_idVar(char *var)
{
    int i;

    i = 0;
    if (ft_isalpha(var[i]) ==  0 && var[i] != '_')
        return (false);
    i++;
    while (var[i] && var[i] != '=')
    {
        if (ft_isalnum(var[i]) ==  0 && var[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

/* @ get_idVar_value
*       here looking for the separates given into identifier et the value
*       in the environment variable.
*       return an array of 2 string containing the identifier and the value
*           of the new environment variable.
*       or return NULL in case of error.
*/
static char **get_idVar_value(char *arg)
{
    char **tmp;
    int i;

    tmp = ft_split(arg, '=');
    if (!tmp)
        return (NULL);
    if (!tmp[1])
        return (tmp);
    i = 2;
    while (tmp[i])
    {
        tmp[1] = ft_strjoin(tmp[1], "=");
        tmp[1] = ft_strjoin(tmp[1], tmp[i]);
        free(tmp[i]);
        i++;
    }
    return (tmp);
}

/* @ ft_export:
*       add the given variable to the environment variable.
*       return 0 if all args added to env.
*       return 1 if one or more args not added to env. 
*/

int ft_export(t_command *command)
{
    int i;
    char **tmp;
    char **arr;
    
    i = 1;
    arr = command->argv;
    if (!arr[i]) // i dont know are its utile or not?
        printf("???????????\n");
    while (arr[i])
    {
        if (!is_valid_env_var_idVar(arr[i]))
        {
            printf("export: %s not a valid identifier\n", arr[i]);
            return (1);
        }
        else if (ft_strchr(arr[i], '=') != NULL)
        {
            tmp = get_idVar_value(arr[i]);
            set_env_var(command, tmp[0], tmp[1]);
            free(tmp);
        }
        i++;
        
    }
    
    printf("😀");
	printf("\n");
    return (0);
}
