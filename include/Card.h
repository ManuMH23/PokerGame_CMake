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
#include <exception>

using namespace std;


template <typename T>
class PileOfCards {
public:
    inline PileOfCards(TemplateType type = PLAYER_HAND) : maxCards((int)type) {};
    inline void addCard(const T& card)
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

    inline void clear()
    {
        cards.clear();
    }

    inline friend std::ostream& operator<<(std::ostream& os, const PileOfCards& hand)
    {
        for (const T& card : hand.cards)
        {
            os << card << " ";
        }
        return os;
    }

    inline bool isEmpty() const
    {
        return cards.empty();
    }

    inline int size() const
    {
        return cards.size();
    }

    inline T at(int pos) const
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
    inline Card(CardType type, CardNumber number) : type(type), number(number) {}
    inline Card(const Card& other);
    ~Card() = default;

    inline CardType getType() const;
    inline CardNumber getNumber() const;
    inline virtual bool isWild() const;
    inline friend std::ostream& operator<<(std::ostream& os, const Card& card);
    inline bool operator==(const Card& other) const;
    inline bool operator<(const Card& other) const;
protected:
    CardType type;
    CardNumber number;
};

class WildCard : public Card {
public:
    inline WildCard(CardType type) : Card(type, JOKER) {}

    inline bool isWild() const override;

    inline friend std::ostream& operator<<(std::ostream& os, const WildCard& card);
};


class Deck {
protected:
    inline Deck();
    static Deck* instance;
    std::vector<Card> cards;

public:
    inline static Deck* getInstance();

    inline Deck(const Deck& other) = delete;
    inline void operator=(const Deck&) = delete;

    inline void shuffle();

    inline Card draw();

    inline bool isEmpty() const;
};

class CommunityCards {
public:
    inline static CommunityCards* getInstance();

    inline void addCard(const Card& card);

    inline void clear();

    inline void displayCards();

    inline bool isEmpty() const;

    inline int size() const;

    inline PileOfCards<Card> getCards() const { return cards; }

private:
    inline CommunityCards() : maxCards(5) {}
    static CommunityCards* instance;
    PileOfCards<Card> cards = PileOfCards<Card>(COMMUNITY_CARDS);
    const int maxCards;
};


class DeckEmptyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Deck is empty.";
    }
};


#endif //POKERGAME_2_CARD_H
