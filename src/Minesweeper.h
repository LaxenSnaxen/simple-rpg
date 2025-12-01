#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Minesweeper {
public:
    Minesweeper(int width, int height, int mines)
        : width(width), height(height), mines(mines) {
        BuildBoard();
        PlaceNumbers();
    }

    void BuildBoard() {
        board.assign(height, std::vector<int>(width, 0));
        PlaceMines();
    }

    void PlaceMines() {
        std::vector<sf::Vector2i> allPositions;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                allPositions.emplace_back(x, y);
            }
        }

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(allPositions.begin(), allPositions.end(), std::default_random_engine(seed));

        for (int i = 0; i < mines; i++) {
            sf::Vector2i pos = allPositions[i];
            board[pos.y][pos.x] = -1;
            BombLocations.push_back(pos);
        }
    }

    void PlaceNumbers() {
        for (const auto& bomb : BombLocations) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = bomb.x + dx;
                    int ny = bomb.y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && board[ny][nx] != -1) {
                        board[ny][nx]++;
                    }
                }
            }
        }
    }

    void renderBoard() {
        // Debug console output
        for (const auto& row : board) {
            for (int cell : row) {
                if (cell == -1)
                    std::cout << "* ";
                else
                    std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int width;
    int height;
    int mines;
    std::vector<std::vector<int>> board;
    std::vector<sf::Vector2i> BombLocations;
};
