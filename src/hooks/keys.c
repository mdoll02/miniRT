/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:31:56 by kschmidt          #+#    #+#             */
/*   Updated: 2023/05/02 11:35:07 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "definitions.h"

int	key_hook(int keycode, t_minirt *minirt)
{
	if (keycode == XK_Escape)
		close_hook(minirt);
	return (0);
}
