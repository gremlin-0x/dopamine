#include <ncurses.h>
#include <stdlib.h>
#include "dopamine.h"
#include <string.h>

static void draw_bars_main() {
    attron(A_REVERSE);
    mvprintw(0, 0, " Balance: %.2f %s ", balance, currency);
    mvprintw(LINES - 1, 0, "[v]ViewH [w]ViewR [q]Quit");
    attroff(A_REVERSE);
}

static void draw_bars_habits() {
    attron(A_REVERSE);
    mvprintw(0, 0, " Balance: %.2f %s ", balance, currency);
    mvprintw(LINES - 1, 0, "[a]Add [c]Complete [d]Delete [b]Back");
    attroff(A_REVERSE);
}

static void draw_bars_rewards() {
    attron(A_REVERSE);
    mvprintw(0, 0, " Balance: %.2f %s ", balance, currency);
    mvprintw(LINES - 1, 0, "[a]Add [u]Use [d]Delete [b]Back");
    attroff(A_REVERSE);
}

void show_main_menu() {
    int highlight = 0;
    const char *opts[] = {
        "View Habits", "View Rewards", "Reset Data", "Exit"
    };
    int n = sizeof(opts) / sizeof(opts[0]);
    int ch;

    while (1) {
        clear();
        draw_bars_main();
        for (int i = 0; i < n; i++) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(2 + i, 2, "%s", opts[i]);
            if (i == highlight) attroff(A_REVERSE);
        }
        ch = getch();
        switch (ch) {
            case KEY_UP:    highlight = (highlight + n - 1) % n; break;
            case KEY_DOWN:  highlight = (highlight + 1) % n;     break;
            case 10:
                switch (highlight) {
                    case 0: view_habits(); break;
                    case 1: view_rewards(); break;
                    case 2: reset_all_data(); break;
                    case 3: return;
                }
                break;
            case 'v': view_habits(); break;
            case 'w': view_rewards(); break;
            case 'r': reset_all_data(); break;
            case 'q': return;
        }
    }
}

#define LIST_START 4
#define LIST_HEIGHT (LINES - 6)

void add_habit() {
    echo(); curs_set(1);
    if (habit_count >= MAX_HABITS) {
        clear(); draw_bars_habits(); mvprintw(2,2,"Habit list full."); mvprintw(4,2,"Press any key..."); getch(); noecho(); curs_set(0); return;
    }
    Habit h; char buf[MAX_INPUT];
    clear(); draw_bars_habits(); mvprintw(2,2,"Add Habit");
    mvprintw(4,2,"Title: "); getnstr(h.title, MAX_INPUT-1);
    mvprintw(6,2,"Description: "); getnstr(h.description, MAX_INPUT-1);
    mvprintw(8,2,"Frequency(daily/weekly): "); getnstr(h.frequency, MAX_INPUT-1);
    mvprintw(10,2,"Base Reward(%s): ", currency); getnstr(buf, MAX_INPUT-1); h.reward_amount = atof(buf);
    h.completed = 0; h.streak = 0; h.last_completed = 0;
    habits[habit_count++] = h; save_habits();
    noecho(); curs_set(0);
    mvprintw(12,2,"Habit added."); mvprintw(14,2,"Press any key..."); getch();
}

void add_reward() {
    echo(); curs_set(1);
    if (reward_count >= MAX_REWARDS) {
        clear(); draw_bars_rewards(); mvprintw(2,2,"Reward list full."); mvprintw(4,2,"Press any key..."); getch(); noecho(); curs_set(0); return;
    }
    Reward r; char buf[MAX_INPUT];
    clear(); draw_bars_rewards(); mvprintw(2,2,"Add Reward");
    mvprintw(4,2,"Description: "); getnstr(r.description, MAX_INPUT-1);
    mvprintw(6,2,"Price(%s): ", currency); getnstr(buf, MAX_INPUT-1); r.price = atof(buf);
    rewards[reward_count++] = r; save_rewards();
    noecho(); curs_set(0);
    mvprintw(8,2,"Reward added."); mvprintw(10,2,"Press any key..."); getch();
}

void view_habits() {
    int highlight = 0, offset = 0;
    int ch;

    // Auto-reset outdated completions
    time_t now = time(NULL);
    int modified = 0;
    for (int i = 0; i < habit_count; ++i) {
        if (!habits[i].completed) continue;

        double diff = difftime(now, habits[i].last_completed);
        if ((strcmp(habits[i].frequency, "daily") == 0 && diff > 24 * 3600) ||
            (strcmp(habits[i].frequency, "weekly") == 0 && diff > 7 * 24 * 3600)) {
            habits[i].completed = 0;
            modified = 1;
        }
    }
    if (modified) save_habits();

    while (1) {
        clear();
        draw_bars_habits();
        mvprintw(2, 2, "Habits (%d):", habit_count);
        if (habit_count == 0) {
            mvprintw(4, 4, "No habits.");
        } else {
            int end = offset + LIST_HEIGHT;
            if (end > habit_count) end = habit_count;
            for (int i = offset; i < end; i++) {
                int y = LIST_START + i - offset;
                if (i == highlight) attron(A_REVERSE);
                mvprintw(y, 2, "%d. %s [Streak: %d] [Done: %s]",
                         i+1, habits[i].title,
                         habits[i].streak,
                         habits[i].completed ? "Yes" : "No");
                if (i == highlight) attroff(A_REVERSE);
            }
        }
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (highlight > 0) highlight--;
                if (highlight < offset) offset--;
                break;
            case KEY_DOWN:
                if (highlight < habit_count - 1) highlight++;
                if (highlight >= offset + LIST_HEIGHT) offset++;
                break;
            case 'a':
                add_habit(); break;
            case 'd':
                remove_habit_index(highlight); break;
            case 'c':
                complete_habit(highlight); break;
            case 'b': return;
        }
    }
}

void view_rewards() {
    int highlight = 0, offset = 0;
    int ch;
    while (1) {
        clear();
        draw_bars_rewards();
        mvprintw(2, 2, "Rewards (%d):", reward_count);
        if (reward_count == 0) {
            mvprintw(4, 4, "No rewards.");
        } else {
            int end = offset + LIST_HEIGHT;
            if (end > reward_count) end = reward_count;
            for (int i = offset; i < end; i++) {
                int y = LIST_START + i - offset;
                if (i == highlight) attron(A_REVERSE);
                mvprintw(y, 2, "%d. %s [%.2f %s]",
                         i+1, rewards[i].description, rewards[i].price, currency);
                if (i == highlight) attroff(A_REVERSE);
            }
        }
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (highlight > 0) highlight--;
                if (highlight < offset) offset--;
                break;
            case KEY_DOWN:
                if (highlight < reward_count - 1) highlight++;
                if (highlight >= offset + LIST_HEIGHT) offset++;
                break;
            case 'a':
                add_reward(); break;
            case 'd':
                remove_reward_index(highlight); break;
            case 'u':
    if (rewards[highlight].price <= balance) {
        balance -= rewards[highlight].price;
        save_balance();
    }
    break;
            case 'b': return;
        }
    }
}

void reset_all_data() {
    for (int i = 0; i < habit_count; ++i) {
        habits[i].completed = 0;
        habits[i].streak = 0;
    }
    balance = 0;
    save_habits();
    save_balance();

    clear();
    draw_bars_main();
    mvprintw(4, 2, "All habits reset. Balance cleared.");
    mvprintw(6, 2, "Press any key to return...");
    getch();
}

