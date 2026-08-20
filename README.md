# Sudoko
Sudoko is a very basic [Sudoku](https://en.wikipedia.org/wiki/Sudoku) like game written in [C language](https://en.wikipedia.org/wiki/C_(programming_language)) and use a [Raylib](https://www.raylib.com/) graphics library. The reason why I build is just very simple I want to make my first game and first project that all.

![Game Look](/look.png "Game Look")

## How to interact with game
 - Point the mouse to a blank cell
 - Enter a number from 1-9 in the keyboard
 - Press ENTER when you have completed the board (the grid)
    > [!NOTE]
    > You can press ENTER Key whenever you want it just show "YOU WIN" or "YOU LOSE" 
 - Last but not the least to exit the game press ESC 

## How to compile it
If you are in [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux) like me and inside it has [Arch linux](https://archlinux.org/) then it simple because it was developed like this. To install dependencies in your [Linux](https://en.wikipedia.org/wiki/Linux)
> [!NOTE] 
> It may differ some times depending on your package manager so read the [raylib wiki](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

```
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama clang raylib
```

To compile the code 

```
clang main.c -o game.out -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

For [Windows](https://en.wikipedia.org/wiki/Microsoft_Windows), [macOS](https://en.wikipedia.org/wiki/MacOS), [BSD](https://en.wikipedia.org/wiki/Berkeley_Software_Distribution) and others please read the [raylib installation guide](https://www.raylib.com/#supported-platforms)