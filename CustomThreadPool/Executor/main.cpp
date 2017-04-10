// TestTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "../MultithreadLib/DeferredTasksExecutor.h"
#include "../MultithreadLib/ThreadPool.h"



int _tmain(int argc, _TCHAR* argv[])
  {

	DeferredTaskExecutor executor;
	int a = 0;
	TaskPtr p_task1 = std::make_shared<Task>([&]()
	{
		a = 10;
	});
	int b = 0;
	TaskPtr p_task2 = std::make_shared<Task>([&]() { b = 11; });

	int c = 0;
	TaskPtr p_task3 = std::make_shared<Task>([&]() { c = 12; });

	unsigned id1 = p_task1->GetId();
	unsigned id2 = p_task2->GetId();
	unsigned id3 = p_task3->GetId();

	executor.AddTaskToExecute(p_task1);
	executor.AddTaskToExecute(p_task2);
	executor.AddTaskToExecute(p_task3);


	//wait while tasks are finished
	std::this_thread::sleep_for(std::chrono::seconds(10));

	return 0;
  }

