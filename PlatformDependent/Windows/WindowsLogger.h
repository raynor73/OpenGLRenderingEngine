#pragma once

#include <Logger.h>

namespace PlatformDependent
{
namespace Windows 
{
class WindowsLogger : public Logger
{
public:
    virtual void d(const std::string& tag, const std::string& msg) override;
    virtual void w(const std::string& tag, const std::string& msg) override;
    virtual void e(const std::string& tag, const std::string& msg) override;
    virtual void e(const std::string& tag, const std::string& msg, const std::exception& e) override;
};
}
}
