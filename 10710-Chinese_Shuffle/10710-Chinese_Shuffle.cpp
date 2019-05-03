// jpkc's solution for UVA problem 10710 - Chinese Shuffle

// The idea:
//				1: If one card returns to its original position, all cards do.
//				2: If after s-1 shuffles of a s sized deck all cards are back in place s is a Jimmy number.
//				3: Beware: if it gets sorted before s-1 shuffles it's not Jimmy number.
//				3: The position p of a card in a deck with odd size s after shuffeling is p1 = (2*p0 + 1) mod(s). For beauty purposes (modular math) start counting p at 0 so that a 15 card deck has pos range from 0 to 14.
//				4: The closed formula for position 0 after n sorts can be calculated from a series given by
//					4.1:	| P0 = 0
//							| Pn = 1 + 2 * P(n-1)
//					Recursevely replacing gives us Pn = 1 + 2 + 4 + 8 + 16 + ... + 2^n * Pn-n = sum(2^i)_{0}^{i-1}
//					4.2: Pn = sum(2^i)_{0}^{i-1} can be solved as a telescopic geometric progression sum. (system below)
//							Pn = 2^0 + 2^1 + 2^2 + ... + 2^(n-1)
//					  2 * Pn =       2^1 + 2^2 + ... + 2^(n-1) + 2^n
//												(all internal terms cancels out)
//				(2 * Pn) - Pn = 2^n - 1
//
//				Solving for Pn gives us Pn = 2^n - 1
//
//				Ok. So
//				1: if P(n-1) = 0 mod(n) and P(n/2) != 0 mod(n) we have a Jimmy number.
//				The caveat:
//
//			The caveat:
//				This is fast but we need to compute giant numbers. This solution Only works for n < 64 (we need to calculate 2^n without overflow)

#include <iostream>
#define VISUAL_FEEDBACK 0

using namespace std;

unsigned long int P(unsigned long int n) {
	switch(n) {
	case 0:
		return 0;
	case 1:
		return 1;
	default:
		return (1 << n) - 1;
	}
}

int main(int, char **)
{
	unsigned long int size, pn;

	for(cin >> size; ; cin >> size) {
		switch (size) {
		case -1:
			return 0;

		case 0:
			cout << size << " is not a Jimmy-number" << endl;
			break;

		case 1:
		case 2:
			cout << size << " is a Jimmy-number" << endl;
			break;

		default:
			if(VISUAL_FEEDBACK) {
				cout << size << ": P(size-1)%size = " << P(size-1)%size << ", P(size/2)%size = " << P(size/2)%size << endl;
			}
			if((P(size-1)%size == 0) && P(size/2)%size != 0) {
				cout << size << " is a Jimmy-number" << endl;
			}
			else {
				cout << size << " is not a Jimmy-number" << endl;
			}
			break;
		}
	}
	return 0;
}
