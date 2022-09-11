#include <iostream>
#include <ctime>
#include <list>
using namespace std;

class AbstractCard {
public:
	virtual void show()=0;
	virtual ~AbstractCard() {
	}
};

class Card: public AbstractCard {
	int type;
public:
	Card(int type) :
			type(type) {
	}
	void show() override {
		if (type == 1)
			cout << "Ace";
		else if (type == 11)
			cout << "Jack";
		else if (type == 12)
			cout << "Queen";
		else if (type == 13)
			cout << "King";
		else
			cout << this->type;
	}
};

class CardSuit: public AbstractCard {
protected:
	Card *card;
public:
	CardSuit(Card *card) {
		this->card = card;
	}
	virtual void show()=0;
	virtual ~CardSuit() {
	}
};

class Hearts: public CardSuit {
	Hearts(Card *card) :
			CardSuit(card) {
	}
	void show() override {
		this->card->show();
		cout << " of Hearts";
	}
	friend class HeartsFactory;
};

class Diamonds: public CardSuit {
	Diamonds(Card *card) :
			CardSuit(card) {
	}
	void show() override {
		this->card->show();
		cout << " of Diamonds";
	}
	friend class DiamondsFactory;
};

class Clubs: public CardSuit {
	Clubs(Card *card) :
			CardSuit(card) {
	}
	void show() override {
		this->card->show();
		cout << " of Clubs";
	}
	friend class ClubsFactory;
};

class Spades: public CardSuit {
	Spades(Card *card) :
			CardSuit(card) {
	}
	void show() override {
		this->card->show();
		cout << " of Spades";
	}
	friend class SpadesFactory;
};

class AbstractCardFactory {
public:
	virtual AbstractCard* makeCard(int type)=0;
	virtual ~AbstractCardFactory() {
	}
};

class HeartsFactory: public AbstractCardFactory {
public:
	AbstractCard* makeCard(int type) {
		return new Hearts(new Card(type));
	}
};

class DiamondsFactory: public AbstractCardFactory {
public:
	AbstractCard* makeCard(int type) {
		return new Diamonds(new Card(type));
	}
};

class ClubsFactory: public AbstractCardFactory {
public:
	AbstractCard* makeCard(int type) {
		return new Clubs(new Card(type));
	}
};

class SpadesFactory: public AbstractCardFactory {
public:
	AbstractCard* makeCard(int type) {
		return new Spades(new Card(type));
	}
};

int main() {
	srand(time(NULL));
	HeartsFactory h;
	DiamondsFactory d;
	ClubsFactory c;
	SpadesFactory s;

	list<AbstractCard*> lst;
	for (size_t i = 1; i < 14; i++) {
		lst.insert(next(lst.begin(), rand() % (lst.size() + 1)), h.makeCard(i));
		lst.insert(next(lst.begin(), rand() % (lst.size() + 1)), d.makeCard(i));
		lst.insert(next(lst.begin(), rand() % (lst.size() + 1)), c.makeCard(i));
		lst.insert(next(lst.begin(), rand() % (lst.size() + 1)), s.makeCard(i));
	}

	for (auto c : lst) {
		c->show();
		cout << endl;
	}
	return 0;
}
