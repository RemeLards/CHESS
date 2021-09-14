#ifndef MOVE_PECA_H
#define MOVE_PECA_H
#include "infos_e_jogadas.h"
enum ORDEM
{
    BRANCO = 0,
    PRETO,
};
std::vector<std::vector<char>> peao(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> cavalo(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> bispo(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> torre(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> rainha(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> rei(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> roque_menor(int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>> roque_maior(int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);
std::vector<std::vector<char>>  Move_Peca(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro);

#endif