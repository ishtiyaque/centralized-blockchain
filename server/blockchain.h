#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include<stdio.h>
#include "utils.h"

class Block {
	Clientid sndr;
	Clientid rcvr;
	double amount;
	
public:
	Block *prev, *next;
	Block(Clientid s, Clientid r, double a);
	Clientid get_sndr(){return sndr;}
	Clientid get_rcvr(){return rcvr;}
	double get_amount(){return amount;}

};

class Blockchain {
	Block *head, *tail;
	bool append(Block * blk);
public:
	Blockchain(){head = tail = 0;}
	double get_balance(Clientid id);
	bool make_transaction(Clientid sndr, Clientid rcvr, double amount);
	
	void print();
	
};

#endif