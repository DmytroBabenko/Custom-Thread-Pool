#include "stdafx.h"

#include "../MultithreadLib/Woker.h"
#include "../MultithreadLib/Utility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MultithreadLibTest
{		
	TEST_CLASS(WorkerTest)
	{
	public:

		TEST_METHOD(WorkerFree)
		{
			Worker worker;

			Assert::IsTrue(worker.IsFree());
			Assert::AreEqual(size_t(0), worker.GetCountOfTask());
		}
		
		TEST_METHOD(AddTask)
		{
			Worker worker;
			TaskPtr p_task = std::make_shared<Task>([&]() {});

			worker.AddTask(p_task);

			Assert::IsFalse(worker.IsFree());
			Assert::AreEqual(size_t(1), worker.GetCountOfTask());
		}

		TEST_METHOD(_ThreadFunExecuteChangeVariableTask)
		{
			int variable = 10;
			{
				Worker worker;
				TaskPtr p_task = std::make_shared<Task>([&]()
				{
					variable = 20;
				});
				worker.AddTask(p_task);
			}
			
			Assert::AreEqual(20, variable);
		}

		TEST_METHOD(CheckTaskStatusInQueueAndProcessing)
		{
			Worker worker;
			TaskPtr p_task1 = std::make_shared<Task>([&]() {});
			TaskPtr p_task2 = std::make_shared<Task>([&]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(10));
			});
			worker.AddTask(p_task2);
			worker.AddTask(p_task1);

			Assert::IsTrue(p_task1->m_status == EStatus::InQueue);
			Assert::IsTrue(p_task2->m_status == EStatus::Processing);

		}

		TEST_METHOD(CheckTaskStatusDone)
		{
			TaskPtr p_task = std::make_shared<Task>([&]() {});
			
			{
				Worker worker;
				worker.AddTask(p_task);
			}

			Assert::IsTrue(p_task->m_status == EStatus::Done);
		}

		TEST_METHOD(CheckTaskPriority)
		{

			TaskPtr p_task2 = std::make_shared<Task>([&]() {}, EPriority::Critical);

			TaskPtr p_task1 = std::make_shared<Task>([&]()
			{
				std::this_thread::sleep_for(std::chrono::seconds(5));
			});

			Worker worker;
			worker.AddTask(p_task1);
			worker.AddTask(p_task2);

			std::this_thread::sleep_for(std::chrono::seconds(1));


			Assert::IsTrue(p_task2->m_status == EStatus::Done);
			Assert::IsTrue(p_task1->m_status == EStatus::Processing);
		}

		TEST_METHOD(WorkerCancelTaskTrue)
		{
			TaskPtr p_task1 = std::make_shared<Task>([&]() {});

			{
				TaskPtr p_task2 = std::make_shared<Task>([&]()
				{
					std::this_thread::sleep_for(std::chrono::seconds(5));
				});
				Worker worker;
				worker.AddTask(p_task2);
				worker.AddTask(p_task1);

				Assert::IsTrue(worker.CancelTask(p_task1->GetId()));

			}

			Assert::IsTrue(p_task1->m_status == EStatus::Canceled);

		}

		TEST_METHOD(WorkerCancelTaskFalse)
		{
			TaskPtr p_task = std::make_shared<Task>([&]() {});

			Worker worker;
			worker.AddTask(p_task);

			std::this_thread::sleep_for(std::chrono::seconds(1));

			Assert::IsFalse(worker.CancelTask(p_task->GetId()));

		}

		TEST_METHOD(WorkerCancelTaskException)
		{
			TaskPtr p_task = std::make_shared<Task>([&]() {});

			Worker worker;
			worker.AddTask(p_task);

			std::this_thread::sleep_for(std::chrono::seconds(1));

			Assert::ExpectException<std::invalid_argument>([&]()
			{
				worker.CancelTask(Utility::GenerateUniqueID());
			});

		}




	};
}