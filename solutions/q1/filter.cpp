#include "filter.h"

Filter::Filter(double alpha) : alpha{alpha} {

}

double Filter::correct(double current_state) {
    return current_state;
}