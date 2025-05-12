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
