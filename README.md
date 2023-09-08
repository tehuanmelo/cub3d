# cub3D - 42 School Project

cub3D is a project at 42 School designed to introduce you to the world of raycasting, a fundamental technique used in 3D game development. In this project, you'll create a simple 3D game engine capable of rendering a maze-like world, and you'll be able to move around in this world using basic controls. This README file will provide you with all the information you need to get started with cub3D.

![Untitled-4](https://github.com/tehuanmelo/cub3d/assets/59938530/b647310d-752a-42ec-9cae-8fd674030e39)


## Table of Contents

1. [Getting Started](#getting-started)
2. [Prerequisites](#prerequisites)
3. [Installing](#installing)
4. [Usage](#usage)
5. [Controls](#controls)
6. [Configuring the Map](#configuring-the-map)
8. [Contributing](#contributing)
8. [Acknowledgments](#acknowledgments)

## Getting Started

These instructions will help you set up and run the cub3D project on your local machine.

### Prerequisites

Before you begin, make sure you have the following installed:

- **macOS**: cub3D is designed to work on macOS. Ensure you have a macOS-based machine.

### Installing

1. Clone the cub3D repository to your local machine:

   ```bash
   git clone https://github.com/tehuanmelo/cub3D.git



2. Change into the project directory:
    ```bash
    cd cub3D
3. Compile the project:
    ```Makefile
    make

## Usage

- To run the cub3D project, use the following command:

    ```bash
    ./cub3D path/to/map.cub

Replace path/to/map.cub with the path to your map configuration file. The game window will open, and you can start exploring the world.

### Controls

    W/UP Arrow: Move forward
    A: Strafe left
    S/Down Arrow: Move backward
    D: Strafe right
    Left Arrow/Mouse: Rotate left
    Right Arrow/Mouse: Rotate right
    Esc: Quit the game

### Configuring the Map

To create and configure the map for your game, follow these guidelines:

1. Create a text file with the .cub extension (e.g., my_map.cub).

2. Inside the file, define the map layout and game settings. This is a simple valid map.

    ```bash
    NO ./textures/north_texture.xpm  # North wall texture
    SO ./textures/south_texture.xpm  # South wall texture
    WE ./textures/west_texture.xpm   # West wall texture
    EA ./textures/east_texture.xpm   # East wall texture
    F 255,255,255  # Floor color (RGB)
    C 0,0,0        # Ceiling color (RGB)
    1111111111111
    1001000000011
    100100S010001
    1000000010001
    1111111111111

3. Save your map configuration file.

Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as :

∗ North texture:

         NO ./path_to_the_north_texture

· identifier: NO
· path to the north texure 

∗ South texture:

         SO ./path_to_the_south_texture

· identifier: SO
· path to the south texure ∗ West texture:

         WE ./path_to_the_west_texture

· identifier: WE
· path to the west texure 

∗ East texture:

         EA ./path_to_the_east_texture

· identifier: EA
· path to the east texure 

∗ Floor color:

            F 220,100,0

· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255

 ∗ Ceiling color:

            C 225,30,0

· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255



## Contributing

Contributions to cub3D are welcome! If you have ideas for improvements, bug fixes, or new features, please submit a pull request. Be sure to follow the project's coding standards and guidelines.



## Acknowledgments

The cub3D project was inspired by the classic game Wolfenstein 3D.
Special thanks to 42 School for providing the opportunity to work on this project.
