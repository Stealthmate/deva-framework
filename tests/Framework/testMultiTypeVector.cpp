#include <DevaFramework\Util\MultiTypeVector.hpp>
#include <iostream>
using namespace std;
using namespace DevaFramework;

int main() {
	MultiTypeVector<float, float, float, float> mtv;
	mtv.push_back({0.1f, 0.1f, 0.1f, 1.f});
	auto tuple = mtv[0];
}