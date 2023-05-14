#include "IOProcessor.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    // все перегрузки операторов ввода/вывода должны начинатьс€ с проверки экземпл€ра класса sentry
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}


std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

// (0,0)
std::istream& operator>>(std::istream& in, Point& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Point input;
    {
        using sep = DelimiterIO;
        using num = IntIO;

        in >> sep{ '(' };
        in >> num{ input.x };
        in >> sep{ ',' };
        in >> num{ input.y };
        in >> sep{ ')' };
    }
    if (in)
    {
        dest = input;
    }
    return in;
}

// 5 (0,0) (0,1) (1,1) (1,0) (2,0)
std::istream& operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Polygon tmp;

    std::string inputString = "";
    std::getline(in, inputString);
    std::istringstream ss(inputString);

    size_t vertexCount = 0;
    ss >> vertexCount;

    std::copy(
        std::istream_iterator<Point>(ss),
        std::istream_iterator<Point>(),
        tmp.points
    );

    if (in && tmp.points.size() == vertexCount)
    {
        dest = tmp;
    }
    return in;
}

std::istream& operator>>(std::istream& in, IntIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> dest.num;
}

ScopeGuard::ScopeGuard(std::basic_ios< char >& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{}

ScopeGuard::~ScopeGuard()
{
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
}