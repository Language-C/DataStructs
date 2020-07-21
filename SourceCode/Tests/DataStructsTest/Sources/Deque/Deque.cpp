#include "pch.h"
#include "CppUnitTest.h"
#include "../ClassMeta/Point3DMeta.h"

extern "C"
{
#include <deque.h>
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DequeTest
{
    TEST_CLASS(Create)
    {
    public:
        TEST_METHOD(CreateWithNull) {
            Assert::IsNull(DequeCreate(Null));
        }

        TEST_METHOD(CanCreate) {
            void* deque = DequeCreate(Point3DConfig());
            Assert::IsNotNull(deque);
            DequeDestroy(&deque);
        }
    };

    TEST_CLASS(Destroy)
    {
    public:
        TEST_METHOD(DestroyNull) {
            DequeDestroy(Null);
        }

        TEST_METHOD(CanDestroy) {
            void* deque = DequeCreate(Point3DConfig());
            DequeDestroy(&deque);
            Assert::IsNull(deque);
        }
    };

    TEST_CLASS(PushBack)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~PushBack() {
            DequeDestroy(&deque);
        }
        TEST_METHOD(PushNull) {
            DequePushBack(deque, Null);
        }

        TEST_METHOD(Push_33) {
            for (int i = 0; i < 33; i++) {
                Assert::IsTrue(DequePushBack(deque, new Point3D(0)));
            }
        }

        TEST_METHOD(PopBeforePush_33) {
            DequePushBack(deque, new Point3D(0));
            DequePushBack(deque, new Point3D(0));
            DequePushBack(deque, new Point3D(0));
            DequePushBack(deque, new Point3D(0));
            DequePopFront(deque);
            DequePopFront(deque);
            DequePopFront(deque);
            DequePopFront(deque);
            for (int i = 0; i < 33; i++) {
                Assert::IsTrue(DequePushBack(deque, new Point3D(i)));
            }
            Point3D* point = nullptr;
            for (int i = 0; i < 33; i++) {
                point = ((Point3D*)DequePickFront(deque));
                Assert::AreEqual(point->X, i);
                DequePopFront(deque);
            }
        }
    };

    TEST_CLASS(PopFront)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~PopFront() {
            DequeDestroy(&deque);
        }

        TEST_METHOD(PopEmptyDeque) {
            DequePopFront(deque);
        }

        TEST_METHOD(CanPop) {
            DequePushBack(deque, new Point3D(0));
            DequePopFront(deque);
            Assert::AreEqual((int)DequeSize(deque), 0);
        }

        TEST_METHOD(PushBeforePop) {
            for (int i = 0; i < 33; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 33; i++) {
                DequePopFront(deque);
            }
            Assert::AreEqual((int)DequeSize(deque), 0);
        }

        TEST_METHOD(PushBeforePop_2) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopFront(deque);
            }
            for (int i = 0; i < 30; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 30; i++) {
                DequePopFront(deque);
            }
            Assert::AreEqual((int)DequeSize(deque), 0);
        }
    };

    TEST_CLASS(PopBack)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~PopBack() {
            DequeDestroy(&deque);
        }

        TEST_METHOD(PopEmptyDeque) {
            DequePopBack(deque);
        }

        TEST_METHOD(CanPop) {
            DequePushBack(deque, new Point3D(0));
            DequePopBack(deque);
            Assert::AreEqual((int)DequeSize(deque), 0);
        }

        TEST_METHOD(PushBeforePop) {
            for (int i = 0; i < 33; i++) {
                DequePushFront(deque, new Point3D(i));
            }
            for (int i = 0; i < 33; i++) {
                DequePopBack(deque);
            }
            Assert::AreEqual((int)DequeSize(deque), 0);
        }

        TEST_METHOD(PushBeforePop_2) {
            for (int i = 0; i < 5; i++) {
                DequePushFront(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopBack(deque);
            }
            for (int i = 0; i < 30; i++) {
                DequePushFront(deque, new Point3D(i));
            }
            for (int i = 0; i < 30; i++) {
                DequePopBack(deque);
            }
            Assert::AreEqual((int)DequeSize(deque), 0);
        }
    };

    TEST_CLASS(IsEmpty)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~IsEmpty() {
            DequeDestroy(&deque);
        }

        TEST_METHOD(Empty) {
            Assert::IsTrue(DequeIsEmpty(deque));
        }

        TEST_METHOD(IsNotEmpty) {
            DequePushBack(deque, new Point3D(0));
            Assert::IsFalse(DequeIsEmpty(deque));
        }

        TEST_METHOD(Empty_2) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopFront(deque);
            }
            Assert::IsTrue(DequeIsEmpty(deque));
        }

        TEST_METHOD(Empty_3) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopFront(deque);
            }
            for (int i = 0; i < 30; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 30; i++) {
                DequePopFront(deque);
            }
            Assert::IsTrue(DequeIsEmpty(deque));
        }
    };

    TEST_CLASS(Size)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~Size() {
            DequeDestroy(&deque);
        }

        TEST_METHOD(Size_0) {
            Assert::AreEqual((int)DequeSize(deque), 0);
        }

        TEST_METHOD(Size_1) {
            DequePushBack(deque, new Point3D(0));
            Assert::AreEqual((int)DequeSize(deque), 1);
        }

        TEST_METHOD(Szie_5) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            Assert::AreEqual((int)DequeSize(deque), 5);
        }

        TEST_METHOD(Size_30) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopFront(deque);
            }
            for (int i = 0; i < 30; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            Assert::AreEqual((int)DequeSize(deque), 30);
        }
    };

    TEST_CLASS(PickFront)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~PickFront() {
            DequeDestroy(&deque);
        }

        TEST_METHOD(PickWhenEmpty) {
            Assert::IsNull(DequePickFront(deque));
        }

        TEST_METHOD(Size_1) {
            Point3D * point = new Point3D(0);
            DequePushBack(deque, point);
            Assert::AreEqual(DequePickFront(deque), (void*)point);
        }

        TEST_METHOD(Szie_5) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            Assert::AreEqual(((Point3D*)DequePickFront(deque))->X, 0);
        }

        TEST_METHOD(Size_30) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopFront(deque);
            }
            for (int i = 0; i < 30; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            Assert::AreEqual(((Point3D*)DequePickFront(deque))->X, 0);
        }
    };

    TEST_CLASS(PushFront)
    {
        void* deque = DequeCreate(Point3DConfig());
    public:
        ~PushFront() {
            DequeDestroy(&deque);
        }

        TEST_METHOD(PushNull) {
            DequePushFront(deque, Null);
            Assert::AreEqual((int)DequeSize(deque), 1);
        }

        TEST_METHOD(PushFront_33) {
            for (int i = 0; i < 33; i++) {
                Assert::IsTrue(DequePushFront(deque, new Point3D(0)));
            }
        }

        TEST_METHOD(PopBeforePush_33) {
            for (int i = 0; i < 5; i++) {
                DequePushBack(deque, new Point3D(i));
            }
            for (int i = 0; i < 5; i++) {
                DequePopFront(deque);
            }
            for (int i = 0; i < 33; i++) {
                DequePushFront(deque, new Point3D(i));
            }
            Assert::AreEqual((int)DequeSize(deque), 33);
        }
    };
}
