/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:13:00 by mamesser          #+#    #+#             */
/*   Updated: 2023/10/06 09:07:58 by valmpani         ###   ########.fr       */
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

# define KEY_ESCAPE 65307
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

# define MAP_ERR "Error: Please provide a valid map."
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 0
# define C 1

# define ROT 0.057386
# define WHT 16777215
# define GR 11382186
# define DR 12312433

typedef struct s_ray
{
	int		side;
	double	view_x;
	double	view_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	plane_x;
	double	plane_y;
	double	perpwalldist;
	int		hit;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		wall_color;
	double	wall_hit;
	int		its;
}				t_ray;

typedef struct s_floor
{	
	int		y;
	int		tex_x;
	int		tex_y;	
	double	wall_x;
	double	wall_y;
	double	dist_wall;
	double	dist_pl;
	double	current_dist;
	double	weight;
	double	cur_floor_x;
	double	cur_floor_y;
	
}				t_floor;

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
	int		counter;
	int		zoom;
	int		mouse_flag;
	void	*mlx;
	void	*win;
	int		map_pos;
	double	pl_pos_x;
	double	pl_pos_y;
	int		pov_dir;
	int		array_cols;
	int		array_rows;
	int		floor_ceiling[2][3];
	int		**map;
	char	**textures;
	t_img	*scr_buf;
	t_img	*tex_no;
	t_img	*tex_so;
	t_img	*tex_we;
	t_img	*tex_ea;
	t_img	*tex_floor;
	t_img	*tex_ceil;
	t_img	*torch;
	t_img	*cam_low;
	t_ray	*ray;
	t_floor	*floor;
	int		tex_h;
	int		tex_w;
	int		screen_x;
	int		screen_y;
	int		screen_width;
	int		screen_height;
	int		frame;
}				t_vars;

typedef struct s_circle
{
	int		center_x;
	int		center_y;
	int		radius;
	int		distance;
	int		pl_pixel_x;
	int		pl_pixel_y;
	int		side;
	int		posx;
	int		posy;
	int		square_size;
	double	offset;
}	t_circle;

// DDA_UTILS
void	dda_calc_sidedist_x(t_vars *vars);
void	dda_calc_sidedist_y(t_vars *vars);

// FLOOR_CEILING
int		get_floor_color(int tex_x_pos, int tex_y_pos, t_vars *vars);
int		get_ceiling_color(int tex_x_pos, int tex_y_pos, t_vars *vars);
void	calc_floor_pos(t_vars *vars);
void	init_floor_vars(t_vars *vars);
void	put_floor_ceil(t_vars *vars);

// FREE MEM
void	free_images(t_vars	*vars);
void	free_map(t_vars *vars, int **map);
void	free_all_mem(t_vars *vars);

// HAND ITEM
void	add_hand_item(t_vars *vars);
int		get_hand_item_color(int tex_x_pos, int tex_y_pos, t_vars *vars);

// INIT RAYCASTING
void	init_map_steps_ray_len(t_vars *vars);
void	calc_ray_step_len(t_vars *vars);
void	calc_ray_dir(t_vars *vars);
void	init_raycast(t_vars *vars);

// INIT
int		allocate_mem(t_vars *vars);
void	set_floor_ceil(t_vars **vars);
int		init_tex_and_scr_buf(t_vars *vars);
int		init_mlx(t_vars *vars);
t_vars	*init_vars(void);

// KEY_HOOKS
int		new_pos(t_vars *vars, double x, double y);
int		ft_pl_move(int keycode, t_vars *vars);
void	player_rotate(int keycode, t_vars *vars);
int		move_view(int keycode, t_vars *vars);

// MAIN
int		ft_close(t_vars *vars);

// MINI_MAP_UTILS
int		is_valid_pos(t_vars *vars, int i, int j);
int		adjust_colors(int color, double factor);
void	draw_circle(t_vars *vars, t_circle mp, int i, int j);
void	draw_zoom_circle(t_vars *vars, t_circle mp, int i, int j);

// MINI_MAP
void	draw_square(t_vars *vars, t_circle mp, int color, int border);
void	draw_direction(t_vars *vars, t_circle mp);
void	draw_block(t_vars *vars, t_circle *mp, int i, int j);
void	draw_map(t_vars *vars, t_circle mp);
void	mini_map(t_vars *vars);

// MOUSE_MOVE
int		mouse_move(int x, int y, t_vars *vars);
int		mouse_click(int button, int x, int y, t_vars *vars);

// PARSER_UTILS1
void	set_char(char **buf, char c);
int		is_not_empty_line(char *buf);
int		is_first_line(char *buf);
int		check_rgb_values(t_vars **vars, char **buf);
int		right_file_extension(char *name);

// PARSER_UTILS2
int		floodfill(t_vars **vars, int **map, double x, double y);
int		flood_the_map(t_vars **vars, int fd);
int		textures_not_filled(t_vars **vars);
int		find_paths(t_vars **vars, char **elements);
int		find_ceiling_floor(t_vars **vars, char **buf);

// PARSER
char	*parse_textures(t_vars **vars, char *filename);
int		**test_map(t_vars **vars);
int		create_map(t_vars **vars, char *filename);
int		parse_map(t_vars **vars, int fd, char *filename);
int		parse(t_vars **vars, char *filename);

// PARSER2
int		find_textures(t_vars **vars, char **buf);
int		check_floor_ceil(t_vars **vars, char **elements);
int		check_textures(t_vars **vars, char **elements);
int		not_valid_character(t_vars **vars, char *line);

// PARSER3
void	set_map(t_vars **vars, int **map, int i, char *line);
char	*reach_map(t_vars **vars, int fd, int *i);
void	set_map_cols(t_vars **vars, char *line, int *i);
int		get_map_size(t_vars **vars, char *filename, int i);

// RAYCASTER_UTILS
int		get_pixel_color(int tex_x_pos, int tex_y_pos, t_vars *vars);
void	calc_line_height(t_vars *vars);
void	calc_vline_start_end(t_vars *vars);
int		calc_texture_pos_x(t_vars *vars);

// RAYCASTER
void	put_text_on_buf_scr(t_vars *vars);
void	run_dda(t_vars *vars);
int		cast_rays(t_vars *vars);
void	draw_floor_ceiling(t_vars *vars);
int		ft_render(t_vars *vars);

// SETUP VIEWING DIRECTION
void	set_camera_plane(t_vars *vars);
void	set_viewing_direction(t_vars *vars);

// UTILS
int		init_screen_buffer(t_vars *vars);
int		init_texture_dir(t_vars *vars, t_img *tex, int dir);
int		init_wall_textures(t_vars *vars);
int		init_floor_ceil_textures(t_vars *v);
int		init_hand_item_textures(t_vars *v);
int		set_color(int t, int r, int g, int b);

#endif