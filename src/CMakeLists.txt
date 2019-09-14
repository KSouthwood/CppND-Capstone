project(CppND-Capstone)
add_executable(blackjack
                main.cpp
                Renderer.cpp
                DeckOfCards.cpp
                Card.cpp
                Controller.cpp
)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(blackjack ${SDL2_LIBRARIES})
install(TARGETS blackjack RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
