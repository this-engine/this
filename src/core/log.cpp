#include "log.hpp"
#include <iostream>


void TLog::log(TLogTypes type, const char* text, size_t length)
{
    std::string logstring(text, length);
    TLog::log(type,logstring) ;
}


void TLog::log(TLogTypes type, const TString &text)
{
    //TLog::log(type, (const std::string&)text);
    auto logstring = (const std::string&)text;

    switch (type)
    {
    case TLogTypes::Error:
        std::cerr << logstring << std::endl;
        break;
    case TLogTypes::Debug:
    [[fallthrough]];
    case TLogTypes::Display:
    [[fallthrough]];
    default:
        std::cout << logstring << std::endl;
        break;
    }
}
