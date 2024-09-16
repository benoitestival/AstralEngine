#pragma once
#include "../../../Utils/Array.h"


enum class EKey{
    INVALID = -1,
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8,
    J = 9,
    K = 10,
    L = 11,
    M = 12,
    N = 13,
    O = 14,
    P = 15,
    Q = 16,
    R = 17,
    S = 18,
    T = 19,
    U = 20,
    V = 21,
    W = 22,
    X = 23,
    Y = 24,
    Z = 25,
    SPACE = 26,
    ESCAPE = 27,
    LCTRL = 28,
    RCTRL = 29,
    LSHIFT = 30,
    RSHIFT = 31,
    LALT = 32,
    RALT = 33,
    NUMBER0 = 34,
    NUMBER1 = 35,
    NUMBER2 = 36,
    NUMBER3 = 37,
    NUMBER4 = 38,
    NUMBER5 = 39,
    NUMBER6 = 40,
    NUMBER7 = 41,
    NUMBER8 = 42,
    NUMBER9 = 43,
    TAB = 44,
    ENTER = 45,
    BACKSPACE = 46,
    ARROWUP = 47,
    ARROWDOWN = 48,
    ARROWRIGHT = 49,
    ARROWLEFT = 50,
    
    MOUSEBUTTONLEFT = 51,
    MOUSEBUTTONRIGHT = 52,
    MOUSEBUTTONMIDDLE = 53,
};


enum EInputState {
    Pressed = 0,
    Released = 1,
};



enum EInputValueType {
    EInputBool = 0,
    EInputAxis1D = 0,
};
struct FInputValue {
public:

    FInputValue();
    FInputValue(EInputValueType DesiredType, EInputState InputState);
    
    EInputValueType ActualType;
    union {
        bool InputBool;
        float InputFloat;
    };
   
};


class InputUtils {
public:
    static TArray<EKey> GetKeys();
private:
    static TArray<EKey> Keys;
};
