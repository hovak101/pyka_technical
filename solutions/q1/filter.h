#pragma once

class Filter {
    private:
        double alpha;
        double ema;
        double historyLength;
    public:
        explicit Filter(double);
        double correct(double);
};