#include "pch.h"
#include "CppUnitTest.h"

extern "C"
{
#include <BasicTypes/Int.h>
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Types::IntTest
{
    TEST_CLASS(NullUIntTest)
    {
    public:
        TEST_METHOD(CreateInvalid)
        {
            NullUInt result = NullUIntCreateInvalid();
            Assert::AreEqual(result.Valid, False);
        }

        TEST_METHOD(Create)
        {
            NullUInt result = NullUIntCreate(100U, True);
            Assert::AreEqual(result.Valid, True);
            Assert::AreEqual(result.Value, 100U);
        }
    };
}