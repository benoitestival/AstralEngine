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
DECLARE_CONCRETE_MATH_TYPE(FMatrixVector2D, TMatrix<float COMMA 1 COMMA 2>)
DECLARE_CONCRETE_MATH_TYPE(FMatrixVector3D, TMatrix<float COMMA 1 COMMA 2>)
DECLARE_CONCRETE_MATH_TYPE(FMatrixVector4D, TMatrix<float COMMA 1 COMMA 4>)

DECLARE_CONCRETE_MATH_TYPE(FMatrix2X2, TMatrix<float COMMA 2 COMMA 2>)
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

    static bool IsNearlyEqual(float Number1, float Number2, float Tolerance = 0.00001f);

    /////////////////////////////////Vector////////////////////////////////////////
    static FVector WorldForwardVector();
    static FVector WorldRightVector();
    static FVector WorldUpVector();
    
    static bool IsNearlyEqual(const FVector2D& Vec1, const FVector2D& Vec2, float Tolerance = 0.00001f);
    static FVector2D Normalize(const FVector2D& Vec);
    static FVector Normalize(const FVector& Vec);
    static float DotProduct2D(const FVector2D& Vec1, const FVector2D& Vec2);
    static float DotProduct3D(const FVector& Vec1, const FVector& Vec2);
    static float CrossProduct2D(const FVector2D& Vec1, const FVector2D& Vec2);
    static FVector CrossProduct3D(const FVector& Vec1, const FVector& Vec2);
    static FVector2D MirrorByNormal(const FVector2D& Vec, const FVector2D& Normal);
    static FVector MirrorByNormal(const FVector& Vec, const FVector& Normal);

    /////////////////////////////////Rotator///////////////////////////////////////
    static FRotator MakeRotFromForwardVector(const FVector& Start, const FVector& End);
    static FRotator MakeRotFromRightVector(const FVector& Start, const FVector& End);
    static FRotator MakeRotFromUpVector(const FVector& Start, const FVector& End);

    inline static FRotator FindLookAtRotation(const FVector& Start, const FVector& End);//Just an another name for Find by forward vector
    
    /////////////////////////////////Matrix////////////////////////////////////////
    //Use to rotate an existing transformation matrix around an axis
    FMatrix4X4 RotateMatrixAroundAxis(FMatrix4X4& Matrix, const FVector& Axis, float Angle);
    FMatrix4X4 BuildRodriguesMatrixAroundAxis(const FVector& Axis, float Angle);
    //Return a transformation matrix for the LookAtDirection 
    FMatrix4X4 FindLookAtMatrixFromForward(const FVector& Start, const FVector& End);//From Z
    FMatrix4X4 FindLookAtMatrixFromRight(const FVector& Start, const FVector& End);//From X
    FMatrix4X4 FindLookAtMatrixFromUp(const FVector& Start, const FVector& End);//From Y
    FMatrix4X4 ConstructRotationMatrix(const FVector& Forward, const FVector& Right, const FVector& Up);//All Vectors must be normalized
    //Return the Camera transformation matrix for the LookAtDirection
    FMatrix4X4 FindCameraLookAtMatrix(const FVector& CameraPos, const FVector& LookAtPosition);
    //Return Vulkan perspective matrix
};

