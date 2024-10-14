#include <random>
#include <iostream>
#include <random>
using namespace std;

int main() {
  // 生成 [-1, 1] 范围随机浮点数
  // 模板参数只能是浮点类型（float/double/long double）
  uniform_real_distribution<double> u(8, 10);
  default_random_engine e(time(NULL));

	for (size_t i = 0; i < 10; ++i) {
		cout << u(e) << " ";
	}
	cout << endl;
	return 0;
}

