#include <ncurses.h>
#include "dopamine.h"

int main() {
    initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); curs_set(0);

    load_habits();
    load_rewards();
    load_balance();
    load_currency();
    update_habit_done_statuses();
    save_habits();
    auto_clear_check();

    show_main_menu();

    endwin();
    return 0;
}
