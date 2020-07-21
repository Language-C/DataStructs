#include "pch.h"
#include "CppUnitTest.h"
#include "../ClassMeta/Point3DMeta.h"

extern "C"
{
#include <Stack.h>
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackTest
{
    TEST_CLASS(Create)
    {
    public:
        TEST_METHOD(WhenNull) {
            Stack* stack = StackCreate(Null);
            Assert::IsNotNull(stack);
            StackDestroy(&stack);
        }

        TEST_METHOD(CanCreate) {
            Stack* stack = StackCreate(Point3DConfig());
            Assert::IsNotNull(stack);
            StackDestroy(&stack);
        }
    };

    TEST_CLASS(Destroy)
    {
    public:
        TEST_METHOD(WhenNull) {
            Stack* stack = Null;
            StackDestroy(&stack);
            Assert::IsNull(stack);
        }

        TEST_METHOD(DestroyNull) {
            StackDestroy(Null);
        }

        TEST_METHOD(CanDestroy) {
            Stack* stack = StackCreate(Point3DConfig());
            StackDestroy(&stack);
            Assert::IsNull(stack);
        }
    };

    TEST_CLASS(Top)
    {
        Stack* stack = StackCreate(Point3DConfig());
    public:
        ~Top() {
            StackDestroy(&stack);
        }

        TEST_METHOD(NoData) {
            Assert::IsNull(StackTop(stack));
        }

        TEST_METHOD(CanDestroy) {
            Point3D* point = new Point3D();
            StackPush(stack, point);
            Assert::IsNotNull(StackTop(stack));
        }
    };

    TEST_CLASS(Size)
    {
        Stack* stack = StackCreate(Point3DConfig());
    public:
        ~Size() {
            StackDestroy(&stack);
        }

        TEST_METHOD(Size_0) {
            Assert::AreEqual(StackSize(stack), (Sizetype)0U);
        }

        TEST_METHOD(Size_1) {
            Point3D* point = new Point3D();
            StackPush(stack, point);
            Assert::AreEqual(StackSize(stack), (Sizetype)1U);
        }
    };

    TEST_CLASS(Empty)
    {
        Stack* stack = StackCreate(Point3DConfig());
    public:
        ~Empty() {
            StackDestroy(&stack);
        }

        TEST_METHOD(IsEmpty) {
            Assert::IsTrue(StackIsEmpty(stack));
        }

        TEST_METHOD(Size_1) {
            Point3D* point = new Point3D();
            StackPush(stack, point);
            Assert::IsFalse(StackIsEmpty(stack));
        }
    };

    TEST_CLASS(Push)
    {
        Stack* stack = StackCreate(Point3DConfig());
    public:
        ~Push() {
            StackDestroy(&stack);
        }

        TEST_METHOD(PushNull) {
            Assert::IsTrue(StackPush(stack, Null));
        }

        TEST_METHOD(PushData) {
            Point3D* point = new Point3D();
            StackPush(stack, point);
            Assert::IsFalse(StackIsEmpty(stack));
        }
    };

    TEST_CLASS(Pop)
    {
        Stack* stack = StackCreate(Point3DConfig());
    public:
        ~Pop() {
            StackDestroy(&stack);
        }

        TEST_METHOD(PopNoData) {
            StackPop(stack);
            Assert::IsNull(StackTop(stack));
        }

        TEST_METHOD(PopData) {
            Point3D* point = new Point3D();
            StackPush(stack, point);
            StackPop(stack);
            Assert::IsNull(StackTop(stack));
        }
        TEST_METHOD(PopData_2) {
            Point3D* point = new Point3D();
            Point3D* point2 = new Point3D();
            StackPush(stack, point);
            StackPush(stack, point2);
            StackPop(stack);
            Assert::IsNotNull(StackTop(stack));
        }
    };
}
