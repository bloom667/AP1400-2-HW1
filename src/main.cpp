
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

std::ostream& operator<<(std::ostream& os, const algebra::Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        algebra::Matrix a = algebra::random(2, 2, 2.34, 4.56);
        algebra::show(a);
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}