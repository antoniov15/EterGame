﻿#include <iostream>
#include "Game.h"
#include "GameBoard.h"
#include "Player.h"

Game::Game(int boardSize, const std::string& player1Name, const std::string& player2Name,
    const Wizard& wizard1, const Wizard& wizard2)
    : board(boardSize),
    player1(player1Name, wizard1), // Asociază vrăjitorul 1 jucătorului 1
    player2(player2Name, wizard2), // Asociază vrăjitorul 2 jucătorului 2
    currentPlayer(1) {
    initializePlayers();
}

void Game::resetGame() {
    board = GameBoard(board.getSize()); // Resetează tabla
    player1.wizard.resetGame();
    player2.wizard.resetGame();
    currentPlayer = 1; // Opțional, setăm primul jucător
}

void Game::start() {
    while (true) {
        while (true) {
            board.printBoard();
            Player& activePlayer = (currentPlayer == 1) ? player1 : player2;

            // oponent
            Player& opponent = (currentPlayer == 1) ? player2 : player1;

            // Utilizarea abilitatii vrajitorului
            std::cout << activePlayer.name << ", do you want to use your wizard's ability? (yes/no): ";
            std::string choice;
            std::cin >> choice;

            while (choice != "yes" && choice != "no") {
                std::cout << "Invalid input! Please answer 'yes' or 'no': ";
                std::cin >> choice;
            }

            

}

void Game::validateInput(int& row, int& col) {
    while (true) {
        std::cout << "Enter row and column (0-" << board.getSize() - 1 << "): ";
        if (std::cin >> row >> col && row >= 0 && row < board.getSize() && col >= 0 && col < board.getSize()) {
            break;
        }
        else {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear(); // Curăță eroarea
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignoră restul liniei
        }
    }
}

void Game::validateCardIndex(int& index, const Player& player) {
    while (index < 0 || index >= player.hand.size()) {
        std::cout << "Invalid card index! Enter a valid index (1-" << player.hand.size() << "): ";
        std::cin >> index;
        index -= 1; // Ajustează indexul pentru a începe de la 0
    }
}

void Game::initializePlayers() {
    for (int i = 0; i < 2; ++i) {
        player1.addCard(Card(1));
    }

    for (int i = 0; i < 2; ++i) {
        player2.addCard(Card(1));
    }

    for (int i = 0; i < 2; ++i) {
        player1.addCard(Card(2));
    }

    for (int i = 0; i < 2; ++i) {
        player2.addCard(Card(2));
    }

    player1.addCard(Card(3, true));  // Iluzie
    player2.addCard(Card(3, true));  // Iluzie
}

bool Game::placeIllusion(Player& activePlayer, GameBoard& board) {
    if (activePlayer.hasPlacedIllusion) {
        std::cout << "You have already placed an Illusion this game!\n";
        return false; // Jucătorul nu poate plasa altă iluzie
    }

    std::cout << "Enter the row and column to place the illusion: ";
    int row, col;
    std::cin >> row >> col;

    try {
        if (board.placeCard(row, col, Card(1, true, false, activePlayer.name), activePlayer)) {
            activePlayer.hasPlacedIllusion = true; // Marchează utilizarea iluziilor
            return true; // Plasarea a fost reușită
        }
        else {
            std::cout << "Invalid move. Cannot place an illusion there.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return false; // Plasarea a eșuat
}

bool Game::placeNormalCard(Player& activePlayer, GameBoard& board, Player& opponent) {
    std::cout << activePlayer.name << "'s turn. Select row and column (e.g., 1 1): ";
    int row, col;
    std::cin >> row >> col;

    std::cout << "Select card index from hand (1-" << activePlayer.hand.size() << "): ";
    int cardIndex;
    std::cin >> cardIndex;
    cardIndex -= 1; // Ajustare pentru vectorul intern

    if (cardIndex < 0 || cardIndex >= activePlayer.hand.size()) {
        std::cout << "Invalid card index!\n";
        return false;
    }

    Card card = activePlayer.hand[cardIndex];

    try {
        if (board.placeCard(row, col, card, activePlayer)) {
            activePlayer.removeCard(cardIndex); // Elimină cartea din mână

            // Verificare regulă iluzie
            if (card.isIllusion && board.checkIllusionRule(row, col, opponent)) {
                std::cout << "Illusion revealed! Opponent's turn ends.\n";
            }
            return true; // Plasarea a fost reușită
        }
        else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return false; // Plasarea a eșuat
}


