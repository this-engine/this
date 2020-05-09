// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_core_
#define _this_core_

#include <string>
#include <glm/glm.hpp>

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
class TVec3 : public glm::vec3, TArchive
{

};

/**
 *  TColor
 *  @brief color in linear RGBA
 *  @todo  hsl / rgb / hdr conversions
 */
class TColor : public glm::vec4, TArchive
{
public:
    inline float r() {return x;}
    inline float g() {return y;}
    inline float b() {return z;}
    inline float a() {return w;}
};

#endif // _this_core_