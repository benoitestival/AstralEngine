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

//Class to add
// - Triangle
// - Rect
// - Box
// - Beziez
// - Circle
// - Sphere
// - Plane
// - Line
// - Quat

class AMathsUtils {
public:
    static bool IsNearlyEqual(const FVector2D& Vec1, const FVector2D& Vec2, float Tolerance = 0.00001f);
    
    static bool IsNearlyEqual(float Number1, float Number2, float Tolerance = 0.00001f);

    static FVector2D Normalize(const FVector2D& Vec);

    static FVector Normalize(const FVector& Vec);
    
    static float DotProduct2D(const FVector2D& Vec1, const FVector2D& Vec2);
    
    static float DotProduct3D(const FVector& Vec1, const FVector& Vec2);
    
    static float CrossProduct2D(const FVector2D& Vec1, const FVector2D& Vec2);
    
    static FVector CrossProduct3D(const FVector& Vec1, const FVector& Vec2);

    static FVector2D MirrorByNormal(const FVector2D& Vec, const FVector2D& Normal);
    
    static FVector MirrorByNormal(const FVector& Vec, const FVector& Normal);
};

