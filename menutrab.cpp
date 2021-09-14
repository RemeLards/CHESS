#include "menustrab.h"
//Construtor

//inicializa as variáveis
IMenu::IMenu(std::vector<std::vector<std::string>> infos_e_jogadas) :options_selection(0),options_size(0),tamanho_infos_e_jogadas_class(0),n_jogada(0)
{
    int size_vetor_informacoes_e_jogadas = infos_e_jogadas.size();
    //Guarda o tamanho de vetor infos_e_jogadas na classe IMenu
    SetSizeInfoJogadas(size_vetor_informacoes_e_jogadas);

    //Dependendo do tamanho do vetor infos_e_jogadas
    if(tamanho_infos_e_jogadas_class > 0)
    {
        std::vector<std::string> infos = infos_e_jogadas[0];
        std::vector<std::string> jogadas = infos_e_jogadas[1];
        //Guarda o vetor contendo as informacoes na classe IMenu
        IMenu::SetInfos(infos);
        //Guarda o vetor contendo as jogadas na classe IMenu
        IMenu::SetJogadas(jogadas);
        //Guarda o Tabuleiro inicial no vetor "todos_tabuleiros"
        IMenu::SetTabuleiro();
        //Inicializa o Menu Interativo
        IMenu::InitialMenu();
    }
    else
    {
        //Guarda o Tabuleiro inicial no vetor "todos_tabuleiros"
        IMenu::SetTabuleiro();
        //Inicializa o Menu Interativo
        IMenu::InitialMenu();   
    }    
}

//Destrutor
//Nao executa, pois uso exit(0) caso o usuario escolha sair
IMenu::~IMenu()//Mudar depois
{
    std::cout << "Obrigado por usar nosso programa!!! " << std::endl;
}

//Setters
void IMenu::SetTabuleiro()
{
    //Tabuleiro Inicial
    todos_tabuleiros.push_back(tabuleiro_inicial);
}
void IMenu::SetInfos(std::vector<std::string> infos)
{
    //Guarda o vetor contendo as informacoes na classe IMenu
    infos_class = infos;
}
void IMenu::SetJogadas(std::vector<std::string> jogadas)
{
    //Guarda o vetor contendo as jogadas na classe IMenu
    jogadas_class = jogadas;
}
void IMenu::SetSizeInfoJogadas(int size_vetor_informacoes_e_jogadas)
{
    //Guarda o tamanho de vetor infos_e_jogadas na classe IMenu
    tamanho_infos_e_jogadas_class = size_vetor_informacoes_e_jogadas;
}

//###############
//Menus e Prints
//###############

//Menu Inicial
void IMenu::InitialMenu()
{
    std::vector <std::string> Options {"Proximo Movimento", "Retornar Um Movimento","Escolha Um Jogo","Sair"}; // Opções do menu inicial
    int options_selection = 0; //Vai de 0 a 3, devido as opções acima
    int options_size = Options.size();
    int tamanho_jogadas = jogadas_class.size();
    //Guarda Numero da jogada antiga, se ela foi a primeira(0), ou a segunda(1)
    //Uso para fazer a primeira opcao do menu alternar entre "Reiniciar" e "Proximo Movimento"
    //Caso o Usuario escolha rever a penultima jogada.
    int n_jogada_antiga = 0;

    while(1)
    {
        IMenu::ChessPhrasePrint(); //Printa a Frase "Xadrez"
        IMenu::BoardPrint(); //Printa O Tabuleiro
        //Possibilita A Utilizacao Do Menu com a Opcao Reiniciar
        if(n_jogada == tamanho_jogadas-1 && n_jogada_antiga == tamanho_jogadas-2)n_jogada++;
        if(n_jogada == tamanho_jogadas)
        {
            Options = {"Reiniciar", "Retornar Um Movimento","Escolha Um Jogo","Sair"};
        };
        //Caso Reinicie O Jogo Ou Volte Um Movimento Apos A Ultima Jogada
        if(n_jogada == 0 || n_jogada == tamanho_jogadas-1)
        { 
            Options =  {"Proximo Movimento", "Retornar Um Movimento","Escolha Um Jogo","Sair"};
        }
        IMenu::InitialMenu_OptionsPrint(Options,options_selection,options_size);//Printa As Opcoes Do Menu Inicial 
        IMenu::ControlsPrint(); //Printa Os Controles
        IMenu::InitialMenu_OptionsKeyRegistration(Options,options_selection,options_size);//Registra Os Botoes
        tamanho_jogadas = jogadas_class.size();
        //Permite no final conseguir fazer o menu Proximo Movimento Aparecer
        //Caso O Usuario deseje retornar uma jogada atras
        n_jogada_antiga = n_jogada;
    } 
}

//Prints Do Menu Inicial
//Printando A Frase "Xadrez"
void IMenu::ChessPhrasePrint()
{
    //Limpo O Cmd E Printo Tudo Comecando Pelo Nome "Xadrez"
    system("cls");
    std::cout << "===============================================================================" << std::endl;
    std::cout << "#               ________     _______        _____      ________     _______   #" << std::endl;
    std::cout << "#   \\    /     |        |    |      \\      |     |     |                  /   #"<< std::endl;
    std::cout << "#    \\  /      |        |    |       \\     |_____|     |                 /    #"<< std::endl;
    std::cout << "#     \\/       |________|    |        \\    |     \\     |________        /     #"<< std::endl;
    std::cout << "#     /\\       |        |    |        |    |      \\    |               /      #"<< std::endl;
    std::cout << "#    /  \\      |        |    |        |    |       \\   |              /       #"<< std::endl;
    std::cout << "#   /    \\     |        |    |________|    |        \\  |________     /______  #"<< std::endl;
    std::cout << "===============================================================================" << std::endl;
}

//Printando O Tabuleiro
void IMenu::BoardPrint()
{
    int coluna_tabuleiro = 0;
    int linha_tabuleiro = 0;
    int flip = 0; //Inicializando Todas as Variaveis

    //Uso para mostrar algumas informacoes do lado do tabuleiro
    int tamanho_todos_tabuleiros = todos_tabuleiros.size();
    
    if(tamanho_todos_tabuleiros > 0)
    {
        //Printando As Letras Acima Do Tabuleiro (Nao Coloquei No "for" Para Ficar Mais Simples)
        std::cout<<"                                                        "<<std::endl;
        std::cout<<"   A      B      C      D      E      F      G      H   "<<std::endl;
        std::cout<<"                                                        "<<std::endl;


        for(int i = 0; i < 8; i++)// Printa As Linhas
        {
            if(i%2 == 0)flip = 1;//Comeca Com Branco Se O Numero "i" For Par
            if(i%2 == 1)flip = 0;//Comeca Com Preto Se O Numero "i" For Impar

            for(int j = 0; j < 3; j++) //Printa O Comprimento Dos Quadrados 
            {
                for(int k = 0; k < 8; k++) //Printa A Largura Dos Quadrados
                {
                    for(int l = 0; l < 7; l++) //Printa Os Caracteres 7 vezes, e contem o algoritmo de quando printar um retangulo branco ou printar ' ' nada no cmd
                    {
                        if(j != 1)//Nao Printa As Pecas De Xadrez, Pois Nao E O Meio Do Quadrado, Printa Somente Os Caracteres
                        {
                            if(flip == 1)//Se O "i" For Par
                            {
                                if(k%2 == 0)//Printa O Caracter 219 Da Tabela ASCII (Retangulo Branco)
                                {
                                    std::cout << (char)219;
                                }
                                if(k%2 == 1)//Printa O Caracter Espaco ' ' 
                                {
                                    std::cout << ' ';
                                }
                            }
                            if(flip == 0)//Se O "i" For Impar
                            {
                                if(k%2 == 1)//Printa O Caracter 219 Da Tabela ASCII (Retangulo Branco)
                                {
                                    std::cout << (char)219;
                                }
                                if(k%2 == 0)//Printa O Caracter Espaco ' '
                                {
                                    std::cout << ' ';
                                }
                            }  
                        }
                        
                        else// Se "j = 1" Imprimimos As Peca De Xadrez, Entao usamos uma logica diferente
                        {
                            if(flip == 1)//Se O "i" For Par
                            {
                                if(k%2 == 0)//Printa O Caracter 219 Da Tabela ASCII (Retangulo Branco)
                                {
                                    if(l == 3)//No Centro Do Respectivo Quadrado
                                    {
                                        //Se o char do tabuleiro for diferente do '\0' printamos a peca de xadrez
                                        if(todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro] != '\0')std::cout <<todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro];
                                        //Se o char do tabuleiro for o '\0' printamos o caracter do quadrado correspondente
                                        else std::cout << (char)219; 
                                    }
                                    else std::cout << (char)219;
                                }
                                if(k%2 == 1)//Printa O Caracter Espaco ' '
                                {
                                    if(l == 3)//No Centro Do Respectivo Quadrado
                                    {
                                        //Se o char do tabuleiro for diferente do '\0' printamos a peca de xadrez
                                        if(todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro]!= '\0')std::cout <<todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro];
                                        //Se o char do tabuleiro for o '\0' printamos o caracter do quadrado correspondente
                                        else std::cout << ' '; 
                                    }
                                    else std::cout << ' ';
                                }
                            }
                            if(flip == 0)//Se O "i" For Impar
                            {
                                if(k%2 == 1)//Printa O Caracter 219 Da Tabela ASCII (Retangulo Branco)
                                {
                                    if(l == 3)//No Centro Do Respectivo Quadrado
                                    {
                                        //Se o char do tabuleiro for diferente do '\0' printamos a peca de xadrez
                                        if(todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro] != '\0')std::cout <<todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro];
                                        //Se o char do tabuleiro for o '\0' printamos o caracter do quadrado correspondente
                                        else std::cout << (char)219; 
                                    }
                                    else std::cout << (char)219;
                                }
                                if(k%2 == 0)//Printa O Caracter Espaco ' '
                                {
                                    if(l == 3)//No Centro Do Respectivo Quadrado
                                    {
                                        //Se o char do tabuleiro for diferente do '\0' printamos a peca de xadrez
                                        if(todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro] != '\0')std::cout <<todos_tabuleiros[tamanho_todos_tabuleiros-1][linha_tabuleiro][coluna_tabuleiro];
                                        //Se o char do tabuleiro for o '\0' printamos o caracter do quadrado correspondente
                                        else std::cout << ' '; 
                                    }
                                    else std::cout << ' ';
                                }
                            }  
                        }
                    }
                    if(j == 1)//Printa os Numeros Dos Tabuleiro e Informacoes (Event,Black,White,....)
                    {
                        coluna_tabuleiro++; //Indo para proximo elemento da matriz "tabuleiro", So Aumenta quando "j = 1",que e quando usariamos o "for" para printar as pecas
                        if(k == 7)
                        {
                            std::cout <<"      "<< 8-linha_tabuleiro; //Printando O Numero Da Linha No Tabuleiro
                            if(tamanho_infos_e_jogadas_class > 0)//Se o cara colocou um replay de um jogo atraves do ".pgn"
                            {
                                if(i == 0)std::cout << "     " << "Preto: " <<infos_class[11]; //Do jeito que eu fiz o Nome do "Black" sempre sera o indice 11
                                if(i == 1)std::cout << "     " << "Evento: " <<infos_class[1]; //Do jeito que eu fiz o Nome do "Event" sempre sera o indice 1
                                if(i == 2)std::cout << "     " << "Local: " <<infos_class[3]; //Do jeito que eu fiz o Nome do "Site" sempre sera o indice 3
                                if(i == 3)std::cout << "     " << "Data: " <<infos_class[5]; //Do jeito que eu fiz o Nome do "Date" sempre sera o indice 5
                                if(i == 4)std::cout << "     " << "Partida: " <<infos_class[7]; //Do jeito que eu fiz o Nome do "Round" sempre sera o indice 7
                                if(i == 5)
                                {
                                    //Do jeito que eu fiz o Nome do "Result" sempre sera o indice 13
                                    std::cout << "     " << "Resultado: ";
                                    if(infos_class[13] == "1/2-1/2")std::cout << "Empate";
                                    if(infos_class[13] == "1-0")std::cout << "Brancas Venceram";
                                    if(infos_class[13] == "0-1")std::cout << "Pretas Venceram";
                                }
                                if(i == 6)std::cout << "     " << "Branco: " <<infos_class[9]; //Do jeito que eu fiz o Nome do "Black" sempre sera o indice 9
                                if(i == 7)
                                {
                                    //Printa Informacoes do jogo na ultima linha do tabuleiro
                                    //Capturas e Xeques
                                    //n_jogada(numero da jogada)
                                    if(n_jogada-1 > 0)
                                    {
                                        int tamanho_jogada = jogadas_class[n_jogada-1].size();
                                        for(int i = 0; i < tamanho_jogada; i++)
                                        {
                                            //Se for Uma Captura
                                            //Printa Diferentes Frases Para Diferentes Pecas
                                            if(jogadas_class[n_jogada-1][i] == 'x')
                                            {
                                                //Funcao Presente em "infos_e_jogadas.cpp"
                                                std::vector<int> destino_peca = destino_da_peca(jogadas_class[n_jogada-1]);

                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'P')std::cout<< "     "  << "Peao Preto";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'p')std::cout<< "     "  << "Peao Branco";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'C')std::cout<< "     "  << "Cavalo Preto";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'c')std::cout<< "     "  << "Cavalo Branco";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'B')std::cout<< "     "  << "Bispo Preto";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'b')std::cout<< "     "  << "Bispo Branco";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'T')std::cout<< "     "  << "Torre Preta";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 't')std::cout<< "     "  << "Torre Branca";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'Q')std::cout<< "     "  << "Rainha Preta";
                                                if(todos_tabuleiros[tamanho_todos_tabuleiros-2][destino_peca[0]][destino_peca[1]] == 'q')std::cout<< "     "  << "Rainha Branca";
                                                std::cout << " Capturado";
                                            }
                                            //Se For um Xeque
                                            if(jogadas_class[n_jogada-1][i] == '+')
                                            {
                                                //Quando Acha um Xeque Fala em Qual Rei Ocorre
                                                if((n_jogada-1)%2 == 0)std::cout<< "     "  << "Xeque No Rei Preto";
                                                if((n_jogada-1)%2 == 1)std::cout<< "     "  << "Xeque No Rei Branco";
                                            }
                                            //Se for um Xeque-Mate
                                            if(jogadas_class[n_jogada-1][i] == '#')
                                            {
                                                //Quando Acha um Xeque-Mate Fala em Qual Rei Ocorre
                                                if((n_jogada-1)%2 == 0)std::cout<< "     "  << "Xeque-Mate No Rei Preto";
                                                if((n_jogada-1)%2 == 1)std::cout<< "     "  << "Xeque-Mate No Rei Branco";
                                            }
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
                }
                std::cout<<std::endl;
            }
            coluna_tabuleiro = 0;//Zeramos A Coluna Para Comecar No Primeiro Elemento Da Segunda Linha
            linha_tabuleiro++;//Indo para proxima linha da matriz "tabuleiro"
        }
        std::cout << std::endl << std::endl;
    }
}

//Printando as opções e dando a sensação do usuário conseguir selecionar a opção.
void IMenu::InitialMenu_OptionsPrint(std::vector <std::string> Options, int options_selection, int options_size)
{
    int options_size_i = 0;//Tamanho da string contida nas opcoes
    for(int i = 0; i < options_size; i++)//Printa os delimitadores em cima
    {
        options_size_i = Options[i].size(); 
        if(i == options_selection)
        {
            for(int j = 0; j < options_size_i+2; j++) std::cout <<"="; //Printando a quantidade de "=" necessaria para caber na palavra/string, coloquei o +2 pois estava sobrando um espaço
        }
        else
        {
            for(int j = 0; j < options_size_i; j++) std::cout <<" ";//Pular a quantidade necessaria dependendo do tamanho da palavra
            std::cout << "                 ";//Pular o espaço que deixei entre as palavras
        }
             
    }
    options_size_i= 0; //Para evitar erros
    
    std::cout << std::endl; //Pula uma linha para delimitar
    
    for(int i = 0; i < options_size; i++)//Printa a Opcao
    {
        if(i == options_selection)std::cout <<"|";
        std::cout << Options[i];
        if(i == options_selection)std::cout <<"|";
        std::cout << "                 ";
    }
    
    std::cout << std::endl; //Pula uma linha para delimitar
    
    for(int i = 0; i < options_size; i++)//Printa os delimitadores embaixo;
    {
        options_size_i = Options[i].size();    
        if(i == options_selection)
        {
            for(int j = 0; j < options_size_i+2; j++) std::cout <<"="; //Printando a quantidade de "=" necessaria para caber na palavra/string, coloquei o +2 pois estava sobrando um espaço
        }
        else
        {
            for(int j = 0; j < options_size_i; j++) std::cout <<" ";//Pular a quantidade necessaria dependendo do tamanho da palavra
            std::cout << "                 ";//Pular o espaço que deixei entre as palavras
        }
    }
    options_size_i= 0; //Para evitar erros

    std::cout << std::endl << std::endl << std::endl; //Pula Linha Para Printar Os Controles Que O Usuário Pode Usar No Programa
    
}

//Printa Os Controles Que o Usuário Pode Usar
void IMenu::ControlsPrint()
{
    std::cout <<"CONTROLES: " << std::endl << std::endl;
    std::cout <<" \"W\" -> Seleciona A Opcao Para Cima";
    std::cout <<"                                  ";
    std::cout <<"       \"S\" -> Seleciona A Opcao Para Baixo" << std::endl << std::endl;

    std::cout <<" \"A\" -> Seleciona A Opcao Para A Esquerda";
    std::cout <<"                                  ";
    std::cout <<" \"D\" -> Seleciona A Opcao Para A Direita";
    std::cout <<"                                  ";
    std::cout <<" \"ENTER\" -> Confirma A Opcao" << std::endl << std::endl;
}

//###################
//Funcionalidades
//###################

//Registra Os Botões Que O Usuario Aperta
void IMenu::InitialMenu_OptionsKeyRegistration(std::vector<std::string> Options,int &options_selection, int options_size)
{
    //Funcao Presente em "keyregistration.cpp"
    int key = keyregistration();
    if(key == LEFT)options_selection -= 1;    //Se o usuario pressionar para Esquerda (tecla "A")
    if(key == RIGHT)options_selection += 1;  //Se o usuario pressionar para Direita (tecla "D")
    if(key == ENTER)
    {
        //Primeira Opcao(Verdadeiro ate executar a ultima jogada)
        if(options_selection == options_size-4 && Options[0] == "Proximo Movimento")
        {
            int tamanho_jogadas = jogadas_class.size();
            //Checo O Tamanho Jogadas para ver se ele nao e um vetor Nulo
            //Caso o Usuario inicie sem jogo algum o tamanho dele e 0
            if(tamanho_jogadas > 0 && n_jogada < tamanho_jogadas)
            {
                int tamanho_todos_tabuleiros = todos_tabuleiros.size();
                //Serve Para Saber quem executou aquela jogada
                //Brancos sempre sao as jogadas 0,2,4,6,8,.....
                //Pretos sempre sao as jogadas 1,3,5,7,9,......
                int branco_ou_preto;
                if(n_jogada%2 == BRANCO)branco_ou_preto = BRANCO;
                if(n_jogada%2 == PRETO)branco_ou_preto = PRETO;
                //Guardo O Novo Tabuleiro No Vetor De Tabuleiros
                //O Novo Tabuleiro Contem O Movimento Atual
                //Faco Isso pois caso o usuario resolva voltar uma jogada, nao preciso calcula-la
                //E Caso eu retorne ela o n_jogada(numero da jogada) acompanha essa volta
                //Logo caso eu precise mostrar a proxima jogada apos um retorno, o numero da jogada corresponde a jogada que o tabuleiro mostra
                //Funcao "Move_Peca" Presente em "pecas.cpp"
                todos_tabuleiros.push_back(Move_Peca(jogadas_class[n_jogada],branco_ou_preto,todos_tabuleiros[tamanho_todos_tabuleiros-1]));
                n_jogada++;
            }
        }
        //Primeira Opcao(Verdadeiro apos a ultima jogada)
        if(options_selection == options_size-4 && Options[0] == "Reiniciar")
        {
            //Se o Usuario Reinicia eu 0 o numero da jogada pois ela volta pro inicio
            n_jogada = 0;
            //Excluo Todos os tabuleiros antigos
            todos_tabuleiros.clear();
            //Adiciono o Tabuleiro Inicial
            SetTabuleiro();
        }
        if(options_selection == options_size-3)
        {
            int tamanho_todos_tabuleiros = todos_tabuleiros.size();
            //Se o Tabuleiro nao for o inicial
            if(tamanho_todos_tabuleiros > 1 && n_jogada > 0)
            {
                //Excluo O Tabuleiro Da Ultima Jogada
                todos_tabuleiros.pop_back();
                //Volto Uma Jogada
                n_jogada--;
            }
        }
        if(options_selection == options_size-2)//Ultima Opcao (sair)
        {
            IMenu::NovoJogo();//Menu Para Escolher Outro Programa
        }
        if(options_selection == options_size-1)//Ultima Opcao (sair)
        {
            exit(0);//Sair do programa
        }
    }
    if(options_selection < 0)options_selection = options_size-1; //Se O Opcao Ficar Negativa, Vai Para A Opcao Final
    if(options_selection >= options_size)options_selection = 0; //Se A Opcao Ficar Maior Do que o numero de Opcoes, Ele Volta Para O Inicio
}

//Coloca o novo jogo que o usuario escolheu, a nao ser que ele escolheu retornar

void IMenu::NovoJogo()
{
    FMenu n_jogo;//novo jogo
    //Metodo Presente em "filemenu.cpp"
    int opcao =  n_jogo.FileMenu();//Retorna a opcao que o usuario escolheu
    std::string jogo = n_jogo.pgns_class[opcao];//Pega a string que o usuario escolheu   

    if(jogo != "Voltar")//Se o usuario escolheu qualquer opcao que nao seja "Voltar"
    {
        std::vector<std::vector<std::string>> infos_e_jogadas;

        //"v_linhas_arquivo" pois ele retornava o vetor com as linhas do arquivo pgn em cada indice
        //Porem mudei, e agora ele retorna as informacoes e jogadas ,Mas Nao tenho um nome melhor 
        //Funcao Presente em "infos_e_jogadas.cpp"
        infos_e_jogadas = v_linhas_arquivo(jogo);//Como existe o arquivo ".pgn", abrimos e pegamos as informacoes
        
        int tamanho_infos_e_jogadas = infos_e_jogadas.size();//Se o tamanho for !=0, foi possivel abrir o arquivo, e continua com o jogo antigo
        
        SetSizeInfoJogadas(tamanho_infos_e_jogadas);//Se abriu o ".pgn" seu tamanho sera 2, caso nao consiga abrir, seu tamanho sera 0

        //Se Conseguiu Abrir O Arquivo PGN Corretamente
        if(tamanho_infos_e_jogadas == 2)
        {
            //Guarda o vetor contendo as informacoes na classe IMenu
            infos_class = infos_e_jogadas[0];
            //Guarda o vetor contendo as jogadas na classe IMenu
            jogadas_class = infos_e_jogadas[1];
            //Zera O Numero Da Jogada
            n_jogada = 0;
            //Limpa O Vetor Contendo Todos Os Tabuleiros
            todos_tabuleiros.clear();
            //Adiciona o Tabuleiro Inicial Ao Vetor Contendo Todos Os Tabuleiros
            SetTabuleiro();
        }
        //Se Nao Conseguiu Abrir O Arquivo PGN Corretamente
        else
        {
            std::cout << std::endl;
            std::cout << "O seu jogo nao pode ser aberto" << std::endl;
            std::cout << "O programa vai continuar com o jogo antigo, aperte qualquer tecla para continuar" << std::endl;
            getch();
        } 
    }
}