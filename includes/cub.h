/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:13:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/25 16:31:44 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "colors.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

# define MAP_ERR "Error: Please provide a valid map."
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 0
# define C 1

typedef struct s_ray
{
	int		x;
	int		side;
	double	playerX;
	double	playerY;
	double	viewX;
	double	viewY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	planeX;
	double	planeY;
	double	perpWallDist;
	int		hit;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_ray;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		map_pos;
	int		**map;
	double	pl_pos_x;
	double	pl_pos_y;
	int		pov_dir;
	int		array_cols;
	int		array_rows;
	void	*red_line;
	void	*img_wall;
	void	*test_texture;
	int		*text_addr;
	int		size_line;
	t_ray	*ray;
	char	**textures;
	int		floor_ceiling[2][3];
}				t_vars;

// PARSER
int		parse(t_vars **vars, char *filename);
char	*parse_textures(t_vars **vars, char *filename);
int		find_ceiling_floor(t_vars **vars, char **buf);
int		find_textures(t_vars **vars, char **buf);
int		find_paths(t_vars **vars, char **elements);

// PARSER2
int		check_floor_ceil(t_vars **vars, char **elements);
int		check_textures(t_vars **vars, char **elements);

// PARSER_UTILS1
void	set_char(char **buf, char c);
int		check_rgb_values(t_vars **vars, char **buf);
void	print_parser(t_vars *vars);
void	print_map(t_vars **vars, int **map);
int		is_not_empty_line(char *buf);
int		is_first_line(char *buf);

// PARSER_UTILS2
int		textures_not_filled(t_vars **vars);

// INIT
void	set_floor_ceil(t_vars **vars);
t_vars	*init_vars(void);

#endif