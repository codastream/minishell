/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:55:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/04/05 11:13:15 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) av;
	if (ac == 1)
	{
		setup_signal();
		data = init_data(env);
		if (!data)
			return (EXIT_FAILURE);
		process_line_input(data);
	}
	else
		printerr("launch ./minishell without option\n");
	return (EXIT_SUCCESS);
}
