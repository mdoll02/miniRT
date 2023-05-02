/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:46:59 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 11:36:12 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "definitions.h"

void	register_hooks(t_minirt *minirt);

int		loop_hook(t_minirt *minirt);
int		key_hook(int keycode, t_minirt *minirt);
int		close_hook(t_minirt *minirt);

#endif //HOOKS_H
