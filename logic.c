// logic.c
#include <string.h>
#include <time.h>
#include "dopamine.h"

int get_today_day_of_year() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    return tm_info->tm_yday;
}

int get_week_of_year(time_t t) {
    struct tm *tm_info = localtime(&t);
    // This is not ISO week!  Adjust if needed.
    int week_num = (tm_info->tm_yday / 7) + 1;
    return week_num;
}

int get_year(time_t t) {
    struct tm *tm_info = localtime(&t);
    return tm_info->tm_year + 1900;
}

void update_balance(Habit *h) {
    if (!h->completed) {
        h->streak++;
        int cap = (int)h->reward_amount;
        float daily = (h->streak < cap ? h->streak : h->reward_amount);
        balance += daily;
        h->completed = 1;
        h->last_completed = time(NULL);
        h->last_completed_day = get_today_day_of_year();
        save_balance();
        save_habits();
    }
}

void auto_clear_check() {
    time_t now = time(NULL);
    for (int i = 0; i < habit_count; i++) {
        Habit *h = &habits[i];
        if (!h->last_completed) continue;
        double diff = difftime(now, h->last_completed);
        if (strcmp(h->frequency, "daily") == 0 && diff > 2 * 24 * 3600) {
            balance = 0;
            save_balance();
            break;
        }
        if (strcmp(h->frequency, "weekly") == 0 && diff > 2 * 7 * 24 * 3600) {
            balance = 0;
            save_balance();
            break;
        }
    }
}

void remove_habit_index(int index) {
    if (index < 0 || index >= habit_count) return;
    for (int i = index; i < habit_count - 1; ++i) {
        habits[i] = habits[i + 1];
    }
    habit_count--;
    save_habits();
}

void complete_habit(int index) {
    if (index < 0 || index >= habit_count) return;
    update_balance(&habits[index]);
}

void remove_reward_index(int index) {
    if (index < 0 || index >= reward_count) return;
    for (int i = index; i < reward_count - 1; ++i) {
        rewards[i] = rewards[i + 1];
    }
    reward_count--;
    save_rewards();
}

void use_reward_index(int index) {
    if (index < 0 || index >= reward_count) return;
    if (balance >= rewards[index].price) {
        balance -= rewards[index].price;
        remove_reward_index(index);
        save_balance();
    }
}

void update_habit_done_statuses() {
    time_t now = time(NULL);
    int today_day = get_today_day_of_year();
    int today_year = get_year(now);

    for (int i = 0; i < habit_count; i++) {
        Habit *h = &habits[i];

        // Reset if there's no last_completed time
        if (h->last_completed == 0) {
            h->completed = 0;
            h->streak = 0; // Reset streak as well
            continue;
        }

        // Daily habit logic
        if (strcmp(h->frequency, "daily") == 0) {
            if (today_year > get_year(h->last_completed) || today_day != h->last_completed_day) {
                h->completed = 0;
                // Reset streak if missed
                if (today_day - h->last_completed_day > 1 || today_year > get_year(h->last_completed)) {
                    h->streak = 0;
                }
            }
        }

        // Weekly habit logic
        else if (strcmp(h->frequency, "weekly") == 0) {
            if (today_year > get_year(h->last_completed) || get_week_of_year(now) != get_week_of_year(h->last_completed)) {
                h->completed = 0;
                // Reset streak if missed
                if (get_week_of_year(now) - get_week_of_year(h->last_completed) > 1 || today_year > get_year(h->last_completed)) {
                    h->streak = 0;
                }
            }
        }
    }
    save_habits(); // Important to save changes!
}
