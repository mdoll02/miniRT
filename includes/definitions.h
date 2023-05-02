/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:59:30 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 11:28:04 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <X11/X.h>
# include <X11/keysym.h>

typedef void*	t_mlx_context;
typedef void*	t_mlx_window;

typedef struct s_minirt
{
	t_mlx_context	ctx;
	t_mlx_window	win;
}	t_minirt;

#endif //DEFINITIONS_H
