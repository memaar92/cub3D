 #include "mlx.h"

#define WIDTH 800
#define HEIGHT 600

void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    int start_x = x;
    int start_y = y;
    int end_x = x + size;
    int end_y = y + size;

    while (start_x < end_x)
    {
        int current_y = start_y;
        while (current_y < end_y)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, start_x, current_y, color);
            current_y++;
        }
        start_x++;
    }
}

int main(void)
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Small Squares Example");

    // Choose a color for the squares (in RGB format)
    int square_color = 0xFF0000; // Red in hexadecimal (RRGGBB)

    // Draw small squares
    int x = 50; // X-coordinate of the square
    int y = 50; // Y-coordinate of the square
    int square_size = 10; // Size of the square

    for (int i = 0; i < 10; i++)
    {
        draw_square(mlx, win, x, y, square_size, square_color);
        x += square_size +1;
        y += square_size +1;
    }
    
    mlx_loop(mlx); // Display the window

    return 0;
}