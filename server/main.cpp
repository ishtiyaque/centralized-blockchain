#include "blockchain.h"

int main() {
	Blockchain chain;
	chain.make_transaction(1,2,0.5);
	chain.make_transaction(2,3,0.6);
	chain.make_transaction(3,4,0.8);
	chain.print();
	return 0;
}