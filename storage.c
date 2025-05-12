#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dopamine.h"

Habit   habits[MAX_HABITS];
int     habit_count   = 0;
Reward  rewards[MAX_REWARDS];
int     reward_count  = 0;
float   balance       = 0.0f;
char    currency[10]  = "USD";

#define DATA_DIR "/.dopamine/"
#define MAX_PATH 512

// Get ~/.dopamine/filename path
static const char* get_path(const char *filename) {
    static char full[MAX_PATH];
    const char *home = getenv("HOME");
    snprintf(full, sizeof(full), "%s%s%s", home, DATA_DIR, filename);
    return full;
}

static void ensure_data_dir() {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "%s%s", getenv("HOME"), DATA_DIR);
    mkdir(path, 0700);  // does nothing if already exists
}

void load_habits() {
    ensure_data_dir();
    FILE *f = fopen(get_path("habits.dat"), "rb");
    if (!f) return;
    fread(&habit_count, sizeof(habit_count), 1, f);
    fread(habits, sizeof(Habit), habit_count, f);
    fclose(f);
}

void save_habits() {
    ensure_data_dir();
    FILE *f = fopen(get_path("habits.dat"), "wb");
    if (!f) return;
    fwrite(&habit_count, sizeof(habit_count), 1, f);
    fwrite(habits, sizeof(Habit), habit_count, f);
    fclose(f);
}

void load_rewards() {
    ensure_data_dir();
    FILE *f = fopen(get_path("rewards.dat"), "rb");
    if (!f) return;
    fread(&reward_count, sizeof(reward_count), 1, f);
    fread(rewards, sizeof(Reward), reward_count, f);
    fclose(f);
}

void save_rewards() {
    ensure_data_dir();
    FILE *f = fopen(get_path("rewards.dat"), "wb");
    if (!f) return;
    fwrite(&reward_count, sizeof(reward_count), 1, f);
    fwrite(rewards, sizeof(Reward), reward_count, f);
    fclose(f);
}

void load_balance() {
    ensure_data_dir();
    FILE *f = fopen(get_path("balance.dat"), "r");
    if (!f) return;
    fscanf(f, "%f", &balance);
    fclose(f);
}

void save_balance() {
    ensure_data_dir();
    FILE *f = fopen(get_path("balance.dat"), "w");
    if (!f) return;
    fprintf(f, "%.2f", balance);
    fclose(f);
}

