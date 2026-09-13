#include "filter.h"

Filter::Filter(double alpha) : alpha{alpha}, historyLength(0) {

}

double Filter::correct(double currentState) {
    if (historyLength == 0) {
        ema = currentState;
    }
    else {
        ema = (1 - alpha) * currentState + alpha * ema;
    }

    historyLength++;
    return ema;
}