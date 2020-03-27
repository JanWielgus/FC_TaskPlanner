// FC_TaskPlanner.h
/*
    Name:       FC_TaskPlanner_example.ino
    Created:	10/09/2019 21:32:39
    Author:     Jan Wielgus
*/

#ifndef _FC_TASKPLANNER_h
#define _FC_TASKPLANNER_h

#include "arduino.h"


class FC_TaskPlanner
{
 private:
	typedef void (*functionPointer)();
	
 public:
	FC_TaskPlanner(uint8_t plannedTasksMaxArrSize = 5); // max amt of planned tasks at one time (default is 5)
	~FC_TaskPlanner();
	bool scheduleTask(functionPointer fPtr, uint32_t call_in); // callIn - in how many milliseconds call a scheduled task; return true if added successfully
	bool scheduleTaskMicroseconds(functionPointer fPtr, uint32_t call_in); // same as above but time is in microseconds
	void runPlanner(); // execute this function in the main loop()
	uint8_t getAmtOfAwaitingTasks();
	uint32_t getCurrentTime(); // in microseconds
	
 private:
	bool removeTaskFromArray(uint8_t taskPos); // used after function execution, remove empty space from the array (0 is the first task)
	
	
 private:
	const uint8_t MaxPlannedTasks;
	
	struct plannedTaskType
	{
		functionPointer functionPtr;
		uint32_t timeToExecute;
	};
	plannedTaskType* plannedTasksArr; // array where stored are functions until they are called
	uint8_t tasksInArray = 0; // amt of tasks in the array above

	uint32_t tNow; // last runPlanner execution time
};


#endif

