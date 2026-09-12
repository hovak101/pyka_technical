#pragma once

class Filter {
    private:
        double alpha;
    public:
        explicit Filter(double);
        double correct(double);
};