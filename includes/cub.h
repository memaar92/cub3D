/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:13:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/21 11:26:41 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include <stdio.h>

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
	int		ceiling[3];
	int		floor[3];
}				t_vars;




#endif