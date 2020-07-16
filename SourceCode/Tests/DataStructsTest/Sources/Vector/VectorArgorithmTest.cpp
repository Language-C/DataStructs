#include "pch.h"
#include "CppUnitTest.h"

extern "C"
{
#include "../../DataStructs/Sources/Vector.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorArgorithmTest
{
    void* dupInt(void* src) {
        return new int(*(int*)src);
    }

    TEST_CLASS(Dup)
    {
    public:
        TEST_METHOD(Dup_Int) {
            Vector* vector = VectorCreate();
            for (UInt i = 0; i < 1000U; i++) {
                VectorAdd(vector, new int(i));
            }

            Vector* dup = VectorDup(vector, dupInt);
            Assert::IsNotNull(dup);

            VectorDestroyWithFreeElements(&vector);
            VectorDestroyWithFreeElements(&dup);
        }
    };
}