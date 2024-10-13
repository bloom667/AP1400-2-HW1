#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
namespace algebra{
    using Matrix = std::vector<std::vector<double>>;
    Matrix zeros(std::size_t n, std::size_t m);
    Matrix ones(std::size_t n, std::size_t m);
}


#endif //AP_HW1_H
