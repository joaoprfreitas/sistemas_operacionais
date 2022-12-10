#ifndef MONITOR_H
#define MONITOR_H

#define PHILOSOPHERS 5

enum {THINKING = 0, EATING, HUNGRY};

void pickup(int i);
void putdown(int i);
void initialization();

#endif