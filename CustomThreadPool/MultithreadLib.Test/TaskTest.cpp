#include "stdafx.h"

#include "../MultithreadLib/Task.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace MultithreadLibTest
{
	TEST_CLASS(TaskTest)
	{
	public:
		TEST_METHOD(operatorless)
		{

			Task task1([&]() {}, EPriority::Critical);
			Task task2([&]() {}, EPriority::High);

			Assert::IsTrue(task2 < task1);

      Task task3([&]() {}, EPriority::Medium);
      Task task4([&]() {}, EPriority::Low);

      Assert::IsTrue(task4 < task3);

      Task task5([&]() {}, EPriority::Critical);

      Assert::IsTrue(task3 < task5);
		}
	};

}