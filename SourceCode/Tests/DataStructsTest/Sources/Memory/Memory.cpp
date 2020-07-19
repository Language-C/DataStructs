#include "pch.h"
#include "CppUnitTest.h"

extern "C"
{
#include "../../DataStructs/Sources/Memory/Memory.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MemoryTest
{
    TEST_CLASS(Copy)
    {
        int i = 0, j = 1;
    public:
        TEST_METHOD(CopyNull) {
            Assert::IsFalse(MemCopy(&i, sizeof(int), Null, sizeof(int)));
        }

        TEST_METHOD(CopyToNull) {
            Assert::IsFalse(MemCopy(Null, sizeof(int), &i, sizeof(int)));
        }

        TEST_METHOD(CopyWithoutSrcSize) {
            Assert::IsFalse(MemCopy(&j, sizeof(int), &i, 0));
        }

        TEST_METHOD(CopyWithoutDstSize) {
            Assert::IsFalse(MemCopy(&j, 0, &i, sizeof(int)));
        }

        TEST_METHOD(CopyToSelf) {
            Assert::IsFalse(MemCopy(&j, sizeof(int), &j, sizeof(int)));
        }

        TEST_METHOD(Success) {
            Assert::IsTrue(MemCopy(&j, sizeof(int), &i, sizeof(int)));
            Assert::AreEqual(i, j);
        }
    };
}