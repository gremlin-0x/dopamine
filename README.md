# Dopamine Tracker

A terminal-based habit tracker and reward system written in C using `ncurses`.

## Repository Structure

```
├── dopamine.h      # Shared data structures & function prototypes
├── main.c          # Application entry point (initialization & main menu)
├── storage.c       # Persistent load/save routines for habits, rewards, and balance
├── logic.c         # Business logic: streak & balance updates, auto-clear checks
├── ui.c            # `ncurses`-based UI: menus, input, and screen drawing
└── README.md       # This file
```

## Build Instructions

From the project root (where all `.c` and `.h` files live), run:

```bash
gcc -o dopamine main.c ui.c logic.c storage.c -lncurses
```

This produces the `dopamine` executable.

## Usage

```bash
./dopamine
```

Once running, use the **arrow keys** or **shortcut keys** indicated in the bottom bar to navigate:

* **a**: Add Habit
* **r**: Add Reward
* **u**: Redeem (Use) Reward
* **d**: Remove Habit
* **e**: Remove Reward
* **b**: Clear Balance
* **c**: Set Currency (e.g., USD, EUR)
* **v**: View Habits
* **w**: View Rewards
* **q**: Quit

## Data Persistence

* Habits are saved to `habits.dat` in binary format.
* Rewards are saved to `rewards.dat` in binary format.
* Balance and currency are saved to `balance.dat` as text.

All data is loaded on startup and saved after each modification.

## License

This project is provided under the MIT License. Feel free to use and modify.

