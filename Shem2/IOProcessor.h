#pragma once

#include <iostream>
#include <cmath>
#include <string>

#include "Geometry.h"

struct DelimiterIO
{
    char exp;
};

struct PointIO
{
    Point& ref;
};

struct StringIO
{
    std::string& ref;
};

struct IntIO
{
    int& num;
};

struct LabelIO
{
    std::string exp;
};

class ScopeGuard
{
public:
    ScopeGuard(std::basic_ios< char >& s);
    ~ScopeGuard();
private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, IntIO&& dest);

std::istream& operator>>(std::istream& in, Point& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

//std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
