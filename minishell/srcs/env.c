/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memam <memam@student.42mulhouse.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:22:35 by memam             #+#    #+#             */
/*   Updated: 2022/09/20 00:28:32 by memam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* @ env_var_count
*       count hom many original environemet variable there are.
*       return the unmber of environemet variable.
*/

/* @ get_env_var_index
*       searche for the given variable in the environment variables.
*       
*       return the index of the variable in the environment 
*       matching the given string.
*       the given string must be a full variable name.
*       return -1 if the string cannot be found in the environment.
*/
int get_env_var_index(char **env, char *var)
{
    int i;
    char *tmp;

    tmp = ft_strjoin(var, "=");
    if (!tmp)
        return (-1);
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
        {
            free(tmp);
            return (i);
        }
        i++;
    }
    free(tmp);
    return (-1);
}  

/* @ srt_env_var
*       add an environment variable wthit the given identifier
*       corresponding to the given value.
*       if the identifier already exists in the environment, the
*       value will be update.
*       if not, it will creates a new entry.
*       return true if the operation was sucessful or false in case of error.
*/

bool set_env_var(char ** envp, char *idVar, char *value)
{
    int index;
    char *tmp;

    index = get_env_var_index(envp, idVar);
    if (value == NULL)
        value = "";
    tmp = ft_strjoin("=", value);
    if (!tmp)
        return (1);
    if (index != -1 && envp[index])
    {
        printf("identifier %s\n", idVar);
        printf(" the new value  %s\n", tmp);

        envp[index] = ft_strjoin(idVar, tmp);
        printf("environment variable with the new value %s\n", envp[index]);
    }
    /*else
        {
            index = env_var_count(envp);
            envp = realloc_env_var(envp, index + 1)
            
        }
    */
    free(tmp);
    return (0);
}
