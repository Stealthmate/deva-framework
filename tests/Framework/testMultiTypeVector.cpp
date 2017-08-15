#include <DevaFramework\Util\MultiTypeVector.hpp>
#include <iostream>
#include <DevaFramework\Core\Serializable.hpp>
#include <DevaFramework\Core\Exceptions.hpp>
using namespace std;
using namespace DevaFramework;

int main() {

	/*MultiTypeVector<Pack<int, double>, Packsize_v<int, double>> abcs;
	abcs.push_back({1, 2.2});
	abcs.push_back({ 2, 3.3 });
	auto a = abcs[1];
	cout << std::get<0>(a) << " " << std::get<1>(a) << endl;*/

	PackedVector<int, double> packv;
	packv.push_back({ 1, 2.2 });
	packv.push_back({ 2, 2.3 });
	auto p = packv[1];
	cout << std::get<0>(p) << std::get<1>(p) << endl;

}