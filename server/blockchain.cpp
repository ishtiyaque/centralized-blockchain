#include "blockchain.h"

Block::Block(Clientid s, Clientid r, double a) {
	sndr = s;
	rcvr = r;
	amount = a;
	prev = next = 0;
}

bool Blockchain::append(Block *blk) {
	if(!head) {
		head = tail = blk;
	}else {
		blk->prev = tail;
		tail->next = blk;
		tail = blk;
	}
	return true;
}

double Blockchain::get_balance(Clientid id) {
	return 10.0;
}

bool Blockchain::make_transaction(Clientid sndr, Clientid rcvr, double amount) {
	if(get_balance(sndr) < amount)
		return false;
	Block *blk = new Block(sndr, rcvr, amount);
	return append(blk);
}

void Blockchain::print() {
	for(Block *tmp = head;tmp;tmp = tmp->next)
		printf("%d %d %lf\n",tmp->get_sndr(), tmp->get_rcvr(), tmp->get_amount());
}


int main() {
	Blockchain chain;
	chain.make_transaction(1,2,0.5);
	chain.make_transaction(2,3,0.6);
	chain.make_transaction(3,4,0.8);
	chain.print();
	return 0;
}