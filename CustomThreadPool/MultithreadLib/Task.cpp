#include "stdafx.h"
#include "Task.h"
#include "Utility.h"

Task::Task(std::function<void()> i_fn, EPriority i_priority)
  : m_fn_execute(i_fn)
  , m_id(Utility::GenerateUniqueID())
  , m_status(EStatus::None)
  , m_priority(i_priority)
  {

  }

bool Task::operator<(const Task& i_task) const
  {
  return m_priority < i_task.m_priority;
  }

unsigned Task::GetId() const
  {
  return m_id;
  }

EStatus Task::GetStatus() const
  {
  return m_status;
  }

void Task::Execute()
  {
  m_fn_execute();
  m_status = EStatus::Done;
  }

void Task::SetPriority(EPriority i_priority)
  {
  m_priority = i_priority;
  }


