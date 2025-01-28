#include <iostream>
#include "WindowsLogger.h"

using namespace PlatformDependent::Windows;
using namespace std;

void WindowsLogger::d(const string& tag, const string& msg)
{
    cout << tag << ": " << msg << endl;
}

void WindowsLogger::w(const string& tag, const string& msg)
{
    cout << tag << ": " << msg << endl;
}

void WindowsLogger::e(const string& tag, const string& msg)
{
    cout << tag << ": " << msg << endl;
}

void WindowsLogger::e(const string& tag, const string& msg, const exception& e)
{
    cout << tag << ": " << e.what() << "; " << msg << endl;
}
