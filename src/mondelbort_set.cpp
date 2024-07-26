#include <mondelbort_set.hpp>

std::complex<double> mondelbort::Calculater::CalculateValue(std::complex<double> point, int recursive_step) {
    std::complex<double> z = {0, 0};
    while (recursive_step--) {
        z = z * z + point;
    }
    return z;
}

std::pair<bool, unsigned char> mondelbort::Calculater::IsSet(std::complex<double> point, int recursive_step) {
    std::complex<double> z = {0, 0};
    for (auto i = 0; i < recursive_step; i++) {
        z = z * z + point;
        if (std::abs(z) > 2)
            return {true, 255 - 15 * i};
    }
    return {true, 0};
}
