#include <iostream>
#include <tuple>

using namespace std;

constexpr int gcd(int x, int y) {
	if (!y) return x;
	return gcd(y, x%y);
}

constexpr int ext_gcd1(int x, int y, int * const a, int * const b) {
	if (!y) {
		*a = 1;
		*b = 0;
		return x;
	}
	int a1 = 0, b1 = 0;
    int gcd = ext_gcd1(y, x%y, &a1, &b1);
    *a = b1;
    *b = a1 - (x/y) * b1;
	return gcd;
}

constexpr tuple<int, int, int> ext_gcd2(int x, int y) {
	int a = 1;
	int b = 0;
	if (!y) {
		return make_tuple(x, a, b);
	}
    tuple<int, int, int> gcd = ext_gcd2(y, x%y);
    a = get<2>(gcd);
    b = get<1>(gcd) - (x/y) * a;
	return make_tuple(get<0>(gcd), a, b);
}

int main() {
	std::cout << std::is_scalar<int>::value << '\n';
	cout << "gcd(765, 500) = " << gcd(765, 500) << endl;
	static_assert(5 == gcd(765, 500), "gcd(765, 500) should be 5");

	int a = 0;
	int b = 0;
	//constexpr auto res1 = ext_gcd1(765, 500, &a, &b); // error
	constexpr auto res = ext_gcd2(765, 500);
	cout << get<0>(res) << endl;
	static_assert(5 == get<0>(res), "");
	static_assert(17 == get<1>(res), "");
	static_assert(-26 == get<2>(res), "");
	return 0;
}
