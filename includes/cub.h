/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:13:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/21 17:13:31 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# define NO 0
# define SO 1
# define WE 2
# define EA 4
# define F 0
# define C 1

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		pl_pos_x;
	int		pl_pos_y;
	int		pov_dir;
	int		array_cols;
	int		array_rows;
	char	*textures[5];
	int		floor_ceiling[2][3];
}				t_vars;

// PARSER
int		parse(t_vars **vars, char *filename, int text_flag, int c_f_flag);
int		find_ceiling_floor(t_vars **vars, char **buf, int *ceil_floor_flag);
int		find_textures(t_vars **vars, char **buf, int *text_flag, int *c_f_flag);
int		find_paths(t_vars **vars, char **elements, int *text_flag);

// PARSER2
int		check_floor_ceil(t_vars **vars, char **elements, int *c_f_flag);
int		check_textures(t_vars **vars, char **elements, int *text_flag);

// UTILS
void	set_char(char **buf, char c);
int		check_rgb_values(t_vars **vars, char **buf);
void	print_parser(t_vars *vars);

// INIT
void	set_floor_ceil(t_vars **vars);
t_vars	*init_vars(void);

#endif