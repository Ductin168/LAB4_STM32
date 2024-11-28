#include "scheduler.h"

#define SCH_MAX_TASKS 40
#define TICK 10
int Last_Task = 0;

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
} sTask;

sTask SCH_Tasks_G[SCH_MAX_TASKS];

void SCH_INIT(void) {
    int i;
    for (i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    int Indextoadd = Last_Task;
    DELAY = DELAY / TICK;
    if (Last_Task < SCH_MAX_TASKS) {
        for (int i = 0; i < Last_Task; i++) {
            if (SCH_Tasks_G[i].Delay <= DELAY) {
                DELAY -= SCH_Tasks_G[i].Delay;
            } else {
                Indextoadd = i;
                break;
            }
        }
        for (int i = Last_Task; i > Indextoadd; i--) {
            SCH_Tasks_G[i] = SCH_Tasks_G[i - 1];
        }
        Last_Task++;
        SCH_Tasks_G[Indextoadd].pTask = pFunction;
        SCH_Tasks_G[Indextoadd].Delay = DELAY;
        SCH_Tasks_G[Indextoadd].Period = PERIOD;
        if (Indextoadd < Last_Task - 1) {
            SCH_Tasks_G[Indextoadd + 1].Delay -= SCH_Tasks_G[Indextoadd].Delay;
        }
    }
}

void SCH_Update(void) {
    if (SCH_Tasks_G[0].Delay > 0) {
        SCH_Tasks_G[0].Delay--;
    }
    if (SCH_Tasks_G[0].Delay <= 0) {
        SCH_Tasks_G[0].RunMe++;
    }
}

void SCH_Dispatch_Task(void) {
    if (SCH_Tasks_G[0].RunMe > 0) {
        SCH_Tasks_G[0].RunMe--;
        (*SCH_Tasks_G[0].pTask)();
        sTask temp = SCH_Tasks_G[0];
        SCH_Delete_Task(0);
        if (temp.Period > 0) {
            SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
        } else {
            SCH_Add_Task(temp.pTask, 0, 0);
        }
    }
}

void SCH_Add_Oneshot_Task(void (*pFunction)(), uint32_t DELAY) {
    SCH_Add_Task(pFunction, DELAY, 0);
}

void SCH_Delete_Task(uint32_t index) {
    if (index >= Last_Task) {
        return;
    }
    if (index < Last_Task - 1) {
        SCH_Tasks_G[index + 1].Delay += SCH_Tasks_G[index].Delay;
    }
    for (int i = index; i < Last_Task - 1; i++) {
        SCH_Tasks_G[i] = SCH_Tasks_G[i + 1];
    }
    SCH_Tasks_G[Last_Task - 1].Delay = 0;
    SCH_Tasks_G[Last_Task - 1].Period = 0;
    SCH_Tasks_G[Last_Task - 1].RunMe = 0;
    Last_Task--;
}
