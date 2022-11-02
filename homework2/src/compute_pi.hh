#pragma once
#include "series.hh"

namespace SCPP
{
    class ComputePi: public Series
    {
    public:
        ComputePi() = default;

        double compute(unsigned int N) override;
        double getAnalyticPrediction() override;
    };
}