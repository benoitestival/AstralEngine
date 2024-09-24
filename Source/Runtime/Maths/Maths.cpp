#include "Maths.h"

bool AMathsUtils::IsNearlyEqual(const FVector2D& Vec1, const FVector2D& Vec2, float Tolerance) {
    return AMathsUtils::IsNearlyEqual(Vec1.X, Vec2.X, Tolerance) && AMathsUtils::IsNearlyEqual(Vec1.Y, Vec2.Y, Tolerance);
}

bool AMathsUtils::IsNearlyEqual(float Number1, float Number2, float Tolerance) {
    return (Number1 - Number2) < Tolerance ;
}
