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
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Renderer.h"
#include "DeckOfCards.h"
#include "Controller.h"

/****** CONSTANTS ******/
const std::size_t WINDOW_WIDTH = 620;
const std::size_t WINDOW_HEIGHT = 570;

/***** MAIN *****/
int main(int, char**) {
    // Start up SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0) {
        // Started up fine, continue
        Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
        Controller game;
        if (renderer.RendererValid()) {
            game.GameLoop(&renderer);
        }

        return 0;
    }
}
