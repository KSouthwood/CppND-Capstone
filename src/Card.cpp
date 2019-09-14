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

#include "Card.h"
Card::Card() {

}

Card::Card(const std::string rank_file, const std::string suit_file, int val) {
    value = val;

    std::string basepath = GetResourcePath();
    std::string rankpath = basepath + rank_file;
    std::string suitpath = basepath + suit_file;

    rank = SDL_LoadBMP(rankpath.c_str());
    if (rank == nullptr) {
        std::cout << "rank SDL_LoadBMP Error: " << rankpath << SDL_GetError() << std::endl;
    }

    suit = SDL_LoadBMP(suitpath.c_str());
        if (suit == nullptr) {
        std::cout << "suit SDL_LoadBMP Error" << suitpath << SDL_GetError() << std::endl;
    }
}

Card::~Card() {
    SDL_FreeSurface(rank);
    SDL_FreeSurface(suit);
}

/******************
 *  Summary: Get the base path of our resource files
 *
 *  Description: Get the path of resources located in bin/res.
 *
 *  Parameter(s):
 *      subDir - optional sub-directory name if res contains sub-directories
 */
std::string Card::GetResourcePath(const std::string &subDir) {
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

int Card::GetValue() {
    return value;
}

SDL_Surface* Card::GetRank() {
    return rank;
}

SDL_Surface* Card::GetSuit() {
    return suit;
}