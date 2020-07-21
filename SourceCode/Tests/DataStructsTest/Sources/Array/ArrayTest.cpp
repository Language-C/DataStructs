#include "pch.h"
#include "CppUnitTest.h"
#include "../ClassMeta/Point3DMeta.h"

extern "C"
{
#include "../../DataStructs/Sources/Array.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArrayTest
{
    constexpr Sizetype ARRAY_SIZE = 32U;

    TEST_CLASS(Create)
    {
        ClassMeta Ponit3DMeta = MakeClassMeta(Point3D);
        Array* array = ArrayCreate(ARRAY_SIZE, &Ponit3DMeta);
    public:
        ~Create() {
            ArrayDestroy(&array);
        }

        TEST_METHOD(CreateWithInvalidParam) {
            Array* arr = ArrayCreate(ARRAY_SIZE, Null);
            Assert::IsNull(arr);
        }

        TEST_METHOD(CreateWithValidParam) {
            Assert::IsNotNull(array);
        }

        TEST_METHOD(CreateWithSize_0) {
            Array* arr = ArrayCreate(0U, &Ponit3DMeta);
            Assert::IsNull(arr);
        }
    };

    TEST_CLASS(Fill)
    {
        Array* array = ArrayCreate(ARRAY_SIZE, Point3DConfig());
        Point3D Point = Point3D(2, 3, 1);
    public:
        ~Fill() {
            ArrayDestroy(&array);
        }
        TEST_METHOD(FillData) {
            ArrayFill(array, &Point);
            Point3D* data = ((Point3D*)ArrayGet(array, ARRAY_SIZE - 1));
            Assert::AreEqual(data->X, Point.X);
        }

        TEST_METHOD(FillNull) {
            ArrayFill(array, Null);
        }
    };

    TEST_CLASS(IsValid)
    {
        Array* array = ArrayCreate(ARRAY_SIZE, Point3DConfig());
        Point3D Point = Point3D(2, 3, 1);
    public:
        ~IsValid() {
            ArrayDestroy(&array);
        }

        TEST_METHOD(WhenNull) {
            Assert::IsFalse(ArrayIsValid(Null));
        }

        TEST_METHOD(Valid) {
            Assert::IsTrue(ArrayIsValid(array));
        }
    };

    TEST_CLASS(Destroy)
    {
    public:
        TEST_METHOD(CanDestroyNull) {
            ArrayDestroy(Null);
            Assert::IsTrue(True);
        }

        TEST_METHOD(CanDestroyNullptr) {
            void* ptr = Null;
            ArrayDestroy(&ptr);
            Assert::IsNull(ptr);
        }

        TEST_METHOD(CanDestroyPtr) {
            Array* array = ArrayCreate(ARRAY_SIZE, Point3DConfig());
            ArrayDestroy(&array);
            Assert::IsNull(array);
        }
    };

    TEST_CLASS(Get)
    {
        Array* array = ArrayCreate(ARRAY_SIZE, Point3DConfig());
    public:
        ~Get() {
            ArrayDestroy(&array);
        }

        TEST_METHOD(Get_30) {
            Assert::IsNull(ArrayGet(array, ARRAY_SIZE));
        }

        TEST_METHOD(Get_29) {
            Assert::IsNotNull(ArrayGet(array, ARRAY_SIZE - 1));
        }
    };

    TEST_CLASS(Set)
    {
        Array* array = ArrayCreate(ARRAY_SIZE, Point3DConfig());
    public:
        ~Set() {
            ArrayDestroy(&array);
        }

        TEST_METHOD(SetToNull) {
            Assert::IsTrue(ArraySet(array, ARRAY_SIZE - 1, Null));
        }

        TEST_METHOD(Set_0) {
            Point3D point = Point3D(1);
            Assert::IsTrue(ArraySet(array, ARRAY_SIZE - 1, &point));
        }
    };
}