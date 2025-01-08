//
// Created by Vlad on 1/7/2025.
//

#ifndef POKERGAME_2_CMAKE_CARD_H
#define POKERGAME_2_CMAKE_CARD_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Utilities.h"
#include "Enums.h"

using namespace std;


template <typename T>
class PileOfCards {
public:
    PileOfCards(TemplateType type = PLAYER_HAND) : maxCards((int)type) {};
    void addCard(const T& card)
    {
        if (cards.size() < maxCards)
        {
            cards.push_back(card);
        }
        else
        {
            std::cout << "Hand is full." << std::endl;
        }
    }

    void clear()
    {
        cards.clear();
    }

    friend std::ostream& operator<<(std::ostream& os, const PileOfCards& hand)
    {
        for (const T& card : hand.cards)
        {
            os << card << " ";
        }
        return os;
    }

    bool isEmpty() const
    {
        return cards.empty();
    }

    int size() const
    {
        return cards.size();
    }

    T at(int pos) const
    {
        return cards.at(pos);
    }

    /*bool containsWildCard() const
    {
        for (const T& card : cards)
        {
            if (card.isWild())
            {
                return true;
            }
        }
        return false;
    }*/

private:
    std::vector<T> cards;
    int maxCards = 2;

};

class Card {
public:
    Card(CardType type, CardNumber number) : type(type), number(number) {}
    virtual ~Card() = default;
    CardType getType() const;
    CardNumber getNumber() const;
    virtual bool isWild() const;
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    bool operator==(const Card& other) const;
    bool operator<(const Card& other) const;
protected:
    CardType type;
    CardNumber number;
};

class WildCard : public Card {
public:
    WildCard(CardType type) : Card(type, JOKER) {}

    bool isWild() const override;

    friend std::ostream& operator<<(std::ostream& os, const WildCard& card);
};


class Deck {
protected:
    Deck();
    static Deck* instance;
    std::vector<Card> cards;

public:
    static Deck* getInstance();

    Deck(const Deck& other) = delete;
    void operator=(const Deck&) = delete;

    void shuffle();

    Card draw();

    bool isEmpty() const;
};

class CommunityCards {
public:
    static CommunityCards* getInstance();

    void addCard(const Card& card);

    void clear();

    bool isEmpty() const;

    int size() const;

    PileOfCards<Card> getCards() const { return cards; }

private:
    CommunityCards() : maxCards(5) {}
    static CommunityCards* instance;
    PileOfCards<Card> cards;
    const int maxCards;
};


#endif //POKERGAME_2_CARD_H
