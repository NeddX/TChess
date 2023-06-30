# TermChess
Chess in the temrinal.
Assignment project.

# Gameplay and Rules
The game follows basic chess rules.
To move a pawn, press ```:``` to enter **Command Mode**, followed by ```m```.
for the Move command, after which type in the pawn's coordinates that you want to move.
followed by a space, and then the new coordinates for the pawn.
E.g., ```f2 f4``` moves the White Pawn from F2 to F4.
After making a move, the turn changes.
Note that you can only select and move pawns that belong to your color.

You can also do ```:h``` for list of available commands although they're not many.

# Build Instructions
Requires CMake 3.20 or higher.
Requires Clang 12.0 or higher.
Requires NCurses 3.6 or higher (though older versions might work, haven't tested).

Since the project requires NCurses, this project won't compile and work on non POSIX compatible systems.
If for some reason your Linux distribution doesn't already come with NCurses installed, then you can install it from your package manager.
- Arch based: ``` sudo pacman -S ncurses ```
- Debian based: ```sudo apt install ncurses```
- Fedora: ```sudo dnf install ncurses```
- Apple with Homebrew: ```brew install ncurses```
- You get the gist. Google also helps.
