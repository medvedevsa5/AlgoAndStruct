#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

#include "DataStruct.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    // все перегрузки операторов ввода/вывода должны начинаться с проверки экземпл¤ра класса sentry
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

std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    unsigned long long tmp = 0;

    ScopeGuard scopeGuard(in);

    in >> std::oct >> tmp;

    if (!in)
    {}
    else if (std::isdigit(in.peek()))
    {
        in.setstate(std::ios::failbit);
    }
    else
    {
        dest.ref = tmp;
    }

    return in;
}

std::istream& operator>>(std::istream& in, ComplexIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{ '#' };
    in >> DelimiterIO{ 'c' };
    in >> DelimiterIO{ '(' };

    double real = 0;
    double imaginary = 0;

    in >> real;
    in >> imaginary;

    dest.ref = std::complex<double>(real, imaginary);

    in >> DelimiterIO{ ')' };

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


// формат ввода:
// (:key1 1321321314:key2 #c(1.0 -1.0):key3 \"data\":)

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
    std::istream::sentry sentry(in);

    if (!sentry)
    {
        return in;
    }

    DataStruct input;
    {
        using sep = DelimiterIO;
        using ull = UnsignedLongLongIO;
        using cmplx = ComplexIO;
        using str = StringIO;

        bool isWritten[3]{};

        const int FIRST_KEY = 0;
        const int SECOND_KEY = 1;
        const int THIRD_KEY = 2;

        in >> sep{ '(' };
        in >> sep{ ':' };

        for (size_t i = 0; i < 3; i++)
        {
            std::string currentLabel = "";
            in >> currentLabel;

            if (currentLabel == "key1" && !isWritten[FIRST_KEY])
            {
                in >> ull{ input.key1 };
                isWritten[FIRST_KEY] = true;
            }
            else if (currentLabel == "key2" && !isWritten[SECOND_KEY])
            {
                in >> cmplx{ input.key2 };
                isWritten[SECOND_KEY] = true;
            }
            else if (currentLabel == "key3" && !isWritten[THIRD_KEY])
            {
                in >> str{ input.key3 };
                isWritten[THIRD_KEY] = true;
            }
            else
            {
                in.setstate(std::ios::failbit);
                break;
            }

            in >> sep{ ':' };
        }

        in >> sep{ ')' };
    }

    if (in)
    {
        dest = input;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
    std::ostream::sentry sentry(out);

    if (!sentry)
    {
        return out;
    }

    ScopeGuard scopeGuard(out);

    out << "(:";

    out << "key1 " << std::oct << src.key1 << ':';

    out << std::fixed << std::setprecision(1)
        << "key2 #c("
        << src.key2.real() << " " << src.key2.imag()
        << ")" << ":";

    out << "key3 " << '\"' << src.key3 << '\"';

    out << ":)";

    return out;
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

#undef COMPARISON_ACCURACY