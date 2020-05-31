# cnake

Terminal snake that uses a custom memory allocator.
- Written in C99
- Uses ncurses for rendering
- Uses my custom memory allocator [hisho](https://github.com/SourenP/hisho)
- Written for learning purposes

## Build and Run

```bash
make
./cnake
make clean
```

## Debug

```bash
make
ASAN_OPTIONS=detect_leaks=1 ./cnake
make clean
```

## Resources

- [fundamelon: terminal-game-tutorial](https://github.com/fundamelon/terminal-game-tutorial)
- [IC210: Keep it classy (or structy?) — a little fun with curses](https://www.usna.edu/Users/cs/wcbrown/courses/F16IC210/lab/l11/lab.html)

## Todo

- [ ] Draw
  - [X] Grid
  - [ ] Snake
    - [X] Head
    - [ ] Body
  - [ ] Food
  - [X] Game over
- [ ] Move snake
  - [X] Head
  - [ ] Body
- [ ] Collision
  - [X] Snake x Bounds
  - [ ] Snake x Snake
  - [ ] Snake x Food
- [ ] Spawn food
- [ ] Track score
- [X] Use custom memory allocator
