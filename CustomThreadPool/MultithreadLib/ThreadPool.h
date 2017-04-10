#pragma once

#include "Task.h"
#include "DllAPI.h"

class Worker;

class  ThreadPool
{
public:
  MULTITHREADLIB_API ThreadPool(size_t i_num_threads);
  MULTITHREADLIB_API ~ThreadPool();
  MULTITHREADLIB_API void AddTaskToExecute(const TaskPtr& ip_task);
  MULTITHREADLIB_API bool CancelTask(unsigned i_task_id);

private:
	std::shared_ptr<Worker> _GetFreeWorker();
private:
	std::vector<std::shared_ptr<Worker>> m_workers;
};