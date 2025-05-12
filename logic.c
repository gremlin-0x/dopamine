#include <string.h>
#include <time.h>
#include "dopamine.h"

void update_balance(Habit *h) {
    if (!h->completed) {
        h->streak++;
        int cap = (int)h->reward_amount;
        float daily = (h->streak < cap ? h->streak : h->reward_amount);
        balance += daily;
        h->completed = 1;
        h->last_completed = time(NULL);
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
        remove_reward_index(index);  // Remove reward after using it
        save_balance();
    }
}

