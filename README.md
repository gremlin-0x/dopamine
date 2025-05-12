# Dopamine

Dopamine is a terminal-based, gamified habit tracker that helps you build consistent routines by reinforcing behavior with a virtual reward system. Built using `ncurses`, it operates entirely in your terminal and saves data locally to `~/.dopamine`.

## Features

* Add, complete, and delete habits
* Assign frequency and reward value to each habit
* Track streaks and automate reward scaling
* Earn a virtual currency for completed habits
* Add, redeem, and delete custom rewards
* Scrollable interface with contextual controls

## Installation

1. Clone the repository:

   ```sh
   git clone https://github.com/gremlin-0x/dopamine
   cd dopamine
   ```

2. Compile the application:

   ```sh
   gcc -o dopamine main.c ui.c logic.c storage.c -lncurses
   ```

3. (Optional) Move it into your `$PATH`:

   ```sh
   sudo mv dopamine /usr/local/bin/
   ```

## Usage

Run the app from anywhere:

```sh
dopamine
```

The app will automatically create a `~/.dopamine/` directory for storing all habits, rewards, and balance data.

### Controls

* Home Screen: Navigate to Habits or Rewards
* In Habits Pane:

  * `a`: Add habit
  * `c`: Mark as complete
  * `d`: Delete habit
  * `↑ ↓`: Scroll
  * `b`: Go back
* In Rewards Pane:

  * `a`: Add reward
  * `u`: Use reward
  * `d`: Delete reward
  * `↑ ↓`: Scroll
  * `b`: Go back

## Data Storage

All data is stored in `~/.dopamine/` and includes:

* `habits.dat`
* `rewards.dat`
* `balance.dat`

## License

MIT License

## Author

[gremlin-0x](https://github.com/gremlin-0x)

