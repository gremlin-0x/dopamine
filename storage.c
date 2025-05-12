#include <stdlib.h>
#include <stdio.h>
#include "dopamine.h"

// Definitions of extern globals
Habit   habits[MAX_HABITS];
int     habit_count   = 0;
Reward  rewards[MAX_REWARDS];
int     reward_count  = 0;
float   balance       = 0.0f;
char    currency[10]  = "USD";

void load_habits() {
    FILE *f = fopen("habits.dat","rb");
    if (!f) return;
    fread(&habit_count, sizeof(habit_count), 1, f);
    fread(habits, sizeof(Habit), habit_count, f);
    fclose(f);
}

void save_habits() {
    FILE *f = fopen("habits.dat","wb");
    if (!f) return;
    fwrite(&habit_count, sizeof(habit_count), 1, f);
    fwrite(habits, sizeof(Habit), habit_count, f);
    fclose(f);
}

void load_rewards() {
    FILE *f = fopen("rewards.dat","rb");
    if (!f) return;
    fread(&reward_count, sizeof(reward_count), 1, f);
    fread(rewards, sizeof(Reward), reward_count, f);
    fclose(f);
}

void save_rewards() {
    FILE *f = fopen("rewards.dat","wb");
    if (!f) return;
    fwrite(&reward_count, sizeof(reward_count), 1, f);
    fwrite(rewards, sizeof(Reward), reward_count, f);
    fclose(f);
}

void load_balance() {
    FILE *f = fopen("balance.dat","r");
    if (!f) return;
    fscanf(f, "%f", &balance);
    fclose(f);
}

void save_balance() {
    FILE *f = fopen("balance.dat","w");
    if (!f) return;
    fprintf(f, "%.2f", balance);
    fclose(f);
}
