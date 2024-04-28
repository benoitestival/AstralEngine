#pragma once
#include "Matrix.h"
#include "Vector2D.h"

#define COMMA ,

#define DECLARE_CONCRETE_MATH_TYPE(ConcreteName, GenericType)\
    using ConcreteName = GenericType;


//Vector 2D
DECLARE_CONCRETE_MATH_TYPE(FVector2D, TVector2D<float>)
DECLARE_CONCRETE_MATH_TYPE(FIntVector2D, TVector2D<int>)

//Matrix
DECLARE_CONCRETE_MATH_TYPE(FMatrix3X3, TMatrix<float COMMA 3 COMMA 3>)
DECLARE_CONCRETE_MATH_TYPE(FMatrix4X4, TMatrix<float COMMA 4 COMMA 4>)
