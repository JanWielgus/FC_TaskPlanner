/*
    Name:       FC_TaskPlanner_example.ino
    Created:	10/09/2019 21:32:39
    Author:     Jan Wielgus
*/
// 

#include <FC_TaskPlanner.h>


FC_TaskPlanner::FC_TaskPlanner(uint8_t plannedTasksMaxArrSize)
	: MaxPlannedTasks(plannedTasksMaxArrSize)
{
	if (plannedTasksMaxArrSize > 0)
		plannedTasksArr = new plannedTaskType[plannedTasksMaxArrSize];
}


FC_TaskPlanner::~FC_TaskPlanner()
{
	if (MaxPlannedTasks > 0)
		delete [] plannedTasksArr;
}


bool FC_TaskPlanner::scheduleTask(functionPointer fPtr, uint32_t call_in)
{
	return scheduleTaskMicroseconds(fPtr, call_in * 1000);
}


bool FC_TaskPlanner::scheduleTaskMicroseconds(functionPointer fPtr, uint32_t call_in)
{
	// Check if array is not full
	if (tasksInArray >= MaxPlannedTasks)
		return false;

	plannedTasksArr[tasksInArray].functionPtr = fPtr;
	plannedTasksArr[tasksInArray].timeToExecute = micros() + call_in;
	tasksInArray++;

	return true;
}


void FC_TaskPlanner::runPlanner()
{
	tNow = micros();

	for (uint8_t i=0; i<tasksInArray; i++)
	{
		if (tNow >= plannedTasksArr[i].timeToExecute)
		{
			// Execute the task
			(*plannedTasksArr[i].functionPtr)();
			
			// Remove the task from the array
			removeTaskFromArray(i);
		}
	}
}


bool FC_TaskPlanner::removeTaskFromArray(uint8_t taskPos)
{
	// If try to remove not existing task
	if (taskPos >= tasksInArray)
		return false;
	
	// Remove the potential free space between removed task and end of the array
	for (uint8_t i=taskPos+1; i < tasksInArray; i++)
	{
		plannedTasksArr[i-1].functionPtr = plannedTasksArr[i].functionPtr;
		plannedTasksArr[i-1].timeToExecute = plannedTasksArr[i].timeToExecute;
	}
	
	// Decrease amt of tasks in the array
	tasksInArray--;
	
	return true;
}

