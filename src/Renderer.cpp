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

Renderer::Renderer(const std::size_t window_width,
        const std::size_t window_height) :
        window_width(window_width), window_height(window_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Renderer::logSDLerror(std::cout, "SDL_Init");
        }

    // Create the window
    window = SDL_CreateWindow("SDLBlackjack", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        Renderer::logSDLerror(std::cout, "SDL_CreateWindow");
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        Renderer::logSDLerror(std::cout, "SDL_CreateRenderer");
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0xA1, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &dealer0);
    SDL_RenderFillRect(renderer, &dealer1);
    SDL_RenderFillRect(renderer, &dealer2);
    SDL_RenderFillRect(renderer, &dealer3);
    SDL_RenderFillRect(renderer, &dealer4);

    // Update the window
    SDL_RenderPresent(renderer);
}

/******************
 * Summary: Log an SDL error
 *
 * Description: Log an SDL error to an output stream of our choice with an
 *              appropriate message
 *
 * Parameter(s):
 *      os - output stream to send message to
 *      msg - string to print
 */
void Renderer::logSDLerror(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

