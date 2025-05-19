// dopamine.h
#ifndef DOPAMINE_H
#define DOPAMINE_H

#include <time.h>

#define MAX_INPUT   100
#define MAX_HABITS  100
#define MAX_REWARDS 100

// Habit structure
typedef struct {
    char title[MAX_INPUT];
    char frequency[MAX_INPUT];   // "daily" or "weekly"
    float reward_amount;
    int completed;               // 0 = not done this period, 1 = done
    int streak;                  // consecutive periods
    time_t last_completed;       // timestamp
    int last_completed_day;      // Day of year of last completion
} Habit;

// Reward structure
typedef struct {
    char description[MAX_INPUT];
    float price;
} Reward;

// Globals
extern Habit   habits[MAX_HABITS];
extern int     habit_count;
extern Reward  rewards[MAX_REWARDS];
extern int     reward_count;
extern float   balance;
extern char    currency[10];

// Function prototypes
void show_main_menu();
void add_habit();
void remove_habit_index(int index);
void complete_habit(int index);

void add_reward();
void remove_reward_index(int index);
void use_reward_index(int index);
void clear_balance_manual();
void view_habits();
void view_rewards();
void load_habits();
void save_habits();
void load_rewards();
void save_rewards();
void load_balance();
void save_balance();
void update_balance(Habit *h);
void reset_all_data();
int show_confirmation_dialog(const char *message);
void change_currency();
void save_currency();
void load_currency();
void update_habit_done_statuses();
int get_today_day_of_year();

#endif // DOPAMINE_H
