#include "pch.h"
#include "CppUnitTest.h"
#include "Point3DMeta.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClassMetaTest
{
    TEST_CLASS(IsInValid)
    {
        ClassMeta Ponit3DMeta = MakeClassMeta(Point3D);
    public:

        TEST_METHOD(InvalidParam_Null) {
            Assert::IsFalse(ClassMetaIsValid(Null));
        }

        TEST_METHOD(InvalidParam_0) {
            Ponit3DMeta.BytesOfValueClass = 0;
            Assert::IsFalse(ClassMetaIsValid(&Ponit3DMeta));
        }

        TEST_METHOD(InvalidConstruct) {
            Ponit3DMeta.Constructor = Null;
            Assert::IsFalse(ClassMetaIsValid(&Ponit3DMeta));
        }

        TEST_METHOD(InvalidCopyConstruct) {
            Ponit3DMeta.CopyConstruct = Null;
            Assert::IsFalse(ClassMetaIsValid(&Ponit3DMeta));
        }
    };

    TEST_CLASS(IsValid)
    {
        ClassMeta Ponit3DMeta = MakeClassMeta(Point3D);
    public:
        TEST_METHOD(ValidParam) {
            Assert::IsTrue(ClassMetaIsValid(&Ponit3DMeta));
        }
    };
}