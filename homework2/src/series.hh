#pragma once

namespace SCPP
{
    class Series
    {
    public:
        virtual double compute(unsigned int N) = 0;
    };
}
