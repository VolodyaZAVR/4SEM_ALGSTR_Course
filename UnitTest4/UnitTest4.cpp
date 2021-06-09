#include "pch.h"
#include "CppUnitTest.h"
#include "../course/List.h"
#include "../course/Graph.h"
#include "../course/Edm-Karp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(List_Test)
	{
	public:
		TEST_METHOD(push_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			Assert::IsTrue(list[0] == 5);
			Assert::IsTrue(list[2] == 7);
			list.~List();
		}

		TEST_METHOD(pop_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			Assert::IsTrue(5 == list.pop_front());
			Assert::IsTrue(list[0] == 6);
			list.~List();
		}

		TEST_METHOD(find_test)
		{
			List<int> list;
			list.push_back(5);
			list.push_back(6);
			list.push_back(7);
			Assert::IsTrue(list[list.find(5)] == 5);
			Assert::IsTrue(list[list.find(6)] == 6);
			Assert::IsTrue(list[list.find(7)] == 7);
			list.~List();
		}

		TEST_METHOD(clear_test)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.clear();
			Assert::IsTrue(list.isEmpty());
			list.~List();
		}

		TEST_METHOD(at_test)
		{
			List<int> list;
			list.push_back(0);
			list.push_back(1);
			list.push_back(2);
			list.push_back(10);
			list.push_back(4);
			list.push_back(7);
			list.push_back(6);
			Assert::IsTrue(list.at(5) == 7);
			Assert::IsTrue(list.at(3) == 10);
			list.~List();
		}

		TEST_METHOD(test_find)
		{
			List<int> list;
			list.push_back(0);
			list.push_back(1);
			list.push_back(2);
			list.push_back(10);
			list.push_back(4);
			list.push_back(7);
			list.push_back(6);
			Assert::IsTrue(list.find(10) == 3);
			Assert::IsTrue(list.find(7) == 5);
			list.~List();
		}
	};

	TEST_CLASS(Graph_Test)
	{
	public:
		TEST_METHOD(get_value_test)
		{
			int size = 2;
			Graph g(size);
			Assert::IsTrue(g.getValue(0, 1) == 0);
			Assert::IsTrue(g.getValue(1, 0) == 0);
			Assert::IsTrue(g.getValue(1, 1) == 0);
		}

		TEST_METHOD(set_value_test)
		{
			int size = 2;
			Graph g(size);
			g.setValue(0, 1, 1);
			g.setValue(1, 0, 2);
			Assert::IsTrue(g.getValue(0, 1) == 1);
			Assert::IsTrue(g.getValue(1, 0) == 2);
			Assert::IsTrue(g.getValue(1, 1) == 0);
		}

		TEST_METHOD(bfs_test)
		{
			int size = 3;
			Graph* graph = new Graph(size);
			Graph* flow = new Graph(size);
			graph->setValue(0, 1, 1);
			graph->setValue(0, 2, 1);
			graph->setValue(1, 2, 1);
			Assert::IsTrue(graph->BFS(*flow)->at(0) == 0);
			Assert::IsTrue(graph->BFS(*flow)->at(1) == 2);
		}
	};
}
