#include "stdafx.h"

#include "Woker.h"

Worker::Worker()
	: m_enabled(true)
	, m_task_comparator(
		[](const TaskPtr& ip_task1, const TaskPtr& ip_task2) {return (*ip_task1) < (*ip_task2);})
	, m_tasks(m_task_comparator)
	, m_cv()
	, m_mutex()
	, m_thread(&Worker::_ThreadFunExecute, this)
{

}

Worker::~Worker()
{
	m_enabled = false;
	m_cv.notify_one();
	m_thread.join();
}

void Worker::AddTask(const TaskPtr& ip_task)
{
	std::unique_lock<std::mutex> locker(m_mutex);
	m_tasks.push(ip_task);
	m_all_tasks[ip_task->GetId()] = ip_task;
	ip_task->m_status = EStatus::InQueue;
	m_cv.notify_one();
}

bool Worker::IsFree()
{
	std::unique_lock<std::mutex> locker(m_mutex);
	return m_tasks.empty();

}

size_t Worker::GetCountOfTask()
{
	std::unique_lock<std::mutex> locker(m_mutex);
	return m_tasks.size();

}

bool Worker::CancelTask(unsigned i_task_id)
{
	std::unique_lock<std::mutex> locker(m_mutex);
	const auto iter = m_all_tasks.find(i_task_id);
	if (iter == m_all_tasks.end())
		throw std::invalid_argument("There are no task with id: " + std::to_string(i_task_id));
	if (iter->second->m_status == EStatus::Processing || iter->second->m_status == EStatus::Done)
		return false;
	iter->second->m_status = EStatus::Canceled;
	return true;
}

bool Worker::ContainTask(unsigned i_task_id)
{
	std::unique_lock<std::mutex> locker(m_mutex);
	const auto iter = m_all_tasks.find(i_task_id);
	return iter != m_all_tasks.end();
}

void Worker::_ThreadFunExecute()
{
	while (m_enabled)
	{
		std::unique_lock<std::mutex> locker(m_mutex);
		m_cv.wait(locker, [&]()
							{
								return !m_tasks.empty() || !m_enabled;
							});

		while (!m_tasks.empty())
		{
			auto p_task = m_tasks.top();
			m_tasks.pop();

			if (p_task->m_status == EStatus::Canceled)
				continue;
			p_task->m_status = EStatus::Processing;

			locker.unlock();
			
			//start execution of task
			p_task->Execute();			

			locker.lock();
			
		}
	}
}