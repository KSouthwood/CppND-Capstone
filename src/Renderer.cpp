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
 *  Description: Create our window and renderer.
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
void Renderer::Render(std::vector<int> dealer, std::vector<int> player, DeckOfCards deck, bool show) {
    const std::string res_path = GetResourcePath();

    // clear the window and fill with green background
    SDL_SetRenderDrawColor(renderer, col_bkgrd.r, col_bkgrd.g, col_bkgrd.b, col_bkgrd.a); // set to green
    SDL_RenderClear(renderer);

    // draw the badges
    SDL_SetRenderDrawColor(renderer, col_badge.r, col_badge.g, col_badge.b, col_badge.a);

    SDL_RenderFillRect(renderer, &box_dealer);
    SDL_Texture *he_one = LoadTexture(res_path + "Dealer.bmp");
    SDL_RenderCopy(renderer, he_one, NULL, &box_dealer);

    SDL_RenderFillRect(renderer, &box_player);
    SDL_Texture *he_two = LoadTexture(res_path + "Player.bmp");
    SDL_RenderCopy(renderer, he_two, NULL, &box_player);

    SDL_RenderFillRect(renderer, &choice_one);
    SDL_Texture *ch_one = LoadTexture(res_path + "Hit.bmp");
    SDL_RenderCopy(renderer, ch_one, NULL, &choice_one);

    SDL_RenderFillRect(renderer, &choice_two);
    SDL_Texture *ch_two = LoadTexture(res_path + "Stand.bmp");
    SDL_RenderCopy(renderer, ch_two, NULL, &choice_two);

    SDL_SetRenderDrawColor(renderer, col_card.r, col_card.g, col_card.b, col_card.a); // set to white

    // draw the dealers hand
    for (int i = 0; i < (int)dealer.size(); i++) {
        SDL_RenderFillRect(renderer, &d_pos[i]);
        // skip drawing the first card if it's not face up
        if (!(i == 0 && show == false)) {
            SDL_Texture *rank = SDL_CreateTextureFromSurface(renderer, deck.shoe[dealer[i]]->GetRank());
            SDL_Texture *suit = SDL_CreateTextureFromSurface(renderer, deck.shoe[dealer[i]]->GetSuit());
            SDL_Rect rect_rank = {.x = 30 + (i * 120), .y = 100, .w = 40, .h = 40};
            SDL_Rect rect_suit = {.x = 30 + (i * 120), .y = 140, .w = 40, .h = 40};
            SDL_RenderCopy(renderer, rank, NULL, &rect_rank);
            SDL_RenderCopy(renderer, suit, NULL, &rect_suit);
        }
    }

    // draw the players hand
    for (int i = 0; i < (int)player.size(); i++) {
        SDL_RenderFillRect(renderer, &p_pos[i]);
        SDL_Texture *rank = SDL_CreateTextureFromSurface(renderer, deck.shoe[player[i]]->GetRank());
        SDL_Texture *suit = SDL_CreateTextureFromSurface(renderer, deck.shoe[player[i]]->GetSuit());
        SDL_Rect rect_rank = {.x = 30 + (i * 120), .y = 340, .w = 40, .h = 40};
        SDL_Rect rect_suit = {.x = 30 + (i * 120), .y = 380, .w = 40, .h = 40};
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

/******************
 *  Summary: Get the base path of our resource files
 *
 *  Description: Get the path of resources located in bin/res.
 *
 *  Parameter(s):
 *      subDir - optional sub-directory name if res contains sub-directories
 */
std::string Renderer::GetResourcePath(const std::string &subDir) {
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

/******************
 *  Summary: Load a texture to a renderer
 *
 *  Description: Takes a file from supplied filename and loads it into the
 *      renderer.
 *
 *  Parameter(s):
 *      subDir - optional sub-directory name if res contains sub-directories
 */
SDL_Texture* Renderer::LoadTexture(const std::string &file) {
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
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
