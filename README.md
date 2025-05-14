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

### Clone and Build

```sh
git clone https://github.com/gremlin-0x/dopamine
cd dopamine
make
```

### Install Globally

```sh
sudo make install
```

This will install the `dopamine` binary into `/usr/local/bin`, allowing you to run it from anywhere.

### Uninstall (Optional)

```sh
sudo make uninstall
```

## Usage

Run the app from anywhere:

```sh
dopamine
```

The app will automatically create a `~/.dopamine/` directory for storing all habits, rewards, and balance data.

## UI Overview

### Main Menu

```
 Balance: 2.00 USD 

  View Habits
  View Rewards
  Reset Data
  Exit











[v]ViewH [w]ViewR [r]Reset [q]Quit
```

### View Habits

```
 Balance: 2.00 USD 

  Habits (10):

  1. [Habit 1] [Streak: 0] [Done: No]
  2. [Habit 2] [Streak: 1] [Done: Yes]
  3. [Habit 3] [Streak: 1] [Done: Yes]
  4. [Habit 4] [Streak: 0] [Done: No]
  5. [Habit 5] [Streak: 0] [Done: No]
  6. [Habit 6] [Streak: 0] [Done: No]
  7. [Habit 7] [Streak: 0] [Done: No]
  8. [Habit 8] [Streak: 0] [Done: No]
  9. [Habit 9] [Streak: 0] [Done: No]
 10. [Habit 10] [Streak: 0] [Done: No]






[a]Add [c]Complete [d]Delete [b]Back
```

### View Rewards

```
 Balance: 2.00 USD 

  Rewards (7):

  1. [Reward 1] [5.00 USD]
  2. [Reward 2] [25.00 USD]
  3. [Reward 3] [25.00 USD]
  4. [Reward 4] [25.00 USD]
  5. [Reward 5] [25.00 USD]
  6. [Reward 6] [50.00 USD]
  7. [Reward 7] [100.00 USD]







[a]Add [u]Use [d]Delete [b]Back
```

## Data Storage

All data is stored in `~/.dopamine/` and includes:

* `habits.dat`
* `rewards.dat`
* `balance.dat`

## License

MIT License

