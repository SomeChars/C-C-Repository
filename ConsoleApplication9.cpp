#include "pch.h"
#include <iostream>

using namespace std;

int rekursiya(int n, int k) {
	if (n - k == 1 || k == 1) {
		return n;
	}
	return rekursiya(n - 1, k - 1) + rekursiya(n - 1, k);
}

int main()
{	
	int l, m = 0;
	cout << "Input basis and index" << endl;
	cin >> l >> m;
	cout << rekursiya(l, m);
}

