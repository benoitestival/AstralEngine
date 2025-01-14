#pragma once
#include "BaseTypes/Matrix.h"
#include "BaseTypes/Rotator.h"
#include "BaseTypes/Vector2D.h"
#include "BaseTypes/Vector3D.h"

#define COMMA ,

#define DECLARE_CONCRETE_MATH_TYPE(ConcreteName, GenericType)\
    using ConcreteName = GenericType;


//Vector 2D
DECLARE_CONCRETE_MATH_TYPE(FVector2D, TVector2D<float>)
DECLARE_CONCRETE_MATH_TYPE(FIntVector2D, TVector2D<int>)

//Vector 3D
DECLARE_CONCRETE_MATH_TYPE(FVector, TVector3D<float>)
DECLARE_CONCRETE_MATH_TYPE(FIntVector, TVector3D<int>)

//Rotator
DECLARE_CONCRETE_MATH_TYPE(FRotator, TRotator<float>)

//Matrix
DECLARE_CONCRETE_MATH_TYPE(FMatrix3X3, TMatrix<float COMMA 3 COMMA 3>)
DECLARE_CONCRETE_MATH_TYPE(FMatrix4X4, TMatrix<float COMMA 4 COMMA 4>)

//Type to add:
// - Quat
// - Triangle
// - Rect
// - Plane
// - Box

class AMathsUtils {
public:
    static bool IsNearlyEqual(const FVector2D& Vec1, const FVector2D& Vec2, float Tolerance = 0.00001f);
    static bool IsNearlyEqual(float Number1, float Number2, float Tolerance = 0.00001f);
};

