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
        if (deck.shuffle) {
            deck.Shuffle();
        }

        ClearHands();
        renderer->Render(dealer.hand, player.hand, deck, dealer.faceup);

        // deal initial cards
        DealHands(renderer);
        std::cout << "Player: " << player.score << " Dealer: " << dealer.score << std::endl; //TODO delete

        // have player play their hand
        PlayPlayerHand(renderer);
        std::cout << "Player: " << player.score << " Dealer: " << dealer.score << std::endl; //TODO delete

        // check if player busted and skip dealers turn if they did
        if (player.score <= 21) {
            // play the dealers hand
            PlayDealerHand(renderer);
        }
        std::cout << "Player: " << player.score << " Dealer: " << dealer.score << std::endl; //TODO delete

        // determine who won
        WhoWon(renderer);

        std::cout << "Entering exit wait loop...\n"; //TODO delete
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            // check for SDL event
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    std::cout << "SDL_QUIT event.\n"; //TODO delete
                    quit = true;
                    game_over = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    // handle the keypresses we want, ignoring the rest
                    switch (e.key.keysym.sym) {
                        case SDLK_y:
                            std::cout << "'Y' pressed.\n"; //TODO delete
                            quit = true;
                            break;
                        case SDLK_n:
                            std::cout << "'N' pressed.\n"; //TODO delete
                            quit = true;
                            game_over = true;
                            break;
                        default:
                            std::cout << "Keypress ignored.\n"; //TODO delete
                            break;
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
        player.faceup = false;
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
        renderer->Render(dealer.hand, player.hand, deck, dealer.faceup);
        SDL_Delay(200);

        dealer.hand.push_back(deck.DealCard());
        renderer->Render(dealer.hand, player.hand, deck, dealer.faceup);
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
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                // handle the keypresses we want, ignoring the rest
                switch (e.key.keysym.sym) {
                    case SDLK_h:
                        std::cout << "'H' pressed.\n"; //TODO delete
                        player.hand.push_back(deck.DealCard());
                        renderer->Render(dealer.hand, player.hand, deck, dealer.faceup);
                        player.score = deck.ScoreHand(player.hand, deck);
                        if (player.score > 21 || player.hand.size() == 5) {
                            // player busted or has the max cards
                            done = true;
                        }
                        break;
                    case SDLK_s:
                        std::cout << "'S' pressed.\n"; //TODO delete
                        done = true;
                        break;
                    default:
                        std::cout << "Keypress ignored.\n"; //TODO delete
                        break;
                }
            }
        }
    }
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
    renderer->Render(dealer.hand, player.hand, deck, dealer.faceup);
    SDL_Delay(800);

    while (dealer.score < 17) {
        dealer.hand.push_back(deck.DealCard());
        dealer.score = deck.ScoreHand(dealer.hand, deck);
        std::cout << "Player: " << player.score << " Dealer: " << dealer.score << std::endl; //TODO delete
        renderer->Render(dealer.hand, player.hand, deck, dealer.faceup);
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
    const std::string res_path = GetResourcePath();
    SDL_Texture *winner = LoadTexture(res_path + "YouWon!.bmp", renderer->renderer);
    SDL_Texture *loser = LoadTexture(res_path + "YouLost!.bmp", renderer->renderer);
    SDL_Texture *tie = LoadTexture(res_path + "Push.bmp", renderer->renderer);

    if (player.score > 21) {
        std::cout << "You lost. :(\n";
        CenterTexture(loser, renderer);
    }
    else if (dealer.score > 21) {
        std::cout << "You won!!\n";
        CenterTexture(winner, renderer);
    }
    else if (player.score > dealer.score) {
        std::cout << "You won!!\n";
        CenterTexture(winner, renderer);
    }
    else if (player.score < dealer.score) {
        std::cout << "You lost. :(\n";
        CenterTexture(loser, renderer);
    }
    else {
        std::cout << "It was a tie.\n";
        CenterTexture(tie, renderer);
    }
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
    int iW, iH;
    SDL_Rect dest;
    SDL_Rect win;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    SDL_GetWindowSize(renderer->window, &win.w, &win.h);
    dest.x = win.w / 2 - iW / 2;
    dest.y = win.h / 2 - iH / 2;
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer->renderer, image, NULL, &dest);
    SDL_RenderPresent(renderer->renderer);
}

/******************
 *  Summary: Get the base path of our resource files
 *
 *  Description: Get the path of resources located in bin/res.
 *
 *  Parameter(s):
 *      subDir - optional sub-directory name if res contains sub-directories
 */
SDL_Texture* Controller::LoadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr){
			std::cout << "SDL_CreateTextureFromSurface failed.\n";
		}
	}
	else {
		std::cout << "LoadBMP failed\n";
	}
	return texture;
}

/******************
 *  Summary: Get the base path of our resource files
 *
 *  Description: Get the path of resources located in bin/res.
 *
 *  Parameter(s):
 *      subDir - optional sub-directory name if res contains sub-directories
 */
std::string Controller::GetResourcePath(const std::string &subDir) {
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif
    static std::string baseRes;
    if (baseRes.empty()) {
        char *basePath = SDL_GetBasePath();
        if (basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        //We replace the last bin/ with res/ to get the the resource path
//        size_t pos = baseRes.rfind("bin");
//        baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
        baseRes = baseRes + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}