# 42 CUB_3D_MAC

## QUICK LAUNCH

`` make re && ./Cub3D ./setup.cub ``

## SAVE FIRST IMAGE

You can take a picture in a bitmap file of the first frame of your game with the save argument
`` ./Cub3D ./setup.cub --save``

Check it at ``./image.bmp``

## EXIT
Quit the game clicking on the window red cross or hit ESC touch

## TEXTURES SETUP
You'll find many textures in the folder `./textures` .
You can set **F**(floor), **C**(Ceil), **NO**(North), **SO**(South), **EA**(East), **WE**(West), **S**(Sprite) textures
by adding the texture path near the corresponding character in setup.cub 

For **F** and **C**, you can replace the path texture by an `R,G,B` code

example:

```
F 150,25,60
C ./textures/skybox.xpm
```
## NOTE

### NORMINETTE

Norminette is OK only for
./inc/*.h files
./src/*.c files
./libft/*.h files
./libft/*.c files
Mlx lib is not normed :/

### BONUS

- HUD
- Life Bar
- Life System (by taking sprite)
- Textures for Ceil and Floor
- Many Sprites in map