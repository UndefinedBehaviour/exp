#include <iostream>
#include <tuple>

using namespace std;

constexpr int gcd(int x, int y) {
	if (!y) return x;
	return gcd(y, x%y);
}

constexpr tuple<int, int, int> ext_gcd(int x, int y) {
	int a = 1;
	int b = 0;
	if (!y) {
		return make_tuple(x, a, b);
	}
    tuple<int, int, int> gcd = ext_gcd(y, x%y);
    a = get<2>(gcd);
    b = get<1>(gcd) - (x/y) * a;
	return make_tuple(get<0>(gcd), a, b);
}

int main() {
	cout << "gcd(765, 500) = " << gcd(765, 500) << endl;
	static_assert(5 == gcd(765, 500), "gcd(765, 500) should be 5");

	constexpr auto res = ext_gcd(765, 500);
	cout << get<0>(res) << endl;
	static_assert(5 == get<0>(res), "");
	static_assert(17 == get<1>(res), "");
	static_assert(-26 == get<2>(res), "");
	return 0;
}
