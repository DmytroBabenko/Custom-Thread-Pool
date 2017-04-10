#pragma once

#include "Task.h"
#include "DllAPI.h"

class  Worker
{
friend class Task;

public:
  MULTITHREADLIB_API Worker();
  MULTITHREADLIB_API ~Worker();

  MULTITHREADLIB_API void AddTask(const TaskPtr& ip_task);
  MULTITHREADLIB_API bool CancelTask(unsigned i_task_id);
  MULTITHREADLIB_API bool IsFree();
  MULTITHREADLIB_API bool ContainTask(unsigned i_task_id);
  MULTITHREADLIB_API size_t GetCountOfTask();


private:
	void _ThreadFunExecute();

private:
	volatile bool m_enabled;
	std::function<bool(const TaskPtr& ip_task1, const TaskPtr& ip_task2)> m_task_comparator;
	std::priority_queue<TaskPtr, std::vector<TaskPtr>, decltype(m_task_comparator)> m_tasks;
	std::condition_variable m_cv;
	std::mutex m_mutex;
	std::thread m_thread;
	std::map<unsigned, TaskPtr> m_all_tasks;

};