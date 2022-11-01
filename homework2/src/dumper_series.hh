#pragma once
#include "series.hh"
#include <ostream>
namespace SCPP
{
    class DumperSeries
    {
    public:
        DumperSeries(Series& series)
            : p_Series(series), p_Precision(4)
        {};
        ~DumperSeries() = default;

        virtual void dump(std::ostream& os) = 0;

        virtual void setPrecision(unsigned int precision) {p_Precision = precision; };

    protected:
        Series& p_Series;
        unsigned int p_Precision;
    };
}