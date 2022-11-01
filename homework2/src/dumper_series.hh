#pragma once
#include "series.hh"

namespace SCPP
{
    class DumperSeries
    {
    public:
        virtual void dump() = 0;

    protected:
        Series& p_Series;
    };
}