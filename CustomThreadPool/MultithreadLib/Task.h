#pragma once
#include "DllAPI.h"

enum MULTITHREADLIB_API EStatus
{
	None,
	InQueue,
	Canceled,
	Processing,
	Done
};

enum MULTITHREADLIB_API EPriority
{
	Low, 
	Medium,
	High,
	Critical
};
class Task
{
public:

  MULTITHREADLIB_API Task(std::function<void()> i_fn, EPriority i_priority = EPriority::Low);

  MULTITHREADLIB_API bool operator < (const Task& i_other) const;
  MULTITHREADLIB_API unsigned GetId() const;
  MULTITHREADLIB_API EStatus GetStatus() const;
  MULTITHREADLIB_API void Execute();
  MULTITHREADLIB_API void SetPriority(EPriority i_priority);


public:
  EStatus m_status;

private:
  std::function<void()> m_fn_execute;
  const unsigned m_id;
  EPriority m_priority;
 
};


typedef std::shared_ptr<Task> TaskPtr;
