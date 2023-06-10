#include "multitask.h"
#include "delay.h"

void mutilTask(Task *task){
	if(MiliSecond() - task->time >task->delay){
			task->function();
			task->time = MiliSecond();
	}
}