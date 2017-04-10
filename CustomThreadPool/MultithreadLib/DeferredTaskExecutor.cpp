#include "stdafx.h"
#include "DeferredTasksExecutor.h"
#include "ThreadPool.h"

DeferredTaskExecutor::DeferredTaskExecutor()
	: mp_thread_pool(new ThreadPool(std::thread::hardware_concurrency()))
{

}
void DeferredTaskExecutor::AddTaskToExecute(const TaskPtr& ip_task)
{
	m_all_tasks[ip_task->GetId()] = ip_task;
	mp_thread_pool->AddTaskToExecute(ip_task);
}

EStatus DeferredTaskExecutor::GetTaskStatus(unsigned i_task_id)
{
	return _GetTaskById(i_task_id)->m_status;
}

bool DeferredTaskExecutor::CancelTask(unsigned i_task_id)
{
	return mp_thread_pool->CancelTask(i_task_id);
}

TaskPtr DeferredTaskExecutor::_GetTaskById(unsigned i_task_id)
{
	const auto iter = m_all_tasks.find(i_task_id);
	if (iter == m_all_tasks.end())
		throw std::invalid_argument("There are no task with id: " + std::to_string(i_task_id));
	return iter->second;
}