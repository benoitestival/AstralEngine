#pragma once
#include "Vector2D.h"

#define DECLARE_CONCRETE_MATH_TYPE(ConcreteName, GenericType)\
    using ConcreteName = GenericType;


//Vector 2D
DECLARE_CONCRETE_MATH_TYPE(FVector2D, TVector2D<float>)
DECLARE_CONCRETE_MATH_TYPE(FIntVector2D, TVector2D<int>)
