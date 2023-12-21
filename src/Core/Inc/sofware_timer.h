/*
 * sofware_timer.h
 *
 *  Created on: Dec 21, 2023
 *      Author: ADMIN
 */

#ifndef INC_SOFWARE_TIMER_H_
#define INC_SOFWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;


void initTimerCycle(int cycle);
void setTimer1(int duration);
void setTimer2(int duration);
void timerRun();

#endif /* INC_SOFWARE_TIMER_H_ */
