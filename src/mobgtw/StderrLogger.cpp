#include "StderrLogger.h"

#include <iostream>

namespace mobcli::mobgtw {

void StderrLogger::error(const std::string& message)
{
    std::cerr << message << std::endl;
}

}
