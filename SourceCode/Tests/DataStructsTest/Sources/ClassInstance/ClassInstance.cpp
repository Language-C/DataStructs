#include "pch.h"
#include "CppUnitTest.h"
#include "../ClassConfigure/Point3DConfigure.h"

extern "C"
{
#include <ClassInstance.h>
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClassInstanceTest
{
    TEST_CLASS(InstanceCreate)
    {
        ClassMeta Config = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(CreateWithNull) {
            Assert::IsNull(NewInstance(Null));
        }

        TEST_METHOD(CreateWithSize_0) {
            Config.BytesOfValueClass = 0;
            Assert::IsNull(NewInstance(&Config));
        }

        TEST_METHOD(CreateWithoutConstructor) {
            Config.Constructor = Null;
            Point3D* point = (Point3D*)NewInstance(&Config);
            Assert::AreNotEqual(point->X, 0);
        }

        TEST_METHOD(Create) {
            Point3D* point = (Point3D*)NewInstance(&Config);
            Assert::AreEqual(point->X, 0);
        }
    };

    TEST_CLASS(InstanceFree)
    {
        ClassMeta* Config = Point3DConfig();
    public:
        TEST_METHOD(FreeWithNull) {
            FreeInstance(Null, Null);
        }

        TEST_METHOD(FreeWithoutConfig) {
            void * ptr = NewInstance(Config);
            FreeInstance(ptr, Null);
        }

        TEST_METHOD(Free) {
            void * ptr = NewInstance(Config);
            FreeInstance(ptr, Config);
        }
    };

    TEST_CLASS(InstancesCreate)
    {
        ClassMeta Config = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(CreateWithSize_0) {
            void* instances = NewInstances(0, &Config);
            Assert::IsNull(instances);
        }

        TEST_METHOD(CreateWithNoConfig) {
            void* instances = NewInstances(10, Null);
            Assert::IsNull(instances);
        }

        TEST_METHOD(CreateWithClassBytes_0) {
            Config.BytesOfValueClass = 0;
            void* instances = NewInstances(10, Null);
            Assert::IsNull(instances);
        }

        TEST_METHOD(Create) {
            void* instances = NewInstances(10, &Config);
            Assert::IsNotNull(instances);
            FreeInstances(instances, 10, &Config);
        }
    };

    TEST_CLASS(InstanceCreateWithParams)
    {
        ClassMeta Config = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(CreateWithNull) {
            Assert::IsNull(NewInstanceWithParams(Null, Null));
        }

        TEST_METHOD(CreateWithSize_0) {
            Config.BytesOfValueClass = 0;
            Assert::IsNull(NewInstanceWithParams(&Config, Null));
        }

        TEST_METHOD(CreateWithoutConstructor) {
            Config.ParamConstructor = Null;
            Point3D* point = (Point3D*)NewInstanceWithParams(&Config, Null);
            Assert::AreNotEqual(point->X, 0);
        }

        TEST_METHOD(Create) {
            Point3DParams params = { 0, 0, 0 };
            Point3D* point = (Point3D*)NewInstanceWithParams(&Config, &params);
            Assert::AreEqual(point->X, 0);
        }
    };
}