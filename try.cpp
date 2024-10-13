#include <iostream>
#include <vector>
#include <stdexcept>  // 包含 std::logic_error

// 创建一个简单的二维矩阵类
class Matrix {
public:
    Matrix(size_t rows, size_t cols) {
        if (rows == 0 || cols == 0) {
            throw std::logic_error("wrong col or row\n");
        }
        data.resize(rows, std::vector<int>(cols, 0));
    }

    // 用于展示矩阵
    void show() const {
        for (const auto& row : data) {
            for (const auto& val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<std::vector<int>> data;
};

int main() {
    try {
        // 创建一个3x3的矩阵，应该成功
        Matrix mat1(3, 3);
        std::cout << "3x3 Matrix created successfully:\n";
        mat1.show();

        // 尝试创建一个 0x5 的矩阵，应该触发异常
        Matrix mat2(0, 5);
        std::cout << "This line will not be printed because an exception is thrown\n";
    }
    catch (const std::logic_error& e) {
        // 捕获并处理逻辑错误异常
        std::cerr << "Caught an exception: " << e.what();
    }

    return 0;
}
