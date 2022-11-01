#pragma once
#include "series.hh"

namespace SCPP
{
    class DumperSeries
    {
    public:
        DumperSeries(Series& series)
            : p_Series(series)
        {};
        ~DumperSeries() = default;

        virtual void dump() = 0;

    protected:
        Series& p_Series;
    };
}