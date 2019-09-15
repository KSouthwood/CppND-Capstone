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

Controller::~Controller() {
}

/***************
 *  Summary: Run the game
 *
 *  Description: Main game loop.
 *
 *  Parameter(s):
 *  	rend - window renderer object
 */
void Controller::GameLoop(Renderer *renderer) {
    bool game_over = false;

    while (!game_over) {
        // shuffle cards if needed
        if (deck.NeedShuffle()) {
            deck.Shuffle();
        }

        // ensure we start each hand off fresh
        ClearHands();
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);
        SDL_RenderPresent(renderer->renderer);

        // deal initial cards
        DealHands(renderer);

        // have player play their hand
        PlayPlayerHand(renderer);

        // check if player busted and skip dealers turn if they did
        if (player.score <= 21) {
            // play the dealers hand
            PlayDealerHand(renderer);
        }

        // determine who won
        WhoWon(renderer);

        SDL_Event e;
        bool quit = false;
        while (!quit) {
            // check for SDL event
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                    game_over = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    // handle the keypresses we want, ignoring the rest
                    switch (e.key.keysym.sym) {
                        case SDLK_p:
                            quit = true;
                            break;
                        case SDLK_q:
                            quit = true;
                            game_over = true;
                            break;
                        default:
                            break;
                    }
                }
                if (e.type == SDL_MOUSEBUTTONUP) {
                    int x = e.button.x;
                    int y = e.button.y;
                    if ((x >= choice_one.x) && (x <= choice_one.x + choice_one.w) &&
                            (y >= choice_one.y) && (y <= choice_one.y + choice_one.h)) {
                        quit = true;
                    }

                    if ((x >= choice_two.x) && (x <= choice_two.x + choice_two.w) &&
                            (y >= choice_two.y) && (y <= choice_two.y + choice_two.h)) {
                        quit = true;
                        game_over = true;
                    }
                }

            }
        }
    }
}

/***************
 *  Summary: Clear the hands of player and dealer
 *
 *  Description: Set the Hand structs to initial values to play a fresh hand.
 *
 *  Parameter(s):
 *  	N/A
 */
void Controller::ClearHands() {
        dealer.hand.clear();
        dealer.score = 0;
        dealer.faceup = false;

        player.hand.clear();
        player.score = 0;
        player.faceup = true;
}

/***************
 *  Summary: Deal the initial hands
 *
 *  Description: Deal the initial two cards to the dealer and player, updating
 *      the window after each card dealt.
 *
 *  Parameter(s):
 *  	renderer - window renderer object
 */
void Controller::DealHands(Renderer *renderer) {
    for (int i = 0; i < 2; i++) {
        player.hand.push_back(deck.DealCard());
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);
        SDL_RenderPresent(renderer->renderer);
        SDL_Delay(200);

        dealer.hand.push_back(deck.DealCard());
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);
        SDL_RenderPresent(renderer->renderer);
        SDL_Delay(200);
    }

    player.score = deck.ScoreHand(player.hand, deck);
    dealer.score = deck.ScoreHand(dealer.hand, deck);
}

/***************
 *  Summary: Have player play their hand
 *
 *  Description: Have player play their hand using an event loop to read the
 *      keyboard.
 *
 *  Parameter(s):
 *  	renderer - window renderer object
 */
void Controller::PlayPlayerHand(Renderer *renderer) {
    SDL_Event e;
    bool done = false;
    while (!done) {
        while (SDL_PollEvent(&e)) {
            bool hit = false;
            if (e.type == SDL_KEYDOWN) {
                    // handle the keypresses we want, ignoring the rest
                    switch (e.key.keysym.sym) {
                        case SDLK_h: // player hits
                            hit = true;
                            break;
                        case SDLK_s: // player stands
                            done = true;
                            break;
                        default:
                            break;
                    }
            }

            if (e.type == SDL_MOUSEBUTTONUP) {
                    int x = e.button.x;
                    int y = e.button.y;
                    if ((x >= choice_one.x) && (x <= choice_one.x + choice_one.w) &&
                            (y >= choice_one.y) && (y <= choice_one.y + choice_one.h)) {
                        hit = true;
                    }

                    if ((x >= choice_two.x) && (x <= choice_two.x + choice_two.w) &&
                            (y >= choice_two.y) && (y <= choice_two.y + choice_two.h)) {
                        done = true;
                    }
            }

            if (hit == true) {
                player.hand.push_back(deck.DealCard());
                player.score = deck.ScoreHand(player.hand, deck);
                renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);
                SDL_RenderPresent(renderer->renderer);

                if (player.score > 21 || player.hand.size() == 5) {
                    done = true; // player busted or has the max cards
                }
            }
        }
    }

//    SDL_Delay(200);
}

/***************
 *  Summary: Play the dealer hand
 *
 *  Description: Play the dealer hand hitting on 16 or less and standing on 17
 *      or more. Max of five cards.
 *
 *  Parameter(s):
 *  	renderer - window renderer object
 */
void Controller::PlayDealerHand(Renderer *renderer) {
    // show dealers hole card
    dealer.faceup = true;
    renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);
    SDL_RenderPresent(renderer->renderer);
    SDL_Delay(800);

    while (dealer.score < 17 && dealer.hand.size() < 5) {
        dealer.hand.push_back(deck.DealCard());
        dealer.score = deck.ScoreHand(dealer.hand, deck);
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);
        SDL_RenderPresent(renderer->renderer);
        SDL_Delay(250);
    }
}

/***************
 *  Summary: Compare dealer and player scores
 *
 *  Description: Compare the scores of the dealer hand to the player hand to
 *      determine who won.
 *
 *  Parameter(s):
 *  	N/A
 */
void Controller::WhoWon(Renderer *renderer) {
    renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup);

    const std::string res_path = renderer->GetResourcePath();
    SDL_Texture *winner = renderer->LoadTexture(res_path + "YouWon!.bmp");
    SDL_Texture *loser = renderer->LoadTexture(res_path + "YouLost!.bmp");
    SDL_Texture *tie = renderer->LoadTexture(res_path + "Push.bmp");
    SDL_Texture *play = renderer->LoadTexture(res_path + "Play.bmp");
    SDL_Texture *quit = renderer->LoadTexture(res_path + "Quit.bmp");

    SDL_SetRenderDrawColor(renderer->renderer, col_badge.r, col_badge.g, col_badge.b, col_badge.a);
    SDL_RenderFillRect(renderer->renderer, &choice_one);
    SDL_RenderFillRect(renderer->renderer, &choice_two);
    SDL_RenderCopy(renderer->renderer, play, NULL, &choice_one);
    SDL_RenderCopy(renderer->renderer, quit, NULL, &choice_two);

    if (player.score > 21) {
        CenterTexture(loser, renderer);
    }
    else if (dealer.score > 21) {
        CenterTexture(winner, renderer);
    }
    else if (player.score > dealer.score) {
        CenterTexture(winner, renderer);
    }
    else if (player.score < dealer.score) {
        CenterTexture(loser, renderer);
    }
    else {
        CenterTexture(tie, renderer);
    }

    SDL_RenderPresent(renderer->renderer);
}

/***************
 *  Summary: Render a texture in the middle of the window
 *
 *  Description: Render a supplied texture in the middle of the window.
 *
 *  Parameter(s):
 *  	image - the texture to display
 */
void Controller::CenterTexture(SDL_Texture* image, Renderer *renderer) {
    SDL_Point win;
    SDL_Rect dest;

    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_GetWindowSize(renderer->window, &win.x, &win.y);
    dest.x = (win.x / 2) - (dest.w / 2);
    dest.y = (win.y / 2) - (dest.h / 2);

    SDL_RenderCopy(renderer->renderer, image, NULL, &dest);
}
