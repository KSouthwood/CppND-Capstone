/*
 * The MIT License
 *
 * Copyright 2019 Keri Southwood-Smith.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include<random>
#include<array>

#include "Card.h"

/******************
 * CONSTANTS
 */
const static std::array<int, 13> values = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const static int cards_in_deck = 52;

// filenames
const static std::string suits[4] = {"spade.bmp", "club.bmp",
        "diamond.bmp", "heart.bmp"};

const static std::string blacks[13] = {"black-A.bmp", "black-2.bmp",
        "black-3.bmp", "black-4.bmp", "black-5.bmp",
        "black-6.bmp", "black-7.bmp", "black-8.bmp",
        "black-9.bmp", "black-10.bmp", "black-J.bmp",
        "black-Q.bmp", "black-K.bmp"};

const static std::string reds[13] = {"red-A.bmp", "red-2.bmp",
        "red-3.bmp", "red-4.bmp", "red-5.bmp",
        "red-6.bmp", "red-7.bmp", "red-8.bmp",
        "red-9.bmp", "red-10.bmp", "red-J.bmp",
        "red-Q.bmp", "red-K.bmp"};

/******************
 * CLASS
 */
class DeckOfCards {
public:
    DeckOfCards();
    ~DeckOfCards();

    void Shuffle();
    int DealCard();
    int ScoreHand(std::vector<int> hand, DeckOfCards deck);
    bool NeedShuffle();

    Card** shoe;

private:
    bool shuffle;       // do we have to shuffle cards
    int card_to_deal;   // keep track of cards
    int reshuffle;      // point in shoe we have to re-shuffle

    void CreateShoe();

};

#endif /* DECKOFCARDS_H */

