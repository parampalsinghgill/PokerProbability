// Author: Parampal Gill
// Date: October 22, 2023

// Card shuffling, dealing and probability of hand types

//These websites may be of benefit on this project:
// https://en.wikipedia.org/wiki/Poker_probability
// https://en.wikipedia.org/wiki/List_of_poker_hands#:~:text=A%20straight%20is%20a%20hand,K%E2%99%A3%20Q%E2%99%A3%20J

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52
#define HAND_SIZE 5
#define HANDS_IN_DECK 10
#define NUMBER_OF_HANDS_PLAYED 10000000  //Currently set to 10 million
#define NUMB_HANDS_STR "10 million" //Currently set to 10 million
#define TRUE 1
#define FALSE 0

// prototypes of functions supplied
void deal(const unsigned int wDeck[], const char* wFace[], //display all cards in deck
    const char* wSuit[]);
void dealNextHand(unsigned int wDeck[], unsigned int hand[]); //deal out next hand from the deck
int isFourOfAKind(const unsigned int hand[]);  // return true if hand contains four of a kind and false otherwise

// prototypes of functions you must implement
void swap(unsigned int* const, unsigned int* const); //swap the two cards pointed to by the 2 pointers
void shuffle(unsigned int wDeck[]); //shuffle deck
int isPair(const unsigned int hand[]);  // return true if hand contains a pair and false otherwise
int isTwoPair(const unsigned int hand[]);  // return true if hand contains a two pair and false otherwise
int isThreeOfAKind(const unsigned int hand[]);  // return true if hand contains three of a kind and false otherwise
int isStraight(const unsigned int hand[]);  // return true if hand is a straight and false otherwise
int isFlush(const unsigned int hand[]);  // return true if hand is a flush and false otherwise
int isFullHouse(const unsigned int hand[]);  // return true if hand is a full house and false otherwise


int main(void)
{
    // define and initialize deck array
    unsigned int deck[CARDS];

    // initialize deck with values 0 to CARDS-1
    // value / 13 caluclates suit #     { "Hearts", "Diamonds", "Clubs", "Spades" };
    // value % 13 calculates face card  {Ace, 2, 3, ... 10, Jack, Queen, King}
    for (size_t card = 0; card < CARDS; ++card)
    {
        deck[card] = card;
    }

    srand((unsigned int)time(NULL)); // seed random-number generator

    // initialize suit array                       
    const char* suit[SUITS] =
    { "Hearts", "Diamonds", "Clubs", "Spades" };

    // initialize face array                   
    const char* face[FACES] =
    { "Ace", "Deuce", "Three", "Four",
     "Five", "Six", "Seven", "Eight",
     "Nine", "Ten", "Jack", "Queen", "King" };

    shuffle(deck);  // uncomment after completing the implementation
                    // of the swap() and shuffle() functions
    
    deal(deck, face, suit); // display the deck unshuffled

    unsigned int hand[HAND_SIZE]; // will contain the cards in the hand.

    //Define and initialize variables used to count each type of hand
    unsigned int pairCount = 0;
    unsigned int twoPairCount = 0;
    unsigned int threeOfAKindCount = 0;
    unsigned int straightCount = 0;
    unsigned int flushCount = 0;
    unsigned int fullHouseCount = 0;
    unsigned int fourOfAKindCount = 0;
    unsigned int straightFlushCount = 0; //NOTE: This count includes both straight flushes and royal flushes.

    // Shuffle the deck for the first time
    // After this, we shuffle deck every time we do not have enough undealth cards 
    // for a complete hand which will be every 10 deals assuming five card hands
    shuffle(deck);

    // Deal out NUMBER_OF_HANDS_PLAYED hands
    for (size_t hands = 1; hands < NUMBER_OF_HANDS_PLAYED; ++hands)
    {
        dealNextHand(deck, hand); // Deal out next 5 cards from the deck into the array hand

        // test hand
        //unsigned int hand[] = {5, 6, 4, 8, 7};

        // Does hand have a pair?
        if (isPair(hand))
        {
            ++pairCount;  // Yes, increment pair count
            //printf("Loop: %d; Pair Count: %d\n", hands, pairCount);
        }

        // Does hand have two pair?
        else if (isTwoPair(hand))
        {
            ++twoPairCount;
        }

        // Does hand have three of a kind?
        else if (isThreeOfAKind(hand))
        {
            ++threeOfAKindCount;
        }

        // Does hand have a straight?
        else if (isStraight(hand))
        {
            // Check if also a flush
            if (isFlush(hand))
            {
                ++straightFlushCount; //both straight and flush
            }
            else
            {
                ++straightCount; // nope, just a straight
            }
        }

        // Does hand have a flush?
        else if (isFlush(hand)) //not a straight, how about a flush?
        {
            ++flushCount;
        }

        // Does hand have a full house?
        else if (isFullHouse(hand))
        {
            ++fullHouseCount;
        }

        // Does hand have four of a kind?
        else if (isFourOfAKind(hand))
        {
            ++fourOfAKindCount;
        }
    }

    printf("\nA pair occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a pair is %.2f %c", pairCount, pairCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nTwo pair occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of two pair is %.2f %c", twoPairCount, twoPairCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nThree of a kind occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of three of a kind is %.2f %c", threeOfAKindCount, threeOfAKindCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nA straight occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a straight is %.3f %c", straightCount, straightCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nA flush occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a flush is %.3f %c", flushCount, flushCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nA full house occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a full house is %.4f %c", fullHouseCount, fullHouseCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nFour of a kind occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of four of a kind is %.4f %c", fourOfAKindCount, fourOfAKindCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    printf("\nStraight flush occurred %d times in "NUMB_HANDS_STR" hands, which means the probability of a straight flush is %.5f %c", straightFlushCount, straightFlushCount * 100.0 / NUMBER_OF_HANDS_PLAYED, '%');
    puts("");

}

// Display all of the cards in the deck
void deal(const unsigned int wDeck[], const char* wFace[],
    const char* wSuit[])
{
    // deal each of the cards
    for (size_t card = 0; card < CARDS; ++card) {
        size_t suit = wDeck[card] / FACES;
        size_t face = wDeck[card] % FACES;
        printf("%5s of %-8s%c", wFace[face], wSuit[suit],
            card % 4 == 3 ? '\n' : '\t'); // 4-column format 
    }
}

// Deal out the next HAND_SIZE cards into the array hand[]
// If not enough undealt cards left in wDeck, shuffle wDeck and 
//    start dealing from beginning of the wDeck again.
void dealNextHand(unsigned int wDeck[], unsigned int hand[])
{
    static unsigned int currentCard = 0; //remembers which is the next card to be dealt.

    // Shuffle deck and start from beginning of the deck if not enough cards left for a whole hand
    if ((currentCard + HAND_SIZE) >= CARDS)
    {
        shuffle(wDeck);
        currentCard = 0;
    }

    // Deal out HAND_SIZE cards from wDeck into the hand array
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        hand[card] = wDeck[currentCard++];
    }
}

/*

Below is the complete implementation of the isFourOfAKind() function.

You should be able to use a variation of this function to compute two of a kind, three of a kind and full house.

The straight, flush and royal flush(optional) calculations will require different logic.

After you have completed the swap() and shuffle() functions and uncommented the call to shuffle(),
this start code should run without errors and the your result for 4 of a kind should be very close to
my results in my sample output.  Then you will be ready to tackle completing the other function stubs.

*/

// Returns true if hand contains four of kind and false otherwise
int isFourOfAKind(const unsigned int hand[])
{
    unsigned int faceCnt[FACES] = { 0 };

    // Calculate the frequency of each face card in the hand
    // In other words, it calculates how many Aces, deuces, 3's, etc. in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % FACES];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any face card occurred 4 times in the hand
    for (size_t face = 0; face < FACES; ++face)
    {
        if (faceCnt[face] == 4)
        {
            return TRUE; // Yes!!! Return true.
        }
    }

    return FALSE; //Nope ;-(
}

// Student implements the 8 functions below

// Swap the two unsigned ints pointed to by the pointers card1 and card2
void swap(unsigned int* const card1, unsigned int* const card2)
{
    unsigned int temp;
    temp    = *card1;
    *card1  = *card2;
    *card2  = temp;
}

// Shuffle cards in deck
// Must invoke swap() function above
void shuffle(unsigned int wDeck[])
{
    unsigned int randomCard;

    for (unsigned int card = 0; card < CARDS; ++card)
    {
        randomCard = rand() % CARDS;

        swap(&wDeck[card], &wDeck[randomCard]);
    }
}

// Returns true if hand contains only a pair and false other wise
// NOTE: Will return FALSE if the hand contains any of these hand types as well:
//  1) Hand has 2 pairs
//  2) Hand has 3 of a kind
//  2) Hand is a full house
//  3) Hand has 4 of a kind
int isPair(const unsigned int hand[])
{
    unsigned int faceCnt[FACES] = { 0 };
    int numTwoPairs = 0;
    int numThreePairs = 0;

    // Calculate the frequency of each face card in the hand
    // In other words, it calculates how many Aces, deuces, 3's, etc. in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % FACES];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any face card occurred 4 times in the hand
    for (size_t face = 0; face < FACES; ++face)
    {
        if (faceCnt[face] == 2)
        {
            ++numTwoPairs;
        }

        if (faceCnt[face] == 3)
        {
            ++numThreePairs;
        }
    }

    if (numTwoPairs == 1 && numThreePairs == 0)
    {
        return TRUE;
    }

    return FALSE; //Nope ;-(
}

// Returns true if hand contains two pairs and false otherwise
// NOTE: Will return FALSE if the hand contains any of these hand types as well:
//  1) Hand has 3 of a kind
//  2) Hand is a full house
//  3) Hand has 4 of a kind
int isTwoPair(const unsigned int hand[])
{
    unsigned int faceCnt[FACES] = { 0 };
    int numPairs = 0;

    // Calculate the frequency of each face card in the hand
    // In other words, it calculates how many Aces, deuces, 3's, etc. in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % FACES];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any face card occurred 4 times in the hand
    for (size_t face = 0; face < FACES; ++face)
    {
        if (faceCnt[face] == 2)
        {
            ++numPairs;
        }
    }

    if (numPairs == 2)
    {
        return TRUE;
    }

    return FALSE; //Nope ;-(
}

// Returns true if hand contains 3 of a kind and false otherwise
// NOTE: Will return FALSE if the hand contains any of these hand types as well:
//  1) Hand has a full house
//  2) Hand has 4 of a kind
int isThreeOfAKind(const unsigned int hand[])
{
    unsigned int faceCnt[FACES] = { 0 };
    int numTwoPairs = 0;
    int numThreePairs = 0;

    // Calculate the frequency of each face card in the hand
    // In other words, it calculates how many Aces, deuces, 3's, etc. in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % FACES];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any face card occurred 4 times in the hand
    for (size_t face = 0; face < FACES; ++face)
    {
        if (faceCnt[face] == 2)
        {
            ++numTwoPairs;
        }

        if (faceCnt[face] == 3)
        {
            ++numThreePairs;
        }
    }

    if (numTwoPairs == 0 && numThreePairs == 1)
    {
        return TRUE;
    }

    return FALSE; //Nope ;-(
}

// Returns true if hand is a straight and false otherwise
// This function does NOT check if also a flush. That is done in main()

// VERY IMPORTANT: The Ace can be used to create a straight in 2 different ways:
//  Ace, 2, 3, 4, 5 and 
//  10, Jack, Queen, King, Ace
//  You need to check for both uses of the Ace to create a straight
int isStraight(const unsigned int hand[])
{
    unsigned int faceCnt[FACES + 1] = { 0 };

    // Calculate the frequency of each face card in the hand
    // In other words, it calculates how many Aces, deuces, 3's, etc. in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % FACES];
    }

    // put the ace in the end as well
    faceCnt[FACES] = faceCnt[0];

    int totalHigh = 0;
    // check if 5 arrarys are high in a row
    for (int val = 0; val < FACES + 1; ++val)
    {
        // if current val is high, check if next 4 are high as well
        if (faceCnt[val] == 1)
        {
            ++totalHigh;
            
            if (totalHigh == 5)
            {
                return TRUE;
            }
        }
        else
        {
            totalHigh = 0;
        }
    }

    return FALSE;
}

// Returns true if hand is a flush and false otherwise
int isFlush(const unsigned int hand[])
{
    unsigned int suitCnt[SUITS] = { 0 };

    // Calculate the frequency of each suit in the hand
    // In other words, it calculates how many suits in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++suitCnt[hand[card] % SUITS];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any suit occurred 5 times in the hand
    for (size_t face = 0; face < SUITS; ++face)
    {
        if (suitCnt[face] == 5)
        {
            return TRUE; // Yes!!! Return true.
        }
    }

    return FALSE; //Nope ;-(
}

// return true if hand is a full house and false otherwise
int isFullHouse(const unsigned int hand[])
{
    unsigned int faceCnt[FACES] = { 0 };
    int numTwoPairs = 0;
    int numThreePairs = 0;

    // Calculate the frequency of each face card in the hand
    // In other words, it calculates how many Aces, deuces, 3's, etc. in the hand of 5 cards
    for (size_t card = 0; card < HAND_SIZE; ++card)
    {
        ++faceCnt[hand[card] % FACES];
    }

    // Iterate through all of the frequency counts to find out if 
    //     any face card occurred 4 times in the hand
    for (size_t face = 0; face < FACES; ++face)
    {
        if (faceCnt[face] == 2)
        {
            ++numTwoPairs;
        }

        if (faceCnt[face] == 3)
        {
            ++numThreePairs;
        }
    }

    if (numTwoPairs == 1 && numThreePairs == 1)
    {
        return TRUE;
    }

    return FALSE; //Nope ;-(
}

