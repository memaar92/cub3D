/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:13:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/28 10:50:11 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "colors.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

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
	char	**textures;
	int		floor_ceiling[2][3];
	void	*red_line;
	void	*img_wall;
	void	*test_texture;
	void	*img;
	int		*img_addr;
	int		*text_addr;
	int		size_line;
	int		size_test;
	int		screen_width;
	int		screen_height;
	t_ray	*ray;
}				t_vars;

// RAYCASTER
int		ft_render(t_vars *vars);
void	init_textures(t_vars *vars); // for testing
void 	print_2D_map_on_window(t_vars *vars); // for testing
int		cast_rays(t_vars *vars);
void	run_dda(t_vars *vars);
void	calc_line_height(t_vars *vars);
void	draw_wall(t_vars *vars);
int		get_pixel_color(int x, int y, t_vars *vars);

// SETUP RAYCAST (probably not needed in the end)
void	setup_raycast(t_vars *vars);
void	set_viewing_direction(t_vars *vars);
void	set_camera_plane(t_vars *vars);

// INIT RAYCASTING
void	init_raycast(t_vars *vars);
void	calc_ray_dir(t_vars *vars);
void	calc_ray_step_len(t_vars *vars);
void	init_map_steps_ray_len(t_vars *vars);

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