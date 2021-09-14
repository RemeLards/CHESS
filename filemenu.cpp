#include "menustrab.h"

//Construtor
//inicializa as variáveis
//Funcao "lista_de_pgns" Presente em "procurarfile.cpp"
FMenu::FMenu() : pgns_class(lista_de_pgns("."))
{
    pgns_class.push_back("Voltar"); // Opções do menu inicial
}

//Destrutor
FMenu::~FMenu()
{
}

int FMenu::FileMenu()
{
    int options_selection = 0; //Vai de 0 a "pgns_class.size() - 1", devido as opções acima, adicionar mais opções depois
    int escolheu = -1;

    while(1)
    {
        system("cls");
        FMenu::FileMenu_OptionsPrint(options_selection);//Printa As Opcoes Do Menu Inicial 
        escolheu = FMenu::FileMenu_OptionsKeyRegistration(options_selection);
        if(escolheu > -1)
        {
            return escolheu;
        }
    }  
}
//Printando as opções e dando a sensação do usuário conseguir selecionar a opção.
void FMenu::FileMenu_OptionsPrint(int options_selection)
{
    int options_size = pgns_class.size();
    int options_size_i = 0;//Tamanho da string contida nas opcoes
    for(int i = 0; i < options_size; i++)//Printa os delimitadores em cima
    {
        options_size_i = pgns_class[i].size();
        if(i == options_selection)
        {
            for(int j = 0; j < options_size_i+2; j++) std::cout <<"=";
            std::cout << std::endl;

            std::cout << '#' << pgns_class[i];

            std::cout << "#" << std::endl;
            for(int j = 0; j < options_size_i+2; j++) std::cout <<"=";
            std::cout << std::endl;
        }
        else
        {
            std::cout << '#' << pgns_class[i]<<std::endl;
        } 
    }
}
//Registra Os Botões Que O Usuario Aperta
int FMenu::FileMenu_OptionsKeyRegistration(int &options_selection)
{
    int options_size = pgns_class.size();
    //Depois traduzir, tirei do meu jogo
    int key = keyregistration();
    if(key == UP)options_selection -= 1;    //Se O Usuario Apertar "W"
    if(key == DOWN)options_selection += 1;  //Se O Usuario Apertar "S"
    if(key == ENTER)
    {
        return options_selection;
    }
    if(options_selection < 0)options_selection = options_size-1; //Se O Opcao Ficar Negativa, Vai Para A Opcao Final
    if(options_selection >= options_size)options_selection = 0; //Se A Opcao Ficar Maior Do que o numero de Opcoes, Ele Volta Para O Inicio
    return -1;
}
