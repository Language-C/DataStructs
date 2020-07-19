#include "pch.h"
#include "CppUnitTest.h"
#include "Point3DConfigure.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClassConfigureTest
{
    TEST_CLASS(IsInValid)
    {
        ClassMeta Ponit3DConfigure = MakeClassMeta(Point3D);
    public:

        TEST_METHOD(InvalidParam_Null) {
            Assert::IsFalse(ClassMetaIsValid(Null));
        }

        TEST_METHOD(InvalidParam_0) {
            Ponit3DConfigure.BytesOfValueClass = 0;
            Assert::IsFalse(ClassMetaIsValid(&Ponit3DConfigure));
        }

        TEST_METHOD(InvalidConstruct) {
            Ponit3DConfigure.Constructor = Null;
            Assert::IsFalse(ClassMetaIsValid(&Ponit3DConfigure));
        }

        TEST_METHOD(InvalidCopyConstruct) {
            Ponit3DConfigure.CopyConstruct = Null;
            Assert::IsFalse(ClassMetaIsValid(&Ponit3DConfigure));
        }
    };

    TEST_CLASS(IsValid)
    {
        ClassMeta* Config = Point3DConfig();
    public:
        TEST_METHOD(ValidParam) {
            Assert::IsTrue(ClassMetaIsValid(Config));
        }
    };
}