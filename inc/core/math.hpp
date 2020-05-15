// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_MATH_
#define _THIS_MATH_


/*!
 *  \namespace TMath
 *  \brief  collection of useful math functions
 *  \note   these are all C-Style functions
 *  \todo   document functions and values
 */
namespace TMath
{

constexpr const float PI = 3.14159265359;

template<typename T, typename U>
T constexpr pow(T base, U exponent)
{
    static_assert(std::is_integral<U>(), "exponent must be integral");
    return exponent == 0 ? 1 : base * pow<T,U>(base, exponent - 1);
}

template<typename T>

constexpr float arctan(T x)
{
    // M.Abramowitz, I.A.Stegun, "Handbook of Mathematical Functions", formule 4.4.47, p.81, Dover Publications, N.-Y., 1972
    // precision is 10^-5 so 0.00001. not so great but "sufficient"
    const T c1 =  0.9998660f;
    const T c2 = -0.3302995f;
    const T c3 =  0.1801410f;
    const T c4 = -0.0851330f;
    const T c5 =  0.0208351f;

    if(x>=-1 && x<=1)
    {
        return \
        c1 * x + \
        c2 * pow(x,3) + \
        c3 * pow(x,5) + \
        c4 * pow(x,7) + \
        c5 * pow(x,9);
    }
    else if(x <-1)
    {
        return PI/2.f -\
        c1 * x + \
        c2 * pow(1/x,3) + \
        c3 * pow(1/x,5) + \
        c4 * pow(1/x,7) + \
        c5 * pow(1/x,9);
    }
    else //  if(x > 1)
    {
        return -PI/2.f -\
        c1 * x + \
        c2 * pow(1/x,3) + \
        c3 * pow(1/x,5) + \
        c4 * pow(1/x,7) + \
        c5 * pow(1/x,9);
    }
    
}


};

#endif // _THIS_MATH_
