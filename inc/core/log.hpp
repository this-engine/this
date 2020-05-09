// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef _this_log_
#define _this_log_

#include <string>
#include <memory>
#include "core.hpp"

/**
 *  TLogTypes
 *  @brief      types of message sent to log
 */
enum class TLogTypes
{
    Error   /* Error message, something went wrong, sent to stderr        */,
    Debug   /* Debug message, should not be displayed in release (stdout) */,
    Display /* Display message, will be printed to stdout                 */
};

/**
 *  TLog
 *  @brief     class of a log writing class
 */
class TLog
{

public:
  

    /**
     *  log()
     *  @brief      write text to the log (char* variant)
     *  @param      type    type of log @see TLogTypes
     *  @param      text    actual text
     *  @param      length  number of character
     */
    static void log( TLogTypes type, const char* text, size_t length);

    /**
     *  log()
     *  @brief      write text to the log (TSring variant)
     *  @param      type    type of log @see TLogTypes
     *  @param      text    actual text
     */
    static void log(TLogTypes type, const TString &text);
#if 0
    /**
     *  log()
     *  @brief      write text to the log (std string variant)
     *  @param      type    type of log @see TLogTypes
     *  @param      text    actual text
     */
    static void log( TLogTypes type, const std::string &text);
#endif

};

#endif // _this_log_