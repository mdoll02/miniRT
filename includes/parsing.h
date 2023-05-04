/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:56:49 by mdoll             #+#    #+#             */
/*   Updated: 2023/05/02 13:56:54 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "definitions.h"
# include <unistd.h>
# include <stdbool.h>

typedef struct s_elements
{
	bool	light;
	bool	camera;
	bool	ambient;
}	t_elements;

int		parse_rt_file(char	*file, t_world *world);
char	*skip_spaces(char *line);
char	*get_word_end(char *line);
ssize_t	get_file_size(char *file);
int		allocate_flt_array(float **num_arr, char *line);
void	append_object(t_object **objects, t_object *new_obj);
int		add_object(t_lexed_line *lex, t_object **objects);
void	set_support_functions(const char *type, t_object *obj);
void	free_lexed_line(t_lexed_line *lexed_line);
float	ft_atof(char *str);
int		check_file_ending(char const *file);
bool	check_elements(t_elements *elements, char *obj_name);
char	*set_type(char	*line, t_lexed_line *lexed_line, t_elements *elements);
int		set_value(char *line, t_lexed_line *lexed_line, int end, int i);

#endif //PARSING_H
