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

#include "Controller.h"

Controller::Controller() {
    DeckOfCards deck;
}

Controller::Controller(const Controller& orig) {
}

Controller::~Controller() {
}

void Controller::GameLoop(Renderer rend) {
    std::cout << "Starting game...\n"; //TODO Delete

    std::vector<int> dealer, player;
    deck.Shuffle();
}

/*
 * Delete after we get our assumptions correct and the display working
 */
void Controller::Test(Renderer rend) {
    std::cout << "Dealing hands" << std::endl;
    std::vector<int> dealer, player;


    rend.Render(dealer, player, deck);
    SDL_Delay(1000);



    SDL_Delay(1000);


    SDL_Event event;
    bool quit = false;
    int card = 0;

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        std::cout << card << std::endl;
        if (card % 2) {
            player.push_back(deck.DealCard());
        } else {
            dealer.push_back(deck.DealCard());
        }

        rend.Render(dealer, player, deck);
        SDL_Delay(200);

        card++;

        if (card == 52) {
            card = 0;
            deck.Shuffle();
        }

        if (card % 10 == 0) {
            dealer.clear();
            player.clear();
        }

    }
}