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

#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

#include "DeckOfCards.h"
#include "Card.h"

const static std::size_t CARD_WIDTH  = 100;
const static std::size_t CARD_HEIGHT = 150;

class Renderer {
public:
    Renderer(const std::size_t window_width, const std::size_t window_height);
    ~Renderer();

    void Render(std::vector<int> dealer, std::vector<int> player, DeckOfCards deck);
    bool RendererValid();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    const std::size_t window_width;
    const std::size_t window_height;

    // Card positions
    const SDL_Rect d_pos[5] = {
        {.x =  30, .y = 20, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 150, .y = 20, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 270, .y = 20, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 390, .y = 20, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 510, .y = 20, .w = CARD_WIDTH, .h = CARD_HEIGHT}
    };

    const SDL_Rect p_pos[5] = {
        {.x =  30, .y = 220, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 150, .y = 220, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 270, .y = 220, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 390, .y = 220, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 510, .y = 220, .w = CARD_WIDTH, .h = CARD_HEIGHT}
    };
};

#endif /* RENDERER_H */

