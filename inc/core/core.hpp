// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_core_
#define _this_core_

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

// we could use reflection to serialize types easily
//#include <experimental/reflect>

/**
 *  TArchive
 *  @brief      Class allowing to serialize and safe data
 *  @todo       Add reflexion to free subclasses from implementing serialise
 */
class TArchive
{
protected:

private:

    //friend class boost::serialization::access;

    /**
     *  serialize
     *  @brief      function to serialize the data contained in this class 
     *  @note       When the class Archive corresponds to an output archive, the
     *              & operator is defined similar to <<.  Likewise, when the class Archive
     *              is a type of input archive the & operator is defined similar to >>.
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        // ar & data;
    }

};

/**
 *  TString
 *  @brief      String type for __This__
 */
class TString : public TArchive
{
private:
    std::string store;

public:

    TString(char * chars) : store(chars) {}         /** TString @brief from char        */
    TString(const char * chars) : store(chars)  {}  /** TString @brief from const char  */
    TString(std::string string) : store(string) {}  /** TString @brief from string      */

    operator std::string() {return store;}          /** TString @brief to string        */
    operator const char*() {return store.c_str();}  /** TString @brief to char          */

    size_t length() {return store.length();}        /** lenght @brief length of text        */
    const char* c() {return store.c_str();}         /** c      @brief text as C char array  */


};


/**
 *  TVec3
 *  @brief      3d vector type
 */
struct TVec3 : public glm::vec3, TArchive
{
    TVec3(float x, float y, float z) : glm::vec3( x, y, z) {}  /** TVec3 @brief coord constructor */
    TVec3(glm::vec3 v) : glm::vec3(v) {}                       /** TVec3 @brief copy from glm constructor */
};

/**
 *  TVec2
 *  @brief      2d vector type
 */
struct TVec2 : public glm::vec2, TArchive
{
    inline float u() {return x;}
    inline float v() {return y;}
};


/**
 *  TColor
 *  @brief color in linear RGBA
 *  @todo  hsl / rgb / hdr conversions
 */
struct TColor : public glm::vec4, TArchive
{
    inline float r() {return x;}
    inline float g() {return y;}
    inline float b() {return z;}
    inline float a() {return w;}
};

/**
 *  TMat4
 *  @brief    4x4 matrix
 */
struct TMat4 : public glm::mat4x4, TArchive
{

    TMat4() = default;                                           /** TMat4 @brief default constructor */
    TMat4(glm::mat4x4 glm_matrix) : glm::mat4x4(glm_matrix) {};  /** TMat4 @brief copy from glm constructor */

    /**
     *  value_ptr
     *  @brief      get a pointer to pass to openGL/Vulkan/Whatever
     */
    float* value_ptr() {return glm::value_ptr<float>(*this);}

    /**
     *  Identity
     *  @brief     construct an identity matrix
     */
    static inline TMat4 identity() {return TMat4(glm::mat4x4(1.f));}


    /**
     *  perspective
     *  @brief     construct a perspective matrix
     *  @param     fov      field of view , 60 is normal human vision
     *  @param     width    width of your rendering surface
     *  @param     height   height of your rendering surface
     *  @param     near     front clipping plane
     *  @param     far      distant clipping plane
     */
    static inline TMat4 perspective(float fov, float width, float height, float near, float far)
    {
        return TMat4(glm::perspective(fov, width /height, near, far));
    }

    /**
     *  rotate
     *  @brief     rotate matrix
     *  @param     axis     axis of rotation
     *  @param     angle    angle in degrees
     */
    void rotate(TVec3 axis, float deg_angle)
    {
        glm::rotate(*this, deg_angle, glm::vec3(axis));
    }



};

/**
 *  TMat4
 *  @brief    4x4 matrix
 */
struct TRenderMatrices : public TArchive
{
    /**
     *  MVP
     *  @brief    Model View Projection matrix
     */
    TMat4 MVP;

    /**
     *  Model
     *  @brief    Model matrix
     */
    TMat4 Model;


    /**
     *  View
     *  @brief    View matrix
     */
    TMat4 View;
};

#endif // _this_core_