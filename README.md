# cub3D

A 3D raycasting game engine inspired by **Wolfenstein 3D**, built with C and minilibx. This project renders a first-person perspective inside a maze using the raycasting technique.

## Features

- Real-time 3D rendering using raycasting (1600×900 resolution)
- 60° field of view with perspective-correct wall rendering
- Texture-mapped walls with directional textures (North, South, East, West)
- Configurable floor and ceiling colors
- Smooth first-person movement with collision detection
- Map parsing and validation from `.cub` configuration files

## Prerequisites

- **Linux** (minilibx-linux)
- **GCC** compiler
- **X11** development libraries (`libx11-dev`, `libxext-dev`)
- **Make**

## Building

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Clean and recompile
```

## Usage

```bash
./cub3D <path_to_map.cub>
```

Example:

```bash
./cub3D map/test.cub
```

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Turn left |
| `→` | Turn right |
| `ESC` | Quit |

## Map Format

Maps use the `.cub` file format:

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
EA ./path/to/east_texture.xpm
WE ./path/to/west_texture.xpm

F 160,83,83
C 92,73,80

111111
100001
10N001
100001
111111
```

- **NO/SO/EA/WE** — Path to XPM texture for each wall direction
- **F/C** — RGB color for floor and ceiling (0–255)
- **Map grid** — `1` = wall, `0` = empty space
- **Player spawn** — `N`, `S`, `E`, or `W` (sets position and facing direction)
- The map must be fully enclosed by walls

## Project Structure

```
.
├── main.c                  # Entry point and MLX setup
├── include/
│   └── Wolf3D.h            # Structs and function declarations
├── raycasting/             # Rendering engine
│   ├── intersections_alg.c # Ray-wall intersection algorithm
│   ├── render.c            # 3D wall rendering and texture mapping
│   ├── controls.c          # Player input and game loop
│   ├── algo_helpers.c      # Collision detection and math helpers
│   ├── cub_init.c          # Initialization
│   ├── textures.c          # XPM texture loading
│   ├── rgb.c               # Pixel color utilities
│   └── free_textures.c     # Memory cleanup
├── parsing/                # Map file parsing and validation
├── textures/               # XPM texture assets
└── map/                    # Example .cub map files
```

## Authors

- **aessadik**
- **aait-bou**
