

string Utilities::cardTypeToString(CardType type)
{

    return cardTypeString.at(type);

}

string Utilities::cardNumberToString(CardNumber number)

{
    return cardNumberString.at(number);
}

const list<string>& Utilities::getPokerPlayers()
{
    return pokerPlayers;
}


const unordered_map<CardType, string> Utilities::cardTypeString = {
        { HEARTS, "Hearts" },
        { DIAMONDS, "Diamonds" },
        { CLUBS, "Clubs" },
        { SPADES, "Spades" }
};

const unordered_map<CardNumber, string> Utilities::cardNumberString = {
        { ACE, "Ace" },
        { TWO, "Two" },
        { THREE, "Three" },
        { FOUR, "Four" },
        { FIVE, "Five" },
        { SIX, "Six" },
        { SEVEN, "Seven" },
        { EIGHT, "Eight" },
        { NINE, "Nine" },
        { TEN, "Ten" },
        { JACK, "Jack" },
        { QUEEN, "Queen" },
        { KING, "King" }
};

const list<string> Utilities::pokerPlayers = {
        "Doyle Brunson", "Phil Ivey", "Daniel Negreanu", "Phil Hellmuth",
        "Johnny Chan", "Erik Seidel", "Antonio Esfandiari", "Chris Moneymaker",
        "Vanessa Selbst", "Jason Koon", "Bryn Kenney", "Justin Bonomo",
        "Tom Dwan", "Fedor Holz", "Dan Smith", "Sam Trickett",
        "Doug Polk", "Liv Boeree", "Scotty Nguyen", "Barry Greenstein",
        "Jennifer Harman", "Patrik Antonius", "Tony G", "Gus Hansen",
        "Shaun Deeb", "Maria Ho", "Stephen Chidwick", "Chris Ferguson",
        "Jason Mercier", "Michael Mizrachi", "ElkY (Bertrand Grospellier)"
};


list<string> Utilities::getAIPlayerNames(const list<string>& playerList, int count)
{
    vector<string> shuffledPlayers(playerList.begin(), playerList.end());
    random_device rd;
    mt19937 g(rd());
    shuffle(shuffledPlayers.begin(), shuffledPlayers.end(), g);
    return list<string>(shuffledPlayers.begin(), shuffledPlayers.begin() + count);
}

void Utilities::waitOneSecond() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start;
    while (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() < 1) {
        end = std::chrono::high_resolution_clock::now();
    }
}

bool Utilities::isStraight(const vector<CardNumber> &numbers, int wildCardCount) {
    int consecutive = 0;
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == numbers[i - 1] + 1) {
            consecutive++;
        } else if (wildCardCount > 0) {
            wildCardCount--;
            consecutive++;
        } else {
            consecutive = 0;
        }
        if (consecutive >= 4) {
            return true;
        }
    }
    return false;
}

