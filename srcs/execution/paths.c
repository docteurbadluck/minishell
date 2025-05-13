/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:54:38 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 12:54:39 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **get_paths(t_env_exp *env_exp)
{
    char    *env_path;
//  char    **paths;

    ft_getenv(env_exp->env, "PATH", &env_path);
    if (env_path == NULL)
        return (NULL);
    return (ft_split(env_path, ':'));
}

char    *find_path(char **paths, char *command)
{
    int     i;
    char    *tmp_path;
    char    *full_path;

    if (ft_strncmp(command, "./", 2) == 0 || command[0] == '/')
    {
        if (access(command, F_OK) == 0)
        {
            full_path = command;
            return (full_path);
        }
    }
    i = 0;
    while (paths[i])
    {
        tmp_path = ft_strjoin(paths[i], "/");
        if (!tmp_path)
            return (NULL);
        full_path = ft_strjoin(tmp_path, command);
        free(tmp_path);
        if (!full_path)
            return (NULL);
        if (access(full_path, F_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

char    **get_environ(t_env *env)
{
    int     counter;
    t_env   *current;
    char    **environ;

    counter = 0;
    current = env;
    while (current)
    {
        counter++;
        current = current->next;
    }
    environ = (char **)malloc(sizeof(char *) * (counter + 1));
    if (!environ)
    {
        ft_printf("Error: malloc failed\n");
        exit(1);
    }
    return (environ);
}

char    **create_env_from_linked_list(t_env *env)
{
    t_env   *current;
    char    **environ;
    int     i;
    char    *step;

    environ = get_environ(env);
    current = env;
    i = 0;
    while (current)
    {
        step = ft_strjoin(current->type, "=");
        environ[i] = ft_strjoin(step, current->data);
        free(step);
        i++;
        current = current->next;
    }
    environ[i] = NULL;
    return (environ);
}