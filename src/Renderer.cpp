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

#include "Renderer.h"
#include "DeckOfCards.h"

/******************
 *  Summary: Constructor for a renderer
 *
 *  Description: Initialize the SDL2 system, then create our window and renderer.
 *
 *  Parameter(s):
 *      window_width: width of window to create
 *      window_height: height of window to create
 */
Renderer::Renderer(const std::size_t window_width,
        const std::size_t window_height) :
        window_width(window_width), window_height(window_height) {
    // Create the window
    window = SDL_CreateWindow("SDLBlackjack", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

/******************
 *  Summary: Destructor for a renderer
 *
 *  Description: Clean up renderer and window objects and shut down SDL2 system.
 *
 *  Parameter(s):
 *      N/A
 */

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/******************
 *  Summary: Draw our window
 *
 *  Description: Update the window when called after something changes. Also
 *      takes care of hiding the dealers card.
 *
 *  Parameter(s):
 *      N/A
 */

void Renderer::Render(std::vector<int> dealer, std::vector<int> player, DeckOfCards deck) {
    // clear the window and fill with green background
    SDL_SetRenderDrawColor(renderer, 0x00, 0xA1, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // draw the dealers hand
    for (int i = 0; i < dealer.size(); i++) {
        SDL_RenderFillRect(renderer, &d_pos[i]);
        SDL_Texture *rank = SDL_CreateTextureFromSurface(renderer, deck.shoe[dealer[i]]->GetRank());
        SDL_Texture *suit = SDL_CreateTextureFromSurface(renderer, deck.shoe[dealer[i]]->GetSuit());
        SDL_Rect rect_rank = {.x = 40 + (i * 120), .y = 30, .w = 40, .h = 40};
        SDL_Rect rect_suit = {.x = 40 + (i * 120), .y = 70, .w = 40, .h = 40};
        SDL_RenderCopy(renderer, rank, NULL, &rect_rank);
        SDL_RenderCopy(renderer, suit, NULL, &rect_suit);
    }

    // draw the players hand
    for (int i = 0; i < player.size(); i++) {
        SDL_RenderFillRect(renderer, &p_pos[i]);
        SDL_Texture *rank = SDL_CreateTextureFromSurface(renderer, deck.shoe[player[i]]->GetRank());
        SDL_Texture *suit = SDL_CreateTextureFromSurface(renderer, deck.shoe[player[i]]->GetSuit());
        SDL_Rect rect_rank = {.x = 40 + (i * 120), .y = 230, .w = 40, .h = 40};
        SDL_Rect rect_suit = {.x = 40 + (i * 120), .y = 270, .w = 40, .h = 40};
        SDL_RenderCopy(renderer, rank, NULL, &rect_rank);
        SDL_RenderCopy(renderer, suit, NULL, &rect_suit);
    }

    // finally, update the window
    SDL_RenderPresent(renderer);
}

/******************
 *  Summary: Check to make sure everything is fine
 *
 *  Description: Check we have valid pointers to window and renderer just in
 *      case we had a problem.
 *
 *  Parameter(s):
 *      N/A
 */
bool Renderer::RendererValid() {
    return ((window != nullptr) && (renderer != nullptr));
}