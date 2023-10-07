# cub3D

Inspired by Wolfenstein 3D, cub3D is a 42 school project that provides an opportunity to explore the fundamentals of raycasting, textures rendering, and basic game mechanics. 
The goal is to create a small, simple, and visually appealing maze game. The project is written in C and utilizes 42's [MinilibX graphics library](https://github.com/42Paris/minilibx-linux).

### Elements
- Raycasting: Utilizes raycasting techniques to create a 3D perspective effect from a 2D map
- Textured Walls and Floors: Implements textured walls and floors to enhance the visual appeal of the game
- Basic Game Mechanics: Movement, collision detection, and simple game interactions (sliding alongside walls, use different items)
- Sprite Rendering: Includes basic sprite object animations to make the first person perspective and movements more realistic
- Map Parsing: Reads map data from a .cub file to generate the game environment
- Error Management: Handles various error scenarios gracefully


### Preview



### How to compile and run the game
Clone the repository:
```
git clone https://github.com/memaar92/cub3D.git
```

Compile the project:
```
cd <path to the respective folder>
make
```

If you are on Linux and simply typing make doesn't work, that means don't have all required libraries. Try this command to install them:
```
make install on linux
```

And then run the game by typing:
```
./cub3D ./maps/testmap.cub bonus
```

### Keyboard/mouse control

| Key | Action |
| --- | --- |
| W | Move forward |
| A | Move left |
| S | Move backward|
| D | Move right |
| 9 | Swap item hold by player |
| Left Arrow | Rotate camera left |
| Right Arrow | Rotate camera right |
| Left mouse click | Enable/disable rotation by mouse |
| Move mouse | Rotate camera left/right|
| Right mouse click | Zoom in/out |
| Esc | Close the game |

