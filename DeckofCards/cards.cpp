#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <random>    
#include <ctime>  

using std::cout;
using std::endl;
using std::vector;
using std::string;

// Task 1: Create an instance of Card Class with the proper attributes and methods
class Card {
private:
    string suit;
    string label;
    int value;
    int altValue;
    
public:
    // Constructors
    int sortValue;
    Card() {}
    Card(string addSuit, string addLabel, int addValue, int addAltValue, int addSortValue)
        : suit(addSuit), label(addLabel), value(addValue), altValue(addAltValue), sortValue(addSortValue) {}

    // Method to display the card
    void displayCard() {
        cout << " " << label << " of " << suit << endl;
    }
};

class Deck{
private:
    vector<Card> currentDeck;

    // Method to check if the deck is sorted
    bool isSorted() const {
        for (size_t i = 1; i < currentDeck.size(); ++i) {
            if (currentDeck[i - 1].sortValue > currentDeck[i].sortValue) {
                return false;
            }
        }
        return true;
    }

public:
    // Constructors
    Deck() {}

    // Task 2: Create Deck Class with the proper attributes and methods
    Deck(bool newDeck) {
        vector<string> suits = {"Diamonds", "Clubs", "Hearts", "Spades"};
        vector<string> labels = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
        vector<int> values = {1,2,3,4,5,6,7,8,9,10,10,10,10};
        vector<int> altValues = {11,2,3,4,5,6,7,8,9,10,10,10,10};
        vector<int> sortValues = {14,2,3,4,5,6,7,8,9,10,11,12,13};

        // Populate the deck with standard playing cards
        for (const auto e : suits) {
            for (size_t i = 0; i < labels.size(); ++i) {
                Card newCard(e, labels[i], values[i], altValues[i], sortValues[i]);
                currentDeck.push_back(newCard);
            }
        }
    }

    // Task 4: Demonstrate cutting the deck in half
    Deck splitDeck() {
        Deck subDeck;
        size_t halfSize = currentDeck.size() / 2;
        for (size_t i = 0; i < halfSize; ++i) {
            subDeck.currentDeck.push_back(currentDeck.back());
            currentDeck.pop_back();
        }
        return subDeck;
    }

    // Method to deal a card from the deck
    Card dealCard() {
        Card currentCard = currentDeck.back();
        currentDeck.pop_back();
        return currentCard;
    }

    // Task 7: Method to shuffle the deck with the randomizer used in challenges
    void shuffleDeck(int numberOfShuffles) {
        srand(time(NULL)); 

        for (int i = 0; i < numberOfShuffles; i++) {
            // Generate a random permutation of indices
            vector<int> indices(currentDeck.size());
            for (int j = 0; j < currentDeck.size(); ++j) {
                indices[j] = j;
            }

            random_shuffle(indices.begin(), indices.end(), [](int i) { return rand() % i; });

            // Use the generated indices to shuffle the deck
            vector<Card> shuffledDeck(currentDeck.size());
            for (int j = 0; j < currentDeck.size(); ++j) {
                shuffledDeck[j] = currentDeck[indices[j]];
            }
            currentDeck = shuffledDeck;

            // Display the state of the deck after each shuffle
            cout << "State of the deck after shuffle " << i + 1 << ":" << endl;
            displayDeck();
            cout << endl;
        }
    }

    // Method to get the number of cards in the deck
    int cardCount() const {
        return currentDeck.size();
    }

    // Method to display the cards in the deck
    void displayDeck() const {
        for (auto e : currentDeck) {
            e.displayCard();
        }
    }

    // Task 5: RiffleShuffle method
    void riffleShuffle(const Deck& subDeck1, const Deck& subDeck2) {
        size_t subDeck1Index = 0;
        size_t subDeck2Index = 0;
        currentDeck.clear(); // Clear the current deck before shuffling

        // Interleave the cards from subDeck1 and subDeck2
        while (subDeck1Index < subDeck1.currentDeck.size() || subDeck2Index < subDeck2.currentDeck.size()) {
            if (subDeck1Index < subDeck1.currentDeck.size()) {
                currentDeck.push_back(subDeck1.currentDeck[subDeck1Index]);
                subDeck1Index++;
            }
            if (subDeck2Index < subDeck2.currentDeck.size()) {
                currentDeck.push_back(subDeck2.currentDeck[subDeck2Index]);
                subDeck2Index++;
            }
        }
    }

    // Task 6: Shuffle the Deck 8 out shuffle
    void eightOutShuffle() {
        int numShuffles = 0;
        do {
            riffleShuffle(splitDeck(), splitDeck());
            numShuffles++;

            // Display the state of the deck after each shuffle
            cout << "State of the deck after 8-out shuffle " << numShuffles << ":" << endl;
            displayDeck();
            cout << endl;
        } while (numShuffles < 8 && !isSorted());
    }

    // Task 9: Sort method for the deck
    void sortDeck() {
        sort(currentDeck.begin(), currentDeck.end(), [](const Card& a, const Card& b) {
            return a.sortValue < b.sortValue;
        });
    }
};

int main() {
   
    Card myCard("Hearts", "Ace", 1, 11, 14);
    cout << "Displaying the card:" << endl;
    myCard.displayCard();
    cout << endl;

    // Task 2: Create an instance of Deck Class with the proper attributes and methods
    Deck myDeck(true);
    cout << "Displaying the populated deck:" << endl;
    myDeck.displayDeck();
    cout << endl;

    // Task 4: Demonstrate cutting the deck in half
    Deck subDeck1 = myDeck.splitDeck();
    Deck subDeck2 = myDeck;
    cout << "Displaying subdeck 1:" << endl;
    subDeck1.displayDeck();
    cout << endl;
    cout << "Displaying subdeck 2:" << endl;
    subDeck2.displayDeck();
    cout << endl;

    // TASK 5: RiffleShuffle both subdecks back into the one Deck
    cout << "Riffle shuffling both subdecks back into the main deck:" << endl;
    myDeck.riffleShuffle(subDeck1, subDeck2);
    myDeck.displayDeck();

    return EXIT_SUCCESS;
}
