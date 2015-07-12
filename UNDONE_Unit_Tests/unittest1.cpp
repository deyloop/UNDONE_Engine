#include "stdafx.h"
#include "CppUnitTest.h"
#include <ObjectContainer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UNDONE_ENGINE;

namespace UNDONE_Unit_Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ObjectContainer<int> int_cont;
			for (int i = 0; i <= 20; ++i){
				int_cont.Add(i);
			}

			for (int j = 0; j <= 20; ++j){
				Assert::AreEqual(j, int_cont[j]);
			}

			
		}

		TEST_METHOD(RangedBasedForLoops){
			ObjectContainer<int> int_cont;
			for (int i = 0; i <= 20; ++i){
				int_cont.Add(i);
			}

			int k = 0;
			for (auto& num : int_cont){
				Assert::AreEqual(k, num);
				++k;
			}
		}

	};
}