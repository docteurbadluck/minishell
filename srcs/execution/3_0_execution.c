/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_0_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:52:05 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 13:03:08 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void check_path(const char *path) {
    if (path == NULL) {
        fprintf(stderr, "command not found\n");
        exit(127); // Command not found
    }

    // Try to open the path
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        if (errno == EACCES) {
            fprintf(stderr, "Permission denied for path: %s\n", path);
            exit(126);
        } else if (errno == ENOENT) {
            fprintf(stderr, "No such file or directory: %s\n", path);
            exit(127);
        } else {
            perror("Error opening file");
            exit(126);
        }
    }



    // Close the file descriptor since we just wanted to check the path
    close(fd);

    // Check if the file is executable
    if (access(path, X_OK) != 0) {
        if (errno == EACCES) {
            fprintf(stderr, "Permission denied: %s\n", path);
            exit(126);
        } else {
            fprintf(stderr, "Path is not executable: %s\n", path);
            exit(126);
        }
    }

    // Check if the path is a directory
    if (access(path, F_OK) == 0 && access(path, X_OK) == 0) {
        DIR *dir = opendir(path);
        if (dir != NULL) {
            closedir(dir);
            fprintf(stderr, "Path is a directory: %s\n", path);
            exit(126);
        }
    }

}

static void execute_child_process(t_parsed_command *command,
    t_ast_helper *ast_helper, t_env_exp *env_exp, t_free *free_all)
{
    char    *path;
    int     return_value;

    if (command->what_first == 2 || command->what_first == 0)
    {
        execute_command_input(command, ast_helper);
        execute_command_output(command, ast_helper);
    }
    else
    {
        execute_command_output(command, ast_helper);
        execute_command_input(command, ast_helper);
    }   

    
    
    
    if (!command->command || !command->arguments)
    {
        ft_printf("Invalid command: %s\n", strerror(errno));
        exit(1);
    }

    return_value = check_build_in(command->arguments, env_exp);
    if (return_value == 0)
        exit(0);
    if (return_value > 0)
        exit(execute_build_in(command->arguments, env_exp, return_value));
    
    
    path = find_path(env_exp->paths, command->arguments[0]);
    check_path(path);
    
    // else
    // {
    //  if (access(command->arguments[0], F_OK) != 0)
    //  {
    //      fprintf(stderr, "command not found\n");
    //      exit(127);
    //  }
    //  if (access(command->arguments[0], X_OK) != 0)
    //  {
    //      fprintf(stderr, "Path is not executable: %s\n", command->arguments[0]);
    //         exit(126);
    //  }
    // }
    
        
    set_default_signals();
    execve(path, command->arguments, env_exp->execute_env);
    cleanup(free_all);
    exit(1);
}

static int  handle_parent_process(t_parsed_command *command,
    t_ast_helper *ast_helper, t_env_exp *env_exp, int return_value)
{
    int parent_value;
    parent_value = execute_command_parent(command, ast_helper);
    
    if (return_value == 2 && command->pipe_out != 1)
    {
        if (ft_cd(env_exp, command->arguments, 0) == 1)
            return (1);
        return (0);
    }
    if (return_value == 4 && command->pipe_out != 1)
    {
        if (ft_export(env_exp, command->arguments, 2) == 1)
            return (1);
        return (0);
    }
    if (return_value == 5 && command->pipe_out != 1)
    {
        if (ft_unset(env_exp, command->arguments[1]) != 0)
            return (1);
        return (0);
    }
    return (parent_value);
}

void dollar(t_parsed_command **command, t_env_exp *env_exp)
{
    int i = -1;
    int j = 0; // Index for shifting
    char *result;

    // Process each argument
    while ((*command)->arguments[++i])
    {
        result = variable_manager((*command)->arguments[i], env_exp);
        free((*command)->arguments[i]);
        (*command)->arguments[i] = result;

        // If the result is an empty string, set it to NULL
        if ((*command)->arguments[i] && !ft_strncmp((*command)->arguments[i], "", 2))
        {
            free((*command)->arguments[i]);
            (*command)->arguments[i] = NULL;
        }

        // Shift non-NULL arguments forward
        if ((*command)->arguments[i]) {
            (*command)->arguments[j++] = (*command)->arguments[i];
        }
    }

    // Null-terminate the array after shifting
    (*command)->arguments[j] = NULL;
}


void remove_quotation(t_parsed_command **command)
{
    int     i;
    char    *result;

    i = -1;
    while ((*command)->arguments[++i])
    {
        if (((*command)->input_file) && ((*command)->input_file->filename))
        {
            result = remove_quotes((*command)->input_file->filename);
            free((*command)->input_file->filename);
            (*command)->input_file->filename = result;
        }
        if (((*command)->output_file) && ((*command)->output_file->filename))
        {
            result = remove_quotes((*command)->output_file->filename);
            free((*command)->output_file->filename);
            (*command)->output_file->filename = result;
        }
        result = remove_quotes((*command)->arguments[i]);
        free((*command)->arguments[i]);
        (*command)->arguments[i] = result;
    }
}

int execute_command(t_parsed_command *command, t_ast_helper *ast_helper,
                    t_env_exp *env_exp, t_free *free_all)
{
    int return_value;
    
    dollar(&command, env_exp);
    
    remove_quotation(&command);
    // printf("%s\n", command->arguments[1]);   
    return_value = check_build_in(command->arguments, env_exp);
    ast_helper->pids[ast_helper->counter] = fork();
    if (ast_helper->pids[ast_helper->counter] == -1)
    {
        perror("fork");
        cleanup_ast_helper(ast_helper);
        return (-2);
    }
    
    if (ast_helper->pids[ast_helper->counter] == 0)
        execute_child_process(command, ast_helper, env_exp, free_all);
    env_exp->dollar_question = handle_parent_process(command, ast_helper, env_exp, return_value);
    return (env_exp->dollar_question);
}