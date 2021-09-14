#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "procurarfile.h"
#include "infos_e_jogadas.h"
#include "keyregistration.h"
#include "pecas.h"

#ifndef MENU_H
#define MENU_H


class IMenu
{
    public:

       //Construtores e Destrutores
       IMenu(std::vector<std::vector<std::string>>);
       ~IMenu();

       //Setters
       void SetTabuleiro();
       void SetInfos(std::vector<std::string> infos);
       void SetJogadas(std::vector<std::string> jogadas);
       void SetSizeInfoJogadas(int size_vetor_informacoes_e_jogadas);
       void SetSizeJogadas(int size_vetor_jogadas);
       
       //Menus
       void InitialMenu();

       //Prints Do Menu Inicial
       void ChessPhrasePrint();
       void BoardPrint(); //A Fazer;
       void InitialMenu_OptionsPrint(std::vector<std::string> Options, int options_selection, int options_size);
       void ControlsPrint();

       
       //Registrando Keyboard Input
       void InitialMenu_OptionsKeyRegistration(std::vector <std::string> Options ,int &options_selection, int options_size);

       //Muda de partida depois que o usuario seleciona algum ".pgn" no menu de opcoes de pgn
       void NovoJogo();

    private:
        int options_selection;
        int options_size;
        int tamanho_infos_e_jogadas_class;
        int n_jogada;
        std::vector<std::vector<char>> tabuleiro_inicial
        {
            {'T','C','B','Q','K','B','C','T'},
            {'P','P','P','P','P','P','P','P'},
            {'\0','\0','\0','\0','\0','\0','\0','\0'},
            {'\0','\0','\0','\0','\0','\0','\0','\0'},
            {'\0','\0','\0','\0','\0','\0','\0','\0'},
            {'\0','\0','\0','\0','\0','\0','\0','\0'},
            {'p','p','p','p','p','p','p','p'},
            {'t','c','b','q','k','b','c','t'},  
        };
        std::vector<std::vector<std::vector<char>>> todos_tabuleiros;
        std::vector<std::string> infos_class; 
        std::vector<std::string> jogadas_class;   
};

class FMenu //Menu de Files, quando o usuario nao coloca uma ele tem opcao de escolher
{
    public:

        //Construtores e Destrutores
        FMenu();
        ~FMenu();

        //Menu
        int FileMenu();

        //Prints do FileMenu
        void FileMenu_OptionsPrint(int options_selection);

        //Registrando Keyboard Input
        int FileMenu_OptionsKeyRegistration(int &options_selection);


    private:
        std::vector<std::string> pgns_class;
        friend IMenu;
};
#endif
