/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:13:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/09/30 17:06:04 by mamesser         ###   ########.fr       */
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

# define KEY_ESCAPE 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_R 15
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_SHIFT 1

# define MAP_ERR "Error: Please provide a valid map."
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 0
# define C 1

# define ROT 0.185398



typedef struct s_ray
{
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
	int		wall_color;
}				t_ray;

typedef struct s_img
{
	int		line_size;
	int		bpp;
	int		endian;
	void	*img;
	int		*addr;
	int		tex_h;
	int		tex_w;
}				t_img;

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
	t_img	*scr_buf;
	t_img	*test_tex;
	t_img	*tex_no;
	t_img	*tex_so;
	t_img	*tex_we;
	t_img	*tex_ea;
	int		tex_h;
	int		tex_w;
	int		screen_x;
	int		screen_y;
	int		screen_width;
	int		screen_height;
	t_ray	*ray;
}				t_vars;


// UTILS
int	init_screen_buffer(t_vars *vars);
int	init_texture_dir(t_vars *vars, t_img *tex, int dir);
int	init_textures(t_vars *vars);
int	set_color(int t, int r, int g, int b);

// RAYCASTER
int		get_pixel_color(int tex_x_pos, int tex_y_pos, t_vars *vars);
void	calc_vline_start_end(t_vars *vars);
int		calc_texture_pos_x(t_vars *vars);
void	put_text_on_buf_scr(t_vars *vars);
void	calc_line_height(t_vars *vars);
void	run_dda(t_vars *vars);
int		cast_rays(t_vars *vars);
void 	print_2D_map_on_window(t_vars *vars); // for testing
void	draw_floor_ceiling(t_vars *vars);
int		ft_render(t_vars *vars);

// SETUP VIEWING DIRECTION
void	set_camera_plane(t_vars *vars);
void	set_viewing_direction(t_vars *vars);

// INIT RAYCASTING
void	init_map_steps_ray_len(t_vars *vars);
void	calc_ray_step_len(t_vars *vars);
void	calc_ray_dir(t_vars *vars);
void	init_raycast(t_vars *vars);

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