#include <stddef.h>	/* size_t, NULL */
#include <stdlib.h> /*size_t NULL malloc*/ 
#include <assert.h> /*assert*/
#include "./include/task.h"	/* API for task*/
#include "./include/priority_queue.h" /* API for priority_queue*/
#include "./include/uid.h"	/* API for UID*/
#include "./include/scheduler.h" 	/* scheduler header file*/

#define UNUSED(x) (x = x)

/******************************************************************************/

struct schedule 
{
	p_queue_t *queue;
	task_t  *curr_task;
	int erase_running;
	int status;
};

/******************************************************************************/

static int is_before(const void *intern_data,
					 const void *extern_data, 
					 void *param)
{
	UNUSED(param);
	
	return (TaskGetNextRunTime((task_t*)intern_data) <
		   (TaskGetNextRunTime((task_t*)extern_data)));
}

static int IsMatch(void *data, void *param)
{
		
	return (UIDIsSame(TaskGetUID((task_t *)data), *(uuid_t*)param));
}

/******************************************************************************/

/*Creates a new schedule and returns a pointer to the schedule*/
schedule_t *SchedCreate()
{
	schedule_t *schedule = (schedule_t*)malloc(sizeof(schedule_t));
	if (!schedule)
	{
		return NULL;
	}
	
	schedule->queue = PQCreate(is_before, NULL);
	if (!schedule->queue)
	{
		free(schedule); schedule = NULL;
		
		return NULL;
	}
	schedule->curr_task = NULL;
	schedule->erase_running = 0;
	schedule->status = 0;
	
	return (schedule);
}

/*Destroys the schedule (uses schedule clear and PQDestroy)*/
void SchedDestroy(schedule_t *schedule)
{
	assert(schedule);

	SchedClear(schedule);
	PQDestroy(schedule->queue);
	free(schedule);
}

/*Eliminates a task from the scehdule (uses PQErase and TaskDestroy)*/
int SchedRemove(schedule_t *schedule, uuid_t task_id)
{
	task_t *task = NULL;
	
	assert(schedule);
	
	task = PQErase(schedule->queue, IsMatch, &task_id);
	if (task)
	{
		TaskDestroy(task);
		
		return 0;
	}
	/*checks if theres a current task outside of the queue +
	  if the process was found*/
	if (schedule->curr_task && IsMatch(schedule->curr_task, &task_id))
	{
		schedule->erase_running = 1;

		return 0;
	}		
	
	return 1;	
}

/*Clears the schedule of tasks (Uses SchedRemove which uses PQDestroy)*/
void SchedClear(schedule_t *schedule)
{
	assert(schedule);
	
	while(!PQIsEmpty(schedule->queue))
	{
		TaskDestroy(PQPeek(schedule->queue));
		PQDequeue(schedule->queue);		
	}
	
	if ( schedule->curr_task)
	{
		schedule->erase_running = 1;
	}
}


/*Run the schedule. Awaiting tasks run first*/
/*	Return:
	 0 - success.
	 1 - an empty schedule and a failed task run.
	 2 - an already running schedule
*/
int SchedRun(schedule_t *schedule)
{
	int task_status = 0;
	int time_val = 0;
	int pq_val = 0;
	
	assert(schedule);
	
	/*checks if the scheduler is already running*/
	if (schedule->status)
	{
		return 2;
	}
	
	schedule->status = 1;
	
	while (!PQIsEmpty(schedule->queue) && schedule->status)
	{
		schedule->erase_running = 0;		
		schedule->curr_task = PQPeek(schedule->queue);
		PQDequeue(schedule->queue);
		
		/*checks whether theres a task to run right now*/
		time_val = TaskGetNextRunTime(schedule->curr_task) - time(NULL);
		if (time_val > 0)
		{
			sleep(time_val);
		}
		
		/*run the first task inqueue*/
		task_status = TaskRun(schedule->curr_task);
		if (-1 == task_status) /*Check for task fail*/
		{
			schedule->status = 0;
			TaskDestroy(schedule->curr_task); schedule->curr_task = NULL;

			return 1;
		
		}
		else if (0 == task_status)/*task ended succsessfully + more iterations*/ 
		{
			if (schedule->erase_running)
			{
				TaskDestroy(schedule->curr_task); schedule->curr_task = NULL;
			}
			else
			{
				TaskUpdateTimeToRun(schedule->curr_task);
				pq_val = PQEnqueue(schedule->queue,  schedule->curr_task);
				if (pq_val) /*PQEnqueue check codereview*/
				{
					return 1;
				}
			}
		}
		else if (1 == task_status)/*task ended successfully + no iterations left*/
		{
			TaskDestroy(schedule->curr_task); schedule->curr_task = NULL;	 
		}
	}
	
	schedule->status = 0;
	schedule->curr_task = NULL;
	
	return 0;			
}		

/* Stops a running schedule (after the current task)*/
void SchedStop(schedule_t *schedule)
{
	assert(schedule);
	
	schedule->status = 0;
}

/* Returns the number of scheduled tasks */
size_t SchedSize(schedule_t *schedule)
{
	
	assert(schedule);
	
	return (PQSize(schedule->queue) + !!schedule->curr_task);
}
	
/*	Return:
	1 - empty schedule.
	0 - non empty schdule.
*/
int SchedIsEmpty(schedule_t *schedule)
{
	assert(schedule);
		
	return (PQIsEmpty(schedule->queue) && (!schedule->curr_task));
}


/* Adds a task to the schedule in the right priority order using op_func
	@Params - Operation function,
			  Arguments for operation function,
			  Task run interval in seconds,
			  Destroy function for arguments. 
*	Returns the task's uid on success and bad_uid when fails.
*/
uuid_t SchedAddOP(schedule_t *schedule,
				  int (*op_func)(void *arg),
				  void *arg,
				  size_t interval_in_sec,
				  void (*dest_func)(void *arg))
{
	task_t *task = NULL;
	
	assert(schedule);
	assert(op_func);
	assert(dest_func);
	
	task = TaskCreate(op_func, interval_in_sec, arg, dest_func);
	if (!task)
	{
		return (bad_uid);
	}
	if (PQEnqueue(schedule->queue, task))
	{
		TaskDestroy(task);
		
		return (bad_uid);
	}

	return (TaskGetUID(task));
}



















