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
	double bal = 0.0;
	for(Block *temp = tail; temp; temp = temp->prev) {
		if(temp->get_sndr() == id) {
			bal -= temp->get_amount();
		} else if(temp->get_rcvr() == id) {
			bal += temp->get_amount();
		}
	}
	return bal;
}

bool Blockchain::make_transaction(Clientid sndr, Clientid rcvr, double amount) {
	if(sndr && get_balance(sndr) < amount)
		return false;
	Block *blk = new Block(sndr, rcvr, amount);
	return append(blk);
}

void Blockchain::print() {
	for(Block *tmp = head;tmp;tmp = tmp->next)
		printf("%d %d %lf\n",tmp->get_sndr(), tmp->get_rcvr(), tmp->get_amount());
}
