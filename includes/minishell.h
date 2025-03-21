/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/21 18:04:19 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

# include <dirent.h>
# include <stdlib.h>

//$? est remplacer par STATUS_LAST_PROCESS
// TO MAKE IT WORK I ADD IN THE ENVIRONEMENT $status_process	
// so it's important to verify at the beggining that it is		/TODO
// present in the environnement. 
char	*variable_manager(char *input);
char	*assembling(char *variable, char **array_of_str);

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size);
