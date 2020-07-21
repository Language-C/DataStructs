#include "pch.h"
#include "CppUnitTest.h"
#include "../ClassMeta/Point3DMeta.h"

extern "C"
{
#include <ClassInstance.h>
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClassInstanceTest
{
    TEST_CLASS(InstanceCreate)
    {
        ClassMeta Point3DMeta = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(CreateWithNull) {
            Assert::IsNull(NewInstance(Null));
        }

        TEST_METHOD(CreateWithSize_0) {
            Point3DMeta.BytesOfValueClass = 0;
            Assert::IsNull(NewInstance(&Point3DMeta));
        }

        TEST_METHOD(CreateWithoutConstructor) {
            Point3DMeta.Constructor = Null;
            Point3D* point = (Point3D*)NewInstance(&Point3DMeta);
            Assert::AreNotEqual(point->X, 0);
        }

        TEST_METHOD(Create) {
            Point3D* point = (Point3D*)NewInstance(&Point3DMeta);
            Assert::AreEqual(point->X, 0);
        }
    };

    TEST_CLASS(InstanceFree)
    {
        ClassMeta* Point3DMeta = Point3DConfig();
    public:
        TEST_METHOD(FreeWithNull) {
            FreeInstance(Null, Null);
        }

        TEST_METHOD(FreeWithoutConfig) {
            void * ptr = NewInstance(Point3DMeta);
            FreeInstance(ptr, Null);
        }

        TEST_METHOD(Free) {
            void * ptr = NewInstance(Point3DMeta);
            FreeInstance(ptr, Point3DMeta);
        }
    };

    TEST_CLASS(InstancesCreate)
    {
        ClassMeta Point3DMeta = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(CreateWithSize_0) {
            void* instances = NewInstances(0, &Point3DMeta);
            Assert::IsNull(instances);
        }

        TEST_METHOD(CreateWithNoConfig) {
            void* instances = NewInstances(10, Null);
            Assert::IsNull(instances);
        }

        TEST_METHOD(CreateWithClassBytes_0) {
            Point3DMeta.BytesOfValueClass = 0;
            void* instances = NewInstances(10, Null);
            Assert::IsNull(instances);
        }

        TEST_METHOD(Create) {
            void* instances = NewInstances(10, &Point3DMeta);
            Assert::IsNotNull(instances);
            FreeInstances(instances, 10, &Point3DMeta);
        }
    };

    TEST_CLASS(InstanceCreateWithParams)
    {
        ClassMeta Point3DMeta = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(CreateWithNull) {
            Assert::IsNull(NewInstanceWithParams(Null, Null));
        }

        TEST_METHOD(CreateWithSize_0) {
            Point3DMeta.BytesOfValueClass = 0;
            Assert::IsNull(NewInstanceWithParams(&Point3DMeta, Null));
        }

        TEST_METHOD(CreateWithoutConstructor) {
            Point3DMeta.ParamConstructor = Null;
            Point3D* point = (Point3D*)NewInstanceWithParams(&Point3DMeta, Null);
            Assert::AreNotEqual(point->X, 0);
        }

        TEST_METHOD(Create) {
            Point3DParams params = { 0, 0, 0 };
            Point3D* point = (Point3D*)NewInstanceWithParams(&Point3DMeta, &params);
            Assert::AreEqual(point->X, 0);
        }
    };
}