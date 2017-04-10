#pragma once

#include "DllAPI.h"

#include "Task.h" 

class ThreadPool;

class  DeferredTaskExecutor
{
public:
  MULTITHREADLIB_API DeferredTaskExecutor();
  MULTITHREADLIB_API void AddTaskToExecute(const TaskPtr& ip_task);
  MULTITHREADLIB_API bool CancelTask(unsigned i_task_id);
  MULTITHREADLIB_API EStatus GetTaskStatus(unsigned i_task_id);
  
private:
  TaskPtr _GetTaskById(unsigned i_task_id);
private:
	std::unique_ptr<ThreadPool> mp_thread_pool;
	std::map<unsigned/*task_id*/, TaskPtr> m_all_tasks;

};
