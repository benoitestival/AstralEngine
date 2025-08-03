#include "Maths.h"

bool AMathsUtils::IsNearlyEqual(float Number1, float Number2, float Tolerance) {
    return (Number1 - Number2) < Tolerance ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////VECTOR/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool AMathsUtils::IsNearlyEqual(const FVector2D& Vec1, const FVector2D& Vec2, float Tolerance) {
    return AMathsUtils::IsNearlyEqual(Vec1.X, Vec2.X, Tolerance) && AMathsUtils::IsNearlyEqual(Vec1.Y, Vec2.Y, Tolerance);
}


FVector2D AMathsUtils::Normalize(const FVector2D& Vec) {
    return Vec / Vec.Lenght();
}

FVector AMathsUtils::Normalize(const FVector& Vec) {
    return Vec / Vec.Lenght(); 
}

float AMathsUtils::DotProduct2D(const FVector2D& Vec1, const FVector2D& Vec2) {
    return Vec1.Dot(Vec2);
}

float AMathsUtils::DotProduct3D(const FVector& Vec1, const FVector& Vec2) {
    return Vec1.Dot(Vec2);
}

float AMathsUtils::CrossProduct2D(const FVector2D& Vec1, const FVector2D& Vec2) {
    return Vec1.Cross(Vec2);
}

FVector AMathsUtils::CrossProduct3D(const FVector& Vec1, const FVector& Vec2) {
    return Vec1.Cross(Vec2);
}

FVector2D AMathsUtils::MirrorByNormal(const FVector2D& Vec, const FVector2D& Normal) {
    return Vec - 2 * AMathsUtils::DotProduct2D(Vec, Normal) * Normal;
}

FVector AMathsUtils::MirrorByNormal(const FVector& Vec, const FVector& Normal) {
    return Vec - 2 * AMathsUtils::DotProduct3D(Vec, Normal) * Normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////MATRIX/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


FMatrix4X4 AMathsUtils::RotateMatrixAroundAxis(FMatrix4X4& Matrix, const FVector& Axis, float Angle) {
    FMatrix4X4 RodriguesMatrix = BuildRodriguesMatrixAroundAxis(Axis, Angle);
    return Matrix * RodriguesMatrix;
}

FMatrix4X4 AMathsUtils::BuildRodriguesMatrixAroundAxis(const FVector& Axis, float Angle) {
    //This function build the rodrigues matrix who is the equivalent of the rodrigues formula in a matrix form
    // v*cos(𝛉) + dot(u.v)*u*(1-cos(𝛉)) + cross(u, v)*sin(𝛉)  //We need to convert each of the three part to a matrix
    //  
    //---- v*cos(𝛉) [it impact directly the vector on each of it's coordinate so we can make it an identity matrix]
    //
    //---- dot(u.v)*u*(1-cos(𝛉)) [Here "dot(u.v)*u" can be convert to a matrix using tensorial product changing this part to "Tensorial(u*u) * v" that output the same operation but as a matrix
    //                            So now we have [Tensorial(u*u)] * v * (1-cos(𝛉)) that is a matrix to]
    //                                             Matrix Part
    //
    //---- cross(u, v)*sin(𝛉) [the cross product can be convert to anti symmetric matrix of the first vector multiply by the second vector that look like AntiSym(U) * V * sin(𝛉)
    //                         So now we have here to a matrix]

    //Now we just need to developp and factorise all those matrix that give us the following formula:

    const float CosAngle = FMath::CosDeg(Angle); 
    const float SinAngle = FMath::SinDeg(Angle); 

    FVector AxisNormalize = AMathsUtils::Normalize(Axis);
    FVector AxisCosCoef = (1.0f - CosAngle) * AxisNormalize;
    
    FMatrix4X4 RodriguesMatrix = FMatrix4X4();
    RodriguesMatrix[0][0] = CosAngle + AxisCosCoef.X * AxisNormalize.X;
    RodriguesMatrix[0][1] = AxisCosCoef.X * AxisNormalize.Y + SinAngle * AxisNormalize.Z;
    RodriguesMatrix[0][2] = AxisCosCoef.X * AxisNormalize.Z - SinAngle * AxisNormalize.Y;
    
    RodriguesMatrix[1][0] = AxisCosCoef.Y * AxisNormalize.X - SinAngle * AxisNormalize.Z;
    RodriguesMatrix[1][1] = CosAngle + AxisCosCoef.Y * AxisNormalize.Y;
    RodriguesMatrix[1][2] = AxisCosCoef.Y * AxisNormalize.Z + SinAngle * AxisNormalize.X;
    
    RodriguesMatrix[2][0] = AxisCosCoef.Z * AxisNormalize.X + SinAngle * AxisNormalize.Y;
    RodriguesMatrix[2][1] = AxisCosCoef.Z * AxisNormalize.Y - SinAngle * AxisNormalize.X;
    RodriguesMatrix[2][2] = CosAngle + AxisCosCoef.Z * AxisNormalize.Z;
    
    return RodriguesMatrix;
}
