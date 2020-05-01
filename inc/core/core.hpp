// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#pragma once

#include <string>


/**
 *  TString
 *  @brief      String type for __This__
 */
class TString
{
private:
    std::string store;

public:

    TString(char * chars) : store(chars) {}         /** TString @brief from char   */
    TString(std::string string) : store(string) {}  /** TString @brief from string */

    operator std::string() {return store;}          /** TString @brief to string   */
    operator const char*() {return store.c_str();}  /** TString @brief to char     */

};
