# Roguelike

A terminal-based roguelike game written in C++17, rendered with ncurses. Navigate a procedurally generated dungeon of interconnected rooms, each with its own shape, enemies, and doors. Enemy positions persist when you leave a room and are restored when you return.

---

## Requirements

| Dependency                  | Minimum Version    | Notes                      |
| --------------------------- | ------------------ | -------------------------- |
| C++ compiler (GCC or Clang) | C++17 support      | GCC 7+ or Clang 5+         |
| CMake                       | 3.10               | Build system               |
| ncurses                     | Any recent version | Terminal rendering library |

**Installing ncurses (Debian/Ubuntu/WSL):**

```bash
sudo apt install libncurses-dev
```

**Installing ncurses (macOS):**

```bash
brew install ncurses
```

---

## Build

### Configure and build (release)

```bash
cmake -B build -S .
cmake --build build
```

### Configure and build (debug)

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

The debug build enables the debug overlay (bottom-left of screen) showing live FPS and player coordinates.

---

## Run

```bash
./build/roguelike
```

---

## Controls

| Key        | Action                                 |
| ---------- | -------------------------------------- |
| `W` or `↑` | Move up                                |
| `S` or `↓` | Move down                              |
| `A` or `←` | Move left                              |
| `D` or `→` | Move right                             |
| `SPACE`    | Start the game (from the title prompt) |
| `Q`        | Quit the game                          |

**Moving onto a `+` door tile** that is linked to another room will teleport you to that room. Not all doors are linked — unlinked doors are cosmetic.

---

## Gameplay

- You start in Room 1 of 5. The HUD in the top-left shows `Room X/5`.
- Rooms are connected in a chain. Each room has one entrance door and one exit door (except the first and last rooms, which have only an exit or entrance respectively).
- Enemies (`G`, `O`) will chase you when you enter their field of view.
- Taking damage from an enemy reduces your HP shown in the HUD above your character (`@`).
- The game ends when your HP reaches zero.
