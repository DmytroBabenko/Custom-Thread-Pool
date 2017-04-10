#include "stdafx.h"

#include "../MultithreadLib/DeferredTasksExecutor.h"
#include "../MultithreadLib/ThreadPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MultithreadLibTest
{
	TEST_CLASS(DeferredTaskExecutorTest)
	{
	public:

		TEST_METHOD(ExecuteTasksOneThreadChangeVariableTask)
		{
			int variable = 10;
			{
				DeferredTaskExecutor executor;
				TaskPtr p_task = std::make_shared<Task>([&]()
				{
					variable = 20;
				});
				executor.AddTaskToExecute(p_task);
			}

			Assert::AreEqual(20, variable);
		}

		TEST_METHOD(CancelTaskTrue)
		{
			DeferredTaskExecutor executor;
			TaskPtr p_task1 = std::make_shared<Task>([&]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(5));
			});
			TaskPtr p_task2 = std::make_shared<Task>([&]() {});
			TaskPtr p_task3 = std::make_shared<Task>([&]() {});

			unsigned id1 = p_task1->GetId();
			unsigned id2 = p_task2->GetId();
			unsigned id3 = p_task3->GetId();

			executor.AddTaskToExecute(p_task1);
			executor.AddTaskToExecute(p_task2);
			executor.AddTaskToExecute(p_task3);

			Assert::IsTrue(executor.CancelTask(id2));

			//wait while tasks are finished
			std::this_thread::sleep_for(std::chrono::seconds(10));

			Assert::IsTrue(executor.GetTaskStatus(id1) == EStatus::Done);
			Assert::IsTrue(executor.GetTaskStatus(id2) == EStatus::Canceled);
			Assert::IsTrue(executor.GetTaskStatus(id3) == EStatus::Done);

		}

		TEST_METHOD(CancelTaskFalse)
		{
			DeferredTaskExecutor executor;
			TaskPtr p_task1 = std::make_shared<Task>([&]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(5));
			});
	
			unsigned id1 = p_task1->GetId();	

			executor.AddTaskToExecute(p_task1);
			
			std::this_thread::sleep_for(std::chrono::seconds(2)); 

			Assert::IsFalse(executor.CancelTask(id1));

			//wait while tasks are finished
			std::this_thread::sleep_for(std::chrono::seconds(10));		
		}

	};
}