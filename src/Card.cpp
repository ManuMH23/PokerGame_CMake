#include "../include/Card.h"
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
#pragma region Card

//Card::Card(CardType type, CardNumber number)
//{
//	this->type = type;
//	this->number = number;
//}

CardType Card::getType() const
{
    return (CardType)this->type;
}

CardNumber Card::getNumber() const
{
    return (CardNumber)this->number;
}

bool Card::isWild() const
{
    return false;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << cardNumberString.at(card.number) << " of " << cardTypeString.at(card.type);
    return os;
}

bool Card::operator==(const Card &other) const {
    return (type == other.type && number == other.number);
}

bool Card::operator<(const Card &other) const {
    return (number < other.number);
}

#pragma endregion

#pragma region WildCard

std::ostream& operator<<(std::ostream& os, const WildCard& card)
{
    os << "Wild Card";
    return os;
}

bool WildCard::isWild() const
{
    return true;
}

#pragma endregion

#pragma region Deck

Card Deck::draw()
{

    if (cards.empty())
    {
        throw std::out_of_range("Deck is empty.");
    }
    Card card = cards.back();
    cards.pop_back();
    return card;

}
//
//Deck::~Deck()
//{
//	cards.clear();
//}

Deck* Deck::instance = nullptr;

void Deck::shuffle()
{

    cards.clear();
    for (int t = HEARTS; t <= SPADES; ++t)
    {
        for (int n = ACE; n <= KING; ++n)
        {
            cards.emplace_back(static_cast<CardType>(t), static_cast<CardNumber>(n));
        }
    }
    cards.emplace_back(CLUBS, JOKER);
    cards.emplace_back(SPADES, JOKER);

    auto rng = default_random_engine(static_cast<unsigned>(std::time(nullptr)));
    std::for_each(cards.begin(), cards.end(), [&](Card&)
    {
        std::shuffle(cards.begin(), cards.end(), rng);
    });
}



bool Deck::isEmpty() const
{
    return cards.empty();
}

Deck::Deck()
{
    for (int t = HEARTS; t <= SPADES; ++t)
    {
        for (int n = ACE; n <= KING; ++n)
        {
            cards.emplace_back(static_cast<CardType>(t), static_cast<CardNumber>(n));
        }
    }
    // Add two jokers to the deck
    cards.emplace_back(CLUBS, JOKER);
    cards.emplace_back(SPADES, JOKER);
    shuffle();
}

Deck* Deck::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Deck();
    }
    return instance;
}

#pragma endregion

#pragma region CommunityCards

CommunityCards* CommunityCards::instance = nullptr;

CommunityCards *CommunityCards::getInstance() {
    if (!instance) {
        instance = new CommunityCards();
    }
    return instance;
}

void CommunityCards::addCard(const Card &card) {
    if (cards.size() < maxCards) {
        cards.addCard(card);
    } else {
        std::cout << "Community cards are full." << std::endl;
    }
}

void CommunityCards::clear() {
    cards.clear();
}

bool CommunityCards::isEmpty() const {
    return cards.isEmpty();
}

int CommunityCards::size() const {
    return cards.size();
}


#pragma endregion


