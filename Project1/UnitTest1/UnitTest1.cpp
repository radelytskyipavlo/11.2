#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1) 
    {
    public:

        TEST_METHOD(TestPercentagePhysicsMath)
        {
            Student students[3]; 
            students[0] = { "tqwtqwtq", 3, KN, 5, 5, 5 }; 
            students[1] = { "tqgqgwehgw", 2, IN, 4, 4, 4 };
            students[2] = { "rhevgrew", 4, FI, 3, 3, 3 };

            
            Assert::AreEqual(66.6667, percentagePhysicsMath(students, 3), 0.0001);
        }

        TEST_METHOD(TestCountProgrammingGrades)
        {
            Student students[4]; 
            students[0] = { "rwqtq", 3, KN, 5, 5, 5 }; 
            students[1] = { "rqw", 2, IN, 4, 4, 4 };
            students[2] = { "trqw", 4, FI, 3, 3, 3 };
            students[3] = { "brwq", 2, KN, 4, 4, 5 };

       
            Assert::AreEqual(2, CountProgrammingGrades(students, 4, 5));
        }
    };
}