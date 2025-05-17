# Dopamine

Dopamine is a terminal-based, gamified habit tracker that helps you build consistent routines by reinforcing behavior with a virtual reward system. Built using `ncurses`, it operates entirely in your terminal and saves data locally to `~/.dopamine`.

## Features

* Add, complete, and delete habits
* Assign frequency and reward value to each habit
* Track streaks and automate reward scaling
* Earn a virtual currency for completed habits
* Add, redeem, and delete custom rewards
* Change currency unit via the main menu
* Reset data with confirmation dialog
* Scrollable interface with contextual controls

## Reward Scaling

Dopamine employs a reward scaling system to incentivize consistent habit completion. When you complete a habit, you earn a virtual currency. The amount of currency earned is determined by your current streak (i.e., the number of consecutive times you've completed the habit) and the base reward value assigned to that habit.

* If your streak is less than the habit's base reward value, you earn an amount equal to your streak.
* If your streak is equal to or greater than the habit's base reward value, you earn the habit's base reward value.

This system encourages you to maintain your streaks, as you'll initially earn more for each consecutive completion. However, the reward is capped at the habit's base reward value, preventing the reward from growing indefinitely.

**Example:**

For a habit with a base reward value of 5:

* Completion 1: Earn 1 currency
* Completion 2: Earn 2 currency
* Completion 3: Earn 3 currency
* Completion 4: Earn 4 currency
* Completion 5: Earn 5 currency
* Completion 6: Earn 5 currency
* Completion 7: Earn 5 currency
    * And so on...

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

The app will automatically create a `~/.dopamine/` directory for storing all habits, rewards, balance, and currency data.

## UI Overview

### Main Menu

```
 Balance: 2.00 USD

  View Habits
  View Rewards
  Change Currency
  Reset Data
  Exit

[v]ViewH [w]ViewR [r]Reset [q]Quit
```

### View Habits

```
 Balance: 2.00 USD

  Habits (3):

  1. [Learn Spanish] [Streak: 3] [Done: No]
  2. [Exercise] [Streak: 1] [Done: Yes]
  3. [Read book] [Streak: 2] [Done: No]

[a]Add [c]Complete [d]Delete [b]Back
```

### View Rewards

```
 Balance: 2.00 USD

  Rewards (2):

  1. [Coffee] [5.00 USD]
  2. [Movie] [25.00 USD]

[a]Add [u]Use [d]Delete [b]Back
```

### Chance Currency

```
 Balance: 2.00 USD 

  View Habits
  View Rewards
  Change Currency
  Reset Data
  Exit

  Enter new currency (e.g., USD, EUR): Galleons

[v]ViewH [w]ViewR [q]Quit
```

### Reset Data

```
┌────────────────────────────────────────────────────┐
│                                                    │
│      Are you sure you want to reset all data?      │
│                                                    │
│   Press [y] to confirm, any other key to cancel.   │
│                                                    │
└────────────────────────────────────────────────────┘
```

## Data Storage

All data is stored in `~/.dopamine/` and includes:

* `habits.dat`
* `rewards.dat`
* `balance.dat`
* `currency.dat`

## License

MIT License

