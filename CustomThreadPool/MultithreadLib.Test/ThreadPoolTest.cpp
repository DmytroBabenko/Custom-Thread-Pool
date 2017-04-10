#include "stdafx.h"

#include "../MultithreadLib/ThreadPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MultithreadLibTest
{
	TEST_CLASS(ThreadPoolTest)
	{
	public:

		TEST_METHOD(ExecuteTasksOneThread)
		{
			auto five_second = std::chrono::milliseconds(5000);
			auto start = std::chrono::steady_clock::now();

			{
				ThreadPool pool(1);
				TaskPtr p_task1 = std::make_shared<Task>([&]()
				{
					std::this_thread::sleep_for(five_second);
				});
				TaskPtr p_task2 = std::make_shared<Task>([&]()
				{
					std::this_thread::sleep_for(five_second);
				});
				pool.AddTaskToExecute(p_task1);
				pool.AddTaskToExecute(p_task2);
			}

			auto end = std::chrono::steady_clock::now();

			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

			Assert::IsTrue(diff >= 2 * five_second);
			Assert::IsTrue(diff < 2 * five_second + std::chrono::seconds(1));

		}


		TEST_METHOD(ExecuteTasksTwoThread)
		{
			auto five_second = std::chrono::milliseconds(5000);
			auto start = std::chrono::steady_clock::now();

			{
				ThreadPool pool(2);
				TaskPtr p_task1 = std::make_shared<Task>([&]()
				{
					std::this_thread::sleep_for(five_second);
				});
				TaskPtr p_task2 = std::make_shared<Task>([&]()
				{
					std::this_thread::sleep_for(five_second);
				});
				pool.AddTaskToExecute(p_task1);
				pool.AddTaskToExecute(p_task2);
			}

			auto end = std::chrono::steady_clock::now();

			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

			Assert::IsTrue(diff >= five_second);
			Assert::IsTrue(diff < 2 * five_second);

		}



	};
}