#include "pch.h"
#include "CppUnitTest.h"
#include "../../lab1/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab1UnitTests
{
	TEST_CLASS(lab1UnitTests)
	{
	public:
		
		TEST_METHOD(insert)
		{
			string a;
			rbtree new_tree;
			new_tree.insert(3, 'A');
			a = "A ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.insert(33, 'B');
			a = "A B ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.insert(333, 'C');
			a = "B A C ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.insert(1, 'D');
			a = "B A D C ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.insert(20, 'E');
			a = "B A D E C ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.insert(30, 'F');
			a = "B A D E F C ";
			Assert::AreEqual(a, new_tree.get_values());
		}

		TEST_METHOD(insert_except)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
				new_tree.insert(3, 'A');
				new_tree.insert(3, 'B');
				Assert::IsTrue(0);
			}
			catch (exception& invalid_argument)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(remove)
		{
			string a;
			rbtree new_tree;
			new_tree.insert(3, 'A');
			new_tree.insert(33, 'B');
			new_tree.insert(333, 'C');
			new_tree.insert(1, 'D');
			new_tree.insert(20, 'E');
			new_tree.insert(30, 'F');

			new_tree.remove(1);
			a = "B E A F C ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.remove(30);
			a = "B E A C ";
			Assert::AreEqual(a, new_tree.get_values());

			new_tree.insert(1, 'D');
			new_tree.insert(30, 'F');
			new_tree.remove(333);
			a = "A D F E B ";
			Assert::AreEqual(a, new_tree.get_values());
		}

		TEST_METHOD(remove_except)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
			new_tree.remove(3);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(remove_except2)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
				new_tree.insert(3, 'A');
				new_tree.remove(33);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(find)
		{
				rbtree new_tree;
				char a = 'C';
				new_tree.insert(3, 'A');
				new_tree.insert(33, 'B');
				new_tree.insert(333, 'C');
				Assert::AreEqual(a, new_tree.find(333));
		}

		TEST_METHOD(find_except1)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
				new_tree.find(1);
				Assert::IsTrue(0);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(find_except2)
		{
			rbtree new_tree;
			bool a = 0;
			new_tree.insert(1, 'A');
			try
			{
				new_tree.find(0);
				Assert::IsTrue(0);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(get_keys_excep)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
				new_tree.get_keys();
				Assert::IsTrue(0);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(get_values_except)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
				new_tree.get_values();
				Assert::IsTrue(0);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}

		TEST_METHOD(print_except)
		{
			rbtree new_tree;
			bool a = 0;
			try
			{
				new_tree.print();
				Assert::IsTrue(0);
			}
			catch (exception& runtime_error)
			{
				a = 1;
			}
			Assert::IsTrue(a);
		}
	};
}
