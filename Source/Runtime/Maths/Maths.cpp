#include "Maths.h"

bool AMathsUtils::IsNearlyEqual(const FVector2D& Vec1, const FVector2D& Vec2, float Tolerance) {
    return AMathsUtils::IsNearlyEqual(Vec1.X, Vec2.X, Tolerance) && AMathsUtils::IsNearlyEqual(Vec1.Y, Vec2.Y, Tolerance);
}

bool AMathsUtils::IsNearlyEqual(float Number1, float Number2, float Tolerance) {
    return (Number1 - Number2) < Tolerance ;
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
