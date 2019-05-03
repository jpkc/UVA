// jpkc's solution for UVA problem 10710 - Chinese Shuffle

// The idea:
//				1: If one card returns to its original position, all cards do.
//				2: N cards even numbered decks behave as odd numbered N-1 decks creted by removing the first card from the original deck.
//				3: The position p of a card in a deck with odd size s after shuffeling is (2*p + 1) % s.
//				4: If after s-2 shuffles of a s sized deck all cards are back in place s is a Jimmy number.
//				5: Modular algebra predicts this easily. The cicle count is n where n is the prime modulus number. a*b*c will cicle in a modulus a*b*n after n shuffles. each card will jump c positions to the right.
//			In this problem our modulus is (2*n+1) and our stride is the deck size n. The (even numbered) deck will sort out after n perfect shuffles if n is a divisor of 2*n + 1

#include <iostream>
#define VERBOSE 0	//For my algebra debug output.

using namespace std;

int shuffle_reset(int size)
{
	if(size % 2 == 0) {
		return shuffle_reset(size-1);
	}

	int n = 0, shuffle_count = 0;	//Here we follow the card at position 0. It's new position is given by (2*n + 1) % size. We are talking about od decks only. Even decks were ruled out earlier
	do {
		n = (2*n + 1) % size;
		++shuffle_count;
	} while (n != 0);	//ToDo: Replace this iteration by modulus algebra math (modulus, prime number and rings) so that ir runs faster.
	return shuffle_count;
}

int main(int, char **)
{
	int size, shuffles;

	for(cin >> size; size != -1; cin >> size) {
		shuffles = shuffle_reset(size);
		if(VERBOSE && size > 0) {	//This is my algebra debug output. :-)
			cout << "Deck Size n = " << size << ", 2*n + 1 = " << 2*size + 1 << ", (2*n + 1) % n = " << (2*size + 1)%size << ", ";
		}
		if(shuffles + 1 == size) {
			cout << size << " is a Jimmy-number" << endl;
		}
		else {
			cout << size << " is not a Jimmy-number" << endl;
		}
	}

	return 0;
}
