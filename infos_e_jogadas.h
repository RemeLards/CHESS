#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <conio.h>
#include <cctype>

#ifndef INFO_JOGADAS_H
#define INFO_JOGADAS_H


std::vector<std::vector<std::string>> v_linhas_arquivo(std::string arquivo);//Faz o processo de checar se o arquivo abriu, e retorna as jogadas 

std::vector<std::vector<std::string>> info_e_jog(std::vector<std::string> v_linhas);//Retorna as informacoes iniciais e as jogadas

int coluna_ambiguidade(char coluna);//Coluna que remove a ambiguidade

char peca_ptbr(char peca);//Traducao da peca

std::vector<int> coluna_linha(char coluna, char linha);//Retorna Linha E Coluna Da Jogada

std::vector<int> destino_da_peca(std::string jogada);//Retorna Peca,Linha,Coluna, E O Que Ocorreu tudo em numeros


#endif