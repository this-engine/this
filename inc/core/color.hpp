// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_color_
#define _this_color_

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 *  TColor
 *  @brief color in linear RGBA
 *  @todo  hsl / rgb / hdr conversions
 */
struct TColor : public glm::vec4, TArchive
{
    TColor() : glm::vec4() {}                                               /** TColor @brief default constructor */
    TColor(float x, float y, float z, float w) : glm::vec4( x, y, z, w) {}  /** TColor @brief coord constructor */
    TColor(glm::vec4 v) : glm::vec4(v) {}                                   /** TColor @brief copy from glm constructor */

    /** 
      * TColor 
      * @brief init list constructor 
      */
    TColor(std::initializer_list<float> coords)
    {
        const std::vector<float> v = coords;
        x = coords.size() >= 0 ? v[0] : 0.f; 
        y = coords.size() >= 1 ? v[1] : 0.f; 
        z = coords.size() >= 2 ? v[2] : 0.f; 
        w = coords.size() >= 3 ? v[3] : 0.f; 
    }  

    ~TColor(){} /** TColor @brief trivial destructor */

    constexpr inline float r() {return x;}         /** r() @brief red alias     */
    constexpr inline float g() {return y;}         /** g() @brief green alias   */
    constexpr inline float b() {return z;}         /** b() @brief blue alias    */
    constexpr inline float a() {return w;}         /** a() @brief alpha alias   */

    static const TColor rgba256(char red, char green, char blue, char alpha = 255) {return TColor(red/255.f, green/255.f, blue/255.f, alpha/255.f );}

    static const TColor Crimson;  
    static const TColor SlateBlue;
};

const TColor TColor::Crimson   = TColor::rgba256(220,20,60, 255);
const TColor TColor::SlateBlue = TColor::rgba256(106,90,205,255);

#endif //_this_color_