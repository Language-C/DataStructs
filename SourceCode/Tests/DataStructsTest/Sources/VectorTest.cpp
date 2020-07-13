#include "pch.h"
#include "CppUnitTest.h"

extern "C"
{
#include "../../DataStructs/Sources/Vector/Vector.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorTest
{
	TEST_CLASS(Create)
	{
	public:
		TEST_METHOD(CreateByDefault)
		{
            Vector* vector = VectorCreate();
            Assert::IsNotNull(vector);
            VectorDestroyWithFreeElements(&vector);
		}
	};

    TEST_CLASS(DestroyAndFreeAll)
    {
    public:
        TEST_METHOD(WillFree)
        {
            Vector* vector = VectorCreate();
            VectorDestroyWithFreeElements(&vector);
            Assert::IsNull(vector);
        }
    };

    TEST_CLASS(Len)
    {
    public:
        TEST_METHOD(DefaultLength)
        {
            Vector* vector = VectorCreate();
            Assert::AreEqual(VectorLen(vector), 0U);
            VectorDestroyWithFreeElements(&vector);
        }
    };

    TEST_CLASS(Capacity)
    {
    public:
        TEST_METHOD(InitializationCapacity)
        {
            Vector* vector = VectorCreate();
            Assert::AreEqual(VectorCapacity(vector), VectorGetInitializationCapacity());
            VectorDestroyWithFreeElements(&vector);
        }
    };

    TEST_CLASS(SetInitializationCapacity)
    {
    public:
        TEST_METHOD(SetTo_64)
        {
            VectorSetInitializationCapacity(64U);
            Vector* vector = VectorCreate();
            Assert::AreEqual(VectorCapacity(vector), 64U);
            VectorDestroyWithFreeElements(&vector);
        }

        TEST_METHOD(SetTo_0)
        {
            VectorSetInitializationCapacity(0U);
            Vector* vector = VectorCreate();
            Assert::AreNotEqual(VectorCapacity(vector), 0U);
            VectorDestroyWithFreeElements(&vector);
        }
    };

    TEST_CLASS(ReSetCapacity)
    {
        Vector* vector = VectorCreate();
        const unsigned int NewCapacity = 1000;
    public:
        ~ReSetCapacity() 
        {
            VectorDestroyWithFreeElements(&vector);
        }
        TEST_METHOD(NewCapacityIs_0)
        {
            Bool result = VectorReSetCapacity(vector, 0);
            Assert::AreEqual(result, False);
        }

        TEST_METHOD(NewCapacityLessThanCurrentCapacity)
        {
            Bool result = VectorReSetCapacity(vector, VectorCapacity(vector) - 1);
            Assert::AreEqual(result, False);
        }

        TEST_METHOD(NewCapacityEqualCurrentCapacity)
        {
            Bool result = VectorReSetCapacity(vector, VectorCapacity(vector));
            Assert::AreEqual(result, False);
        }

        TEST_METHOD(NewCapacityIs_1000)
        {
            Bool result = VectorReSetCapacity(vector, NewCapacity);
            Assert::AreEqual(result, True);
        }

        TEST_METHOD(DataNotChanged)
        {
            void *ptr = malloc(sizeof(int));
            VectorAdd(vector, ptr);
            VectorReSetCapacity(vector, NewCapacity);
            void *ptr2 = VectorGetByIdx(vector, 0U);
            Assert::AreEqual(ptr, ptr2);
        }
    };

    TEST_CLASS(Add)
    {
        Vector* vector = VectorCreate();
        const unsigned int NewCapacity = 1000;
    public:
        ~Add()
        {
            VectorDestroyWithFreeElements(&vector);
        }

        TEST_METHOD(AddToFirst)
        {
            void *ptr = malloc(sizeof(int));
            VectorAdd(vector, ptr);
            Assert::AreEqual(VectorGetByIdx(vector, 0), ptr);
        }

        TEST_METHOD(CanAddForever)
        {
            for (unsigned int i = 0; i < 100000U; ++i)
            {
                VectorAdd(vector, malloc(sizeof(int)));
            }

            Assert::AreEqual(VectorLen(vector), 100000U);
        }

        TEST_METHOD(AddArray)
        {
            void* arr[3] = { new int(5), new int(5), new int(5) };
            VectorAddArray(vector, arr, 3U);

            Assert::AreEqual(VectorLen(vector), 3U);
            for (unsigned int i = 0; i < 3U; i++)
            {
                Assert::AreEqual(*(int*)VectorGetByIdx(vector, i), 5);
            }
        }
    };

    TEST_CLASS(UpdateByIdx)
    {
        Vector* vector = VectorCreate();
    public:
        ~UpdateByIdx()
        {
            VectorDestroyWithFreeElements(&vector);
        }

        TEST_METHOD(ReturnsFalseWhenEmpty)
        {
            Assert::AreEqual(VectorUpdateByIdx(vector, 0, Null), False);
        }

        TEST_METHOD(ReturnsTrueWhenValidParams)
        {
            VectorAdd(vector, malloc(sizeof(int)));
            Assert::AreEqual(VectorUpdateByIdx(vector, 0, Null), True);
        }
    };

    TEST_CLASS(GetByIdx)
    {
        Vector* vector = VectorCreate();
    public:
        ~GetByIdx()
        {
            VectorDestroyWithFreeElements(&vector);
        }

        TEST_METHOD(GetFirstWhenSizeIs_0)
        {
            Assert::IsNull(VectorGetByIdx(vector, 0));
        }

        TEST_METHOD(GetFirstWhenSizeIs_1)
        {
            void *ptr = malloc(sizeof(int));
            VectorAdd(vector, ptr);
            Assert::AreEqual(VectorGetByIdx(vector, 0), ptr);
        }

        TEST_METHOD(GetBy_10000)
        {
            Assert::IsNull(VectorGetByIdx(vector, 10000U));
        }
    };

    TEST_CLASS(RemoveByIdx)
    {
        Vector* vector = VectorCreate();
    public:
        ~RemoveByIdx()
        {
            VectorDestroyWithFreeElements(&vector);
        }

        TEST_METHOD(RemoveFirstWhenSizeIs_0)
        {
            Assert::IsNull(VectorRemoveByIdx(vector, 0));
        }

        TEST_METHOD(RemoveFirstWhenSizeIs_1)
        {
            void *ptr = malloc(sizeof(int));
            VectorAdd(vector, ptr);
            Assert::AreEqual(VectorRemoveByIdx(vector, 0), ptr);
            free(ptr);
        }

        TEST_METHOD(RemoveBy_10000)
        {
            Assert::IsNull(VectorRemoveByIdx(vector, 10000U));
        }
    };

    TEST_CLASS(RemoveAndFreeByIdx)
    {
        Vector* vector = VectorCreate();
    public:
        ~RemoveAndFreeByIdx()
        {
            VectorDestroyWithFreeElements(&vector);
        }

        TEST_METHOD(RemoveFirstWhenSizeIs_0)
        {
            Assert::AreEqual(VectorRemoveAndFreeByIdx(vector, 0), False);
        }

        TEST_METHOD(RemoveFirstWhenSizeIs_1)
        {
            void *ptr = malloc(sizeof(int));
            VectorAdd(vector, ptr);
            Assert::AreEqual(VectorRemoveAndFreeByIdx(vector, 0), True);
        }

        TEST_METHOD(RemoveBy_10000)
        {
            Assert::AreEqual(VectorRemoveAndFreeByIdx(vector, 10000U), False);
        }
    };

    void TestCallbackWithNoParam(void* data) 
    {
        (*(int*)data)++;
    }

    void TestCallbackWithOneParam(void* data, void* param) 
    {
        TestCallbackWithNoParam(data);
        (*(int*)param)++;
    }

    void TestCallbackWithTwoParams(void* data, void* param1, void* param2)
    {
        TestCallbackWithOneParam(data, param1);
        (*(int*)param2)++;
    }

    void TestCallbackWithThreeParams(void* data, void* param1, void* param2, void* params3)
    {
        TestCallbackWithTwoParams(data, param1, param2);
        (*(int*)params3)++;
    }

    TEST_CLASS(Each)
    {
        Vector* vector = VectorCreate();
    public:
        Each()
        {
            for (unsigned int i = 0; i < 5U; i++)
            {
                VectorAdd(vector, new int(0));
            }
        }
        ~Each() { VectorDestroyWithFreeElements(&vector); }

        TEST_METHOD(EachWithNoParam)
        {
            VectorEachWithNoParam(vector, TestCallbackWithNoParam);
            for (unsigned int i = 0; i < 5U; i++)
            {
                Assert::AreEqual(*(int*)VectorGetByIdx(vector, i), 1);
            }
        }

        TEST_METHOD(EachWithOneParam)
        {
            int param = 0;
            VectorEachWithOneParam(vector, TestCallbackWithOneParam, &param);
            for (unsigned int i = 0; i < 5U; i++)
            {
                Assert::AreEqual(*(int*)VectorGetByIdx(vector, i), 1);
            }
            Assert::AreEqual(param, 5);
        }

        TEST_METHOD(EachWithTwoParams)
        {
            int param1 = 0, param2 = 0;
            VectorEachWithTwoParams(vector, TestCallbackWithTwoParams, &param1, &param2);

            for (unsigned int i = 0; i < 5U; i++)
            {
                Assert::AreEqual(*(int*)VectorGetByIdx(vector, i), 1);
            }
            Assert::AreEqual(param1, 5);
            Assert::AreEqual(param2, 5);
        }

        TEST_METHOD(EachWithThreeParams)
        {
            int param1 = 0, param2 = 0, param3 = 0;
            VectorEachWithThreeParams(vector, TestCallbackWithThreeParams, &param1, &param2, &param3);

            for (unsigned int i = 0; i < 5U; i++)
            {
                Assert::AreEqual(*(int*)VectorGetByIdx(vector, i), 1);
            }
            int *a[10] = { new int(5), new int(8) };
            Assert::AreEqual(param1, 5);
            Assert::AreEqual(param2, 5);
            Assert::AreEqual(param3, 5);
        }
    };
}
