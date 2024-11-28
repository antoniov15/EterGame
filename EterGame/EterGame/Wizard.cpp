﻿#include "Wizard.h"
#include <iostream>

Wizard::Wizard(const std::u8string& name, MagicPower power)
    : name(name), power(power) {
}

// Getteri
std::u8string Wizard::getName() const {
    return name;
}

// puterile
void Wizard::useAbility(GameBoard& board, int row, int col, Player& currentPlayer, int destRow, int destCol) {
    if (usedThisMatch) {
        throw std::runtime_error("The magical power has already been used this match!");
    }
    if (usedThisGame) {
        throw std::runtime_error("The magical power has already been used this game!");
    }

    usedThisGame = true;
    usedThisMatch = true;

    switch (power) {
    case MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN:
        board.removeOpponentCardOverOwn(row, col, currentPlayer);
        break;
    case MagicPower::REMOVE_ROW_WITH_OWN_CARD:
        board.removeRowWithOwnCard(row, currentPlayer);
    case MagicPower::COVER_OPPONENT_CARD:
        board.coverOpponentCard(row, col, currentPlayer);
    case MagicPower::CREATE_HOLE:
        board.createHole(row, col);
    case MagicPower::MOVE_STACK_WITH_OWN_CARD:
        if (destRow == -1 || destCol == -1) {
            throw std::runtime_error("Destination row and column must be specified for this ability!");
        }
        board.moveStackWithOwnCard(row, col, destRow, destCol, currentPlayer);
    case MagicPower::GAIN_EXTRA_CARD: {
        board.placeEtherCard(row, col, currentPlayer);
    case MagicPower::MOVE_STACK_WITH_OPPONENT_CARD:
        if (destRow == -1 || destCol == -1) {
            throw std::runtime_error("Destination row and column must be specified for this ability!");
        }
        board.moveStackWithOpponentCard(row, col, destRow, destCol, currentPlayer);
    case MagicPower::MOVE_ROW_TO_EDGE:
        if (destRow == -1 || destCol == -1) {
            throw std::runtime_error("Destination edge must be specified for this ability!");
        }
        board.moveRowToEdge(row, col, destRow, destCol);
        break;
    }
                                    break;
    default:
        throw std::runtime_error("Invalid magical power!");
    }

    std::cout << name << " used their magical power!\n";
}

void Wizard::resetGame() {
    usedThisGame = false; // Resetăm utilizarea doar pentru jocul curent
}