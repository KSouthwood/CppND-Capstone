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

#include "DeckOfCards.h"


DeckOfCards::DeckOfCards() {
    card_to_deal = 0;
    reshuffle = 0;
    shuffle = true;
    CreateShoe();
}

DeckOfCards::~DeckOfCards() {
}

void DeckOfCards::Shuffle() {
    // random number generator set-up
    std::random_device ran_dev;
    std::mt19937 ran_engine(ran_dev());
    std::uniform_int_distribution<int> card_to_swap(0, 51);
    std::uniform_int_distribution<int> reshuffle_card(35, 42);

    Card *temp;
    std::size_t swap;

    for (std::size_t card = cards_in_deck - 1; card > 0; card--) {
        swap = card_to_swap(ran_engine) % card;

        temp = shoe[swap];
        shoe[swap] = shoe[card];
        shoe[card] = temp;
    }

    card_to_deal = 0;
    reshuffle = reshuffle_card(ran_engine);
    shuffle = false;

    return;
}

void DeckOfCards::CreateShoe() {
    shoe = new Card*[cards_in_deck];

    int i, rank;
    for (i = 0; i < cards_in_deck; i++) {
        rank = i /26;
        shoe[i] = new Card(rank % 2 ? reds[i % 13] : blacks[i % 13],
                        suits[i / 13],
                        values[i % 13]);
    }
}

int DeckOfCards::DealCard() {
    return card_to_deal++;
}