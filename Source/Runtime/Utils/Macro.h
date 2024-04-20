#pragma once
#include <type_traits>

/**
 * Concatenation Macro
 */
#define CONCAT(Args1, Args2)\
    Args1##Args2


/**
 * Macro for detecting the number of arguments in _VA_ARG_
 */
#define VA_NARGS(...) VA_NARGS_CONCAT(__VA_ARGS__,R_SEQ()) //Concat the number of parameters with a sequence of reel number -> Param1,Param2,16,15,...
#define VA_NARGS_CONCAT(...) VA_NARGS_SOLVER(__VA_ARGS__) // Call the solver who will substract Params in _VA_ARGS_ automatically so N equal the number in R_SEQ that doesnt fit in the call
#define VA_NARGS_SOLVER(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N //Output the number of params as N
#define R_SEQ() 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
////////////////////////////////////////////////////////////////////////////////////


/**
 * Macro who execute a block of code for each elements in _VA_ARG_ (limit of 16 elements)
 */
#define FOR_EACH_O(Code)
#define FOR_EACH_1(Code, x, ...)\
    Code(x)
#define FOR_EACH_2(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_1(Code,  __VA_ARGS__);
#define FOR_EACH_3(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_2(Code, __VA_ARGS__);
#define FOR_EACH_4(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_3(Code,  __VA_ARGS__);
#define FOR_EACH_5(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_4(Code,  __VA_ARGS__);
#define FOR_EACH_6(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_5(Code,  __VA_ARGS__);
#define FOR_EACH_7(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_6(Code,  __VA_ARGS__);
#define FOR_EACH_8(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_7(Code,  __VA_ARGS__);
#define FOR_EACH_9(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_8(Code,  __VA_ARGS__);
#define FOR_EACH_10(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_9(Code, __VA_ARGS__);
#define FOR_EACH_11(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_10(Code,  __VA_ARGS__);
#define FOR_EACH_12(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_11(Code,  __VA_ARGS__);
#define FOR_EACH_13(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_12(Code,  __VA_ARGS__);
#define FOR_EACH_14(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_13(Code,  __VA_ARGS__);
#define FOR_EACH_15(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_14(Code,  __VA_ARGS__);
#define FOR_EACH_16(Code, x, ...)\
    ,Code(x)\
    FOR_EACH_15(Code  __VA_ARGS__);


#define GET_APPROPRIATE_FOR_EACH(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,FOR_EACH_NAME,...) FOR_EACH_NAME 

#define VA_ARGS_CODE_EXECUTE(CodeBlock, ...)\
    GET_APPROPRIATE_FOR_EACH(_0,__VA_ARGS__,FOR_EACH_16,FOR_EACH_15,FOR_EACH_14,FOR_EACH_13,FOR_EACH_12,FOR_EACH_11,FOR_EACH_10,FOR_EACH_9,FOR_EACH_8,FOR_EACH_7,FOR_EACH_6,FOR_EACH_5,FOR_EACH_4,FOR_EACH_3,FOR_EACH_2,FOR_EACH_1,FOR_EACH_O)(CodeBlock, __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define IS_POINTER(Variable)\
    //std::is_pointer<Variable>

