#include <ncurses.h>
#include <stdlib.h>
#include "dopamine.h"
#include <string.h>

static void draw_bars() {
    attron(A_REVERSE);
    mvprintw(0, 0, " Balance: %.2f %s ", balance, currency);
    mvprintw(LINES - 1, 0,
        "[a]AddH [r]AddR [u]UseR [d]DelH [e]DelR [b]ClrB [c]Curr [v]ViewH [w]ViewR [q]Quit");
    attroff(A_REVERSE);
}

void show_main_menu() {
    int highlight = 0;
    const char *opts[] = {
        "Add Habit", "Add Reward", "Use Reward", "Remove Habit", "Remove Reward",
        "Clear Balance", "Set Currency", "View Habits", "View Rewards", "Exit"
    };
    int n = sizeof(opts) / sizeof(opts[0]);
    int ch;

    while (1) {
        clear();
        draw_bars();
        for (int i = 0; i < n; i++) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(2 + i, 2, "%s", opts[i]);
            if (i == highlight) attroff(A_REVERSE);
        }
        ch = getch();
        switch (ch) {
            case KEY_UP:    highlight = (highlight + n - 1) % n; break;
            case KEY_DOWN:  highlight = (highlight + 1) % n;     break;
            case 10:        /* Enter */                       
                switch (highlight) {
                    case 0: add_habit(); break;
                    case 1: add_reward(); break;
                    case 2: use_reward(); break;
                    case 3: remove_habit(); break;
                    case 4: remove_reward(); break;
                    case 5: clear_balance_manual(); break;
                    case 6: set_currency(); break;
                    case 7: view_habits(); break;
                    case 8: view_rewards(); break;
                    case 9: return;
                }
                break;
            case 'a': add_habit();      break;
            case 'r': add_reward();     break;
            case 'u': use_reward();     break;
            case 'd': remove_habit();   break;
            case 'e': remove_reward();  break;
            case 'b': clear_balance_manual(); break;
            case 'c': set_currency();   break;
            case 'v': view_habits();    break;
            case 'w': view_rewards();   break;
            case 'q': return;
        }
    }
}

void add_habit() {
    echo(); curs_set(1);
    if (habit_count >= MAX_HABITS) {
        clear(); mvprintw(2,2,"Habit list full."); mvprintw(4,2,"Press any key..."); getch(); noecho(); curs_set(0); return;
    }
    Habit h; char buf[MAX_INPUT];
    clear(); draw_bars(); mvprintw(2,2,"Add Habit");
    mvprintw(4,2,"Title: "); getnstr(h.title, MAX_INPUT-1);
    mvprintw(6,2,"Description: "); getnstr(h.description, MAX_INPUT-1);
    mvprintw(8,2,"Frequency(daily/weekly): "); getnstr(h.frequency, MAX_INPUT-1);
    mvprintw(10,2,"Base Reward(%s): ", currency); getnstr(buf, MAX_INPUT-1); h.reward_amount = atof(buf);
    h.completed = 0; h.streak = 0; h.last_completed = 0;
    habits[habit_count++] = h; save_habits();
    noecho(); curs_set(0);
    mvprintw(12,2,"Habit added."); mvprintw(14,2,"Press any key..."); getch();
}

void remove_habit() {
    int choice;
    echo(); curs_set(1);
    while (1) {
        clear(); draw_bars(); mvprintw(2,2,"Delete Habit (0 cancel)");
        for (int i=0;i<habit_count;i++) mvprintw(4+i,4,"%d. %s", i+1, habits[i].title);
        mvprintw(4+habit_count+1,2,"Choice: "); scanw("%d", &choice);
        if (!choice) break;
        if (choice>0 && choice<=habit_count) {
            for (int j=choice-1;j<habit_count-1;j++) habits[j]=habits[j+1];
            habit_count--; save_habits(); break;
        }
    }
    noecho(); curs_set(0);
}

void add_reward() {
    echo(); curs_set(1);
    if (reward_count >= MAX_REWARDS) {
        clear(); draw_bars(); mvprintw(2,2,"Reward list full."); mvprintw(4,2,"Press any key..."); getch(); noecho(); curs_set(0); return;
    }
    Reward r; char buf[MAX_INPUT];
    clear(); draw_bars(); mvprintw(2,2,"Add Reward");
    mvprintw(4,2,"Description: "); getnstr(r.description, MAX_INPUT-1);
    mvprintw(6,2,"Price(%s): ", currency); getnstr(buf, MAX_INPUT-1); r.price = atof(buf);
    rewards[reward_count++] = r; save_rewards();
    noecho(); curs_set(0);
    mvprintw(8,2,"Reward added."); mvprintw(10,2,"Press any key..."); getch();
}

void remove_reward() {
    int choice;
    echo(); curs_set(1);
    while (1) {
        clear(); draw_bars(); mvprintw(2,2,"Delete Reward (0 cancel)");
        for (int i=0;i<reward_count;i++) mvprintw(4+i,4,"%d. %s", i+1, rewards[i].description);
        mvprintw(4+reward_count+1,2,"Choice: "); scanw("%d", &choice);
        if (!choice) break;
        if (choice>0 && choice<=reward_count) {
            for (int j=choice-1;j<reward_count-1;j++) rewards[j]=rewards[j+1];
            reward_count--; save_rewards(); break;
        }
    }
    noecho(); curs_set(0);
}

void use_reward() {
    int choice;
    echo(); curs_set(1);
    while (1) {
        clear(); draw_bars(); mvprintw(2,2,"Redeem Reward (0 cancel)");
        for (int i=0;i<reward_count;i++) mvprintw(4+i,4,"%d. %s - %.2f %s", i+1, rewards[i].description, rewards[i].price, currency);
        mvprintw(4+reward_count+1,2,"Choice: "); scanw("%d", &choice);
        if (!choice) break;
        if (choice>0 && choice<=reward_count) {
            if (balance>=rewards[choice-1].price) {
                balance-=rewards[choice-1].price;
                save_balance();
                mvprintw(LINES-3,2,"Redeemed! New Balance: %.2f %s", balance, currency);
            } else {
                mvprintw(LINES-3,2,"Insufficient balance.");
            }
            mvprintw(LINES-2,2,"Press any key..."); getch();
            break;
        }
    }
    noecho(); curs_set(0);
}

void clear_balance_manual() {
    balance=0; save_balance();
    clear(); draw_bars(); mvprintw(2,2,"Balance cleared."); mvprintw(4,2,"Press any key..."); getch();
}

void set_currency() {
    echo(); curs_set(1);
    char buf[MAX_INPUT]; clear(); draw_bars(); mvprintw(2,2,"Enter new currency:"); getnstr(buf,MAX_INPUT-1);
    strncpy(currency,buf,sizeof(currency)-1); currency[sizeof(currency)-1]='\0';
    save_balance(); // in case format changes
    noecho(); curs_set(0);
    mvprintw(4,2,"Currency updated to %s",currency); mvprintw(6,2,"Press any key..."); getch();
}

void view_habits() {
    clear(); draw_bars(); mvprintw(2,2,"Habits (%d):",habit_count);
    if (!habit_count) mvprintw(4,4,"No habits.");
    else for (int i=0;i<habit_count;i++) {
        int y=4+i*4;
        mvprintw(y,2,"%d. %s", i+1, habits[i].title);
        mvprintw(y+1,4,"Streak: %d  Done: %s", habits[i].streak, habits[i].completed?"Yes":"No");
    }
    mvprintw(LINES-2,2,"Press any key..."); getch();
}

void view_rewards() {
    clear(); draw_bars(); mvprintw(2,2,"Rewards (%d):",reward_count);
    if (!reward_count) mvprintw(4,4,"No rewards.");
    else for (int i=0;i<reward_count;i++) {
        int y=4+i*3;
        mvprintw(y,2,"%d. %s", i+1, rewards[i].description);
        mvprintw(y+1,4,"Price: %.2f %s", rewards[i].price, currency);
    }
    mvprintw(LINES-2,2,"Press any key..."); getch();
}
