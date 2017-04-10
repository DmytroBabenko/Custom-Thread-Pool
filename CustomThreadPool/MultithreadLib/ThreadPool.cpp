#include "stdafx.h"

#include "ThreadPool.h"
#include "Woker.h"

ThreadPool::ThreadPool(size_t i_num_threads)
{
	size_t num_thread = i_num_threads;
	if (i_num_threads == 0)
		num_thread = 1;
	for (size_t i = 0; i < num_thread; ++i)
	{
		m_workers.push_back(std::make_shared<Worker>());
	}

}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::AddTaskToExecute(const TaskPtr& ip_task)
{
	_GetFreeWorker()->AddTask(ip_task);
}

bool ThreadPool::CancelTask(unsigned i_task_id)
{
	for (const auto& p_worker : m_workers)
	{
		if (p_worker->ContainTask(i_task_id))
			return p_worker->CancelTask(i_task_id);
	}
	return false;
}
std::shared_ptr<Worker> ThreadPool::_GetFreeWorker()
{
	std::shared_ptr<Worker> p_free_worker = nullptr;
	size_t min_task = UINT32_MAX;
	for (auto& p_worker : m_workers)
	{
		if (p_worker->IsFree())
			return p_worker;
		else if (min_task > p_worker->GetCountOfTask())
		{
			min_task = p_worker->GetCountOfTask();
			p_free_worker = p_worker;
		}
	}

	return p_free_worker;
}
