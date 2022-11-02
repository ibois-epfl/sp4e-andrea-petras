#pragma once
#include "series.hh"

namespace SCPP
{
    class ComputeArithmetic: public Series
    {
    public:
        ComputeArithmetic() = default;

        double compute(unsigned int N) override;
    };
}


