#ifndef _MONDELBORT_SET_H
#define _MONDELBORT_SET_H

#include <complex>

namespace mondelbort {
class Calculater {
public:
    std::complex<double> CalculateValue(std::complex<double> point, int recursive_step = 1024);
    std::pair<bool, unsigned char> IsSet(std::complex<double> point, int recursive_step = 1024);

private:
};
}  // namespace mondelbort

#endif  // _MONDELBORT_SET_H
