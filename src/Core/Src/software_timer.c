#include "sofware_timer.h"

/*Cycle variable*/
int sysCycle = 0;
/*Timer1 flag and counter*/
int timer1_flag = 0;
int timer1_counter = 0;

/*Timer2 flag and counter*/
int timer2_flag = 0;
int timer2_counter = 0;

void initTimerCycle(int cycle) {
	sysCycle = cycle;
}

void setTimer1(int duration) {
	timer1_flag = 0;
	timer1_counter = duration / sysCycle;
}

void setTimer2(int duration) {
	timer2_flag = 0;
	timer2_counter = duration / sysCycle;
}

void timerRun() {
	if (timer1_counter > 0) {
		timer1_counter--;
	} else {
		timer1_flag = 1;
	}

	if (timer2_counter > 0) {
		timer2_counter--;
	} else {
		timer2_flag = 1;
	}
}
