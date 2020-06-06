# cnake

Termnial snake written for learning purposes.
- Written in C (99)
- Uses ncurses for rendering
- Uses my custom memory allocator [hisho](https://github.com/SourenP/hisho)
  - The memory allocator is not optimized for this game, I simply used it as a test.


![cnake_demo](images/cnake_demo.gif)

## Instrcutions

- Eating food `o` will make your snake grow and `x` will make it shrink.
- Moving into your own tail or the boundaries will make you lose
- Final score is your snake's size
- Controls:
    - Move: `arrow keys`
    - Quit: `q`

## Build and Run

```bash
make
./cnake
make clean
```

## Debug

```bash
make
ASAN_OPTIONS=detect_leaks=1 ./cnake 2> err
cat err
make clean
```

## Resources

- [fundamelon: terminal-game-tutorial](https://github.com/fundamelon/terminal-game-tutorial)
- [IC210: Keep it classy (or structy?) — a little fun with curses](https://www.usna.edu/Users/cs/wcbrown/courses/F16IC210/lab/l11/lab.html)
