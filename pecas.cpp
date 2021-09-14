#include "infos_e_jogadas.h"
#include "pecas.h"

std::vector<std::vector<char>> peao(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Tamanho do Tabuleiro
    int tamanho_tabuleiro = tabuleiro.size();

    //Uso Para Ver Se Tem Ambiguidade
    int tamanho_jogada = jogada.size();
    
    char peao;//Peca
    int inicio_peao = 0; //Lugar Inicial Do Peao tem a condicao especial de poder mover 2 casas no ao sair desse inicio (Linha inicial)
    int moveu = 0; //Checa se ocorreu um movimento e interrompe os loops

    //Se Dois Peoes Puderem Ir Pro Mesmo Lugar
    //O Que pode ocorrer caso eles possam comer a mesma peca
    int ambiguidade = 0;

    //Se O Peao Se Transforma Em Outra Peca
    int transforma = 0;
    char transformacao_peao = '\0';

    //Como os peoes tem 2 orientacoes
    //Os brancos vao ser a positiva, ou seja, linha_atual - proxima_linha > 0
    //Os pretos a negativa, ou seja, linha_atual - proxima_linha < 0
    int multiplicador = 0;
    
    //Depedendo Da Cor (Branco ou Preto) Escolhe Um Char
    if(branco_ou_preto == BRANCO)
    {
        peao = 'p';
        inicio_peao = 6;
        multiplicador = 1;
    }
    if(branco_ou_preto == PRETO)
    {
        peao = 'P';
        inicio_peao = 1;
        multiplicador = -1;
    }

    //Retorna Linha e Coluna Da Peca em Numeros Para Usar Na Matriz Do Tabuleiro
    //Funcao Presente em "infos_e_jogadas.cpp"
    std::vector<int> destino_peca = destino_da_peca(jogada);

    //Vendo Se A Jogada Possui Ambiguidade e se o Peao Transforma
    for(int i = 0; i < tamanho_jogada; i++)
    {
        //Vendo se tem ambiguidade na jogada (duas letras minusculas => jogada[i] -> coluna que a peca estava, jogada[i+1] -> coluna que a peca vai)
        // de 49 ate 57, ficam as letras [a,b,c,d,e,f,g,h], que sao as colunas do tabuleiro 
        if((jogada[i] - '0' >= 49 && jogada[i] - '0' <= 57)  && (jogada[i+1] - '0' >= 49 && jogada[i+1] - '0' <= 57))
        {
            ambiguidade = 1;
        }

        //Vendo Se O Peao Se Transforma Em Outra Peca
        //de 17 ate 42, ficam as letras Maiusculas, que representam as pecas, inclui todas as letras Maiusculas(de A ate Z) 
        if(jogada[i] == '=' && (jogada[i+1] - '0' >= 17 && jogada[i+1] - '0' <= 42))
        {
            transforma = 1;
            transformacao_peao = jogada[i+1];
        }
    }

    //REGRA DO PEAO
    for(int linha = 0; linha < tamanho_tabuleiro; linha++) //Indo Por Linhas
    {
        for(int coluna = 0; coluna < tamanho_tabuleiro; coluna++) //Indo Por Colunas
        {
            if(tabuleiro[linha][coluna] == peao)//Encontrou um Peao
            {
                //Caso O peao esteja na posicao inicial
                //Peao pode mover 2 casas na posicao inicial
                if(linha == inicio_peao)
                {
                    //Se ele nao comer a peca 
                    if(tabuleiro[destino_peca[0]][destino_peca[1]] == '\0')
                    {
                        //Testa para ver se ele obedece as regras do peao
                        //Diferenca entre linhas tem que ser no maximo 2
                        //Primeiro testo se o peao se move apenas uma casa vertical se estiver indo pro destino
                        if(linha - destino_peca[0] == 1*multiplicador && coluna - destino_peca[1] == 0) 
                        {
                            //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                            //E troca o '\0' no destino por 'p' ou 'P'
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = peao;
                            moveu++;
                        }

                        //Se nao moveu uma casa , testo se o peao se moveu duas casas verticais
                        if(linha - destino_peca[0] == 2*multiplicador && coluna - destino_peca[1] == 0 && moveu == 0)
                        {
                            //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                            //E troca o '\0' no destino por 'p' ou 'P'
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = peao;
                            moveu++;
                        }
                    }

                    //Se ele comer a peca quando estiver na posicao inicial
                    else
                    {
                        //Se tiver ambiguidade
                        if(ambiguidade != 0)
                        {
                            int linha_antiga = 0;
                            //Localizacao da coluna no vetor, pois sempre e ex: "Rhe6", sendo h a coluna que a torre estava
                            //Funcao Presente em "infos_e_jogadas.cpp"
                            int coluna_antiga = coluna_ambiguidade(jogada[1]); //Localizacao da coluna na vetor, pois sempre e ex: "Rhe6", sendo h a coluna que a torre estava
                            for(int i = 0; i < tamanho_tabuleiro; i++)//Indo pelas Linhas
                            {
                                //Quando For Um Peao
                                if(tabuleiro[linha_antiga][coluna_antiga] == peao)
                                {
                                    //Testa para ver se ele obedece as regras do peao
                                    if(linha_antiga - destino_peca[0] == 1*multiplicador && abs(coluna_antiga - destino_peca[1]) == 1 && moveu == 0) 
                                    {
                                        //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                                        //E troca a peca inimiga no destino por 'p' ou 'P'
                                        tabuleiro[linha_antiga][coluna_antiga] = '\0';
                                        tabuleiro[destino_peca[0]][destino_peca[1]] = peao;
                                        moveu++;
                                        break;
                                    }
                                }
                                linha_antiga++;
                            }
                        }
                        //Caso Contrario (Nao tenha Ambiguidade)
                        else
                        {
                            //Testa para ver se ele obedece as regras do peao
                            if(linha - destino_peca[0] == 1*multiplicador && abs(coluna - destino_peca[1]) == 1 && moveu == 0) 
                            {
                                //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                                //E troca a peca inimiga no destino por 'p' ou 'P'
                                tabuleiro[linha][coluna] = '\0';
                                tabuleiro[destino_peca[0]][destino_peca[1]] = peao;
                                moveu++;
                                break;
                            }
                        }
                    }
                }
                    
                else//Caso Nao esteja na posicao inicial
                {

                    //Se ele nao comer a peca 
                    if(tabuleiro[destino_peca[0]][destino_peca[1]] == '\0')
                    {
                        //Testa para ver se ele obedece as regras do peao
                        //diferenca entre linhas igual a 1, move apenas verticalmente
                        if(linha - destino_peca[0] == 1*multiplicador && coluna - destino_peca[1] == 0 && moveu == 0) 
                        {
                            //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                            //E troca o '\0' no destino por 'p' ou 'P'
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = peao;
                            moveu++;
                        }
                        
                        //Como ele nao esta na posicao inicial, ele pode sofrer transformacao
                        //Caso chegue no final do tabuleiro,ou seja, no pgn tera uma parte escrita "=Q"
                        //Sendo o char depois do "=" a peca que o peao se transforma
                        if(transforma == 1)
                        {
                            if(branco_ou_preto == BRANCO)
                            {
                                //Traduz as pecas para portugues, menos Q(Rainha) e K(Rei), pois ambos comecam com R
                                //Funcao Presente em "infos_e_jogadas.cpp"
                                //As Pecas Do Branco Sao Minusculas
                                tabuleiro[destino_peca[0]][destino_peca[1]] = tolower(peca_ptbr(transformacao_peao));     
                            }
                            if(branco_ou_preto == PRETO)
                            {
                                //Traduz as pecas para portugues, menos Q(Rainha) e K(Rei), pois ambos comecam com R
                                //Funcao Presente em "infos_e_jogadas.cpp"
                                //As Pecas Do Preto Sao Maiusculas
                                tabuleiro[destino_peca[0]][destino_peca[1]] = peca_ptbr(transformacao_peao);     
                            }    
                        }
                    }

                    //Se ele comer a peca
                    else
                    {
                        //Se tiver ambiguidade
                        if(ambiguidade != 0)
                        {
                            int linha_antiga = 0;
                            //Localizacao da coluna no vetor, pois sempre e ex: "Rhe6", sendo h a coluna que a torre estava
                            //Funcao Presente em "infos_e_jogadas.cpp"
                            int coluna_antiga = coluna_ambiguidade(jogada[1]); //Localizacao da coluna na vetor, pois sempre e ex: "Rhe6", sendo h a coluna que a torre estava
                            for(int i = 0; i < tamanho_tabuleiro; i++)//Indo pelas Linhas
                            {
                                //Quando For Um Peao
                                if(tabuleiro[linha_antiga][coluna_antiga] == peao)
                                {
                                    //Testa para ver se ele obedece as regras do peao
                                    if(linha_antiga - destino_peca[0] == 1*multiplicador && abs(coluna_antiga - destino_peca[1]) == 1 && moveu == 0) 
                                    {
                                        //Testa Para Ver se ele muda de coluna, ja que ele esta comendo uma peca
                                        if(coluna_antiga != destino_peca[1])
                                        {
                                            //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                                            //E troca a peca inimiga no destino por 'p' ou 'P'
                                            tabuleiro[linha_antiga][coluna_antiga] = '\0';
                                            tabuleiro[destino_peca[0]][destino_peca[1]] = peao;

                                            //Se alem de comer ele transforma
                                            if(transforma == 1)
                                            {
                                                if(branco_ou_preto == BRANCO)
                                                {
                                                    //Traduz as pecas para portugues, menos Q(Rainha) e K(Rei), pois ambos comecam com R
                                                    //Funcao Presente em "infos_e_jogadas.cpp"
                                                    //As Pecas Do Branco Sao Minusculas
                                                    tabuleiro[destino_peca[0]][destino_peca[1]] = tolower(peca_ptbr(transformacao_peao));     
                                                }
                                                if(branco_ou_preto == PRETO)
                                                {
                                                    //Traduz as pecas para portugues, menos Q(Rainha) e K(Rei), pois ambos comecam com R
                                                    //Funcao Presente em "infos_e_jogadas.cpp"
                                                    //As Pecas Do Preto Sao Maiusculas
                                                    tabuleiro[destino_peca[0]][destino_peca[1]] = peca_ptbr(transformacao_peao);     
                                                }    
                                            }
                                            break;
                                        }
                                    }
                                }
                                linha_antiga++;
                            }
                        }
                        
                        //Caso Contrario (Nao tenha Ambiguidade)
                        else
                        {
                            //Testa para ver se ele obedece as regras do peao
                            if(linha - destino_peca[0] == 1*multiplicador && abs(coluna - destino_peca[1]) == 1 && moveu == 0) 
                            {
                                //Se Obedecer Essa Regra, troca 'p'ou 'P' por um '\0'
                                //E troca a peca inimiga no destino por 'p' ou 'P'
                                tabuleiro[linha][coluna] = '\0';
                                tabuleiro[destino_peca[0]][destino_peca[1]] = peao;
                                moveu++;

                                //Se ele move e transforma
                                if(transforma == 1)
                                {
                                    if(branco_ou_preto == BRANCO)
                                    {
                                        //Traduz as pecas para portugues, menos Q(Rainha) e K(Rei), pois ambos comecam com R
                                        //Funcao Presente em "infos_e_jogadas.cpp"
                                        //As Pecas Do Branco Sao Minusculas
                                        tabuleiro[destino_peca[0]][destino_peca[1]] = tolower(peca_ptbr(transformacao_peao));     
                                    }
                                    if(branco_ou_preto == PRETO)
                                    {
                                        //Traduz as pecas para portugues, menos Q(Rainha) e K(Rei), pois ambos comecam com R
                                        //Funcao Presente em "infos_e_jogadas.cpp"
                                        //As Pecas Do Preto Sao Maiusculas
                                        tabuleiro[destino_peca[0]][destino_peca[1]] = peca_ptbr(transformacao_peao);     
                                    }    
                                }
                            }
                        }
                    }
                }
                
            }
            if(moveu == 1)break;
        }
        if(moveu == 1)break; //Se moveu a peca interrompe o loop
    }
    //FALTA O UPGRADE E MOSTRAR CHEQUE ETC ....
    return tabuleiro;
}

std::vector<std::vector<char>> cavalo(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Tamanho do Tabuleiro
    int tamanho_tabuleiro = tabuleiro.size();

    //Uso Para Ver Se Tem Ambiguidade
    int tamanho_jogada = jogada.size();

    char cavalo;//Peca
    int moveu = 0; //Checa se ocorreu um movimento e interrompe os loops

    //O Que pode ocorrer caso dois cavalos possam comer a mesma peca
    int ambiguidade = 0;
    
    //Depedendo Da Cor Escolhe Um Char
    if(branco_ou_preto == BRANCO)cavalo = 'c';
    if(branco_ou_preto == PRETO)cavalo = 'C';
    
    //Retorna Linha e Coluna Da Peca em Numeros Para Usar Na Matriz Do Tabuleiro
    //Funcao Presente em "infos_e_jogadas.cpp"
    std::vector<int> destino_peca = destino_da_peca(jogada);

    //VENDO SE TEM AMBIGUIDADE
    for(int i = 0; i < tamanho_jogada; i++)
    {
        //Vendo se tem ambiguidade na jogada (duas letras minusculas => jogada[i] -> coluna que a peca estava, jogada[i+1] -> coluna que a peca vai)
        if( (jogada[i] - '0' >= 49 && jogada[i] - '0' <= 57) && (jogada[i+1] - '0' >= 49 && jogada[i+1] - '0' <= 57))
        {
            ambiguidade = 1;
        }
    }

    //Caso Tenha Ambiguidade
    if(ambiguidade != 0)
    {
        int linha_antiga = 0;
        //Localizacao da coluna no vetor, pois sempre e ex: "Rhe6", sendo h a coluna que a torre estava
        //Funcao Presente em "infos_e_jogadas.cpp"
        int coluna_antiga = coluna_ambiguidade(jogada[1]);
        for(int i = 0; i < tamanho_tabuleiro; i++)//Indo pelas Linhas
        {
            //Como E Uma Jogada Valida, Nao Preciso Checar Se ele obedece as regras
            if(tabuleiro[linha_antiga][coluna_antiga] == cavalo)
            {
                //Troca 'c'ou 'C' por um '\0'
                //E troca a peca inimiga ou '\0' no destino por 'c' ou 'C'
                tabuleiro[linha_antiga][coluna_antiga] = '\0';
                tabuleiro[destino_peca[0]][destino_peca[1]] = cavalo;
                break;   
            }
            linha_antiga++;
        }
    }
    else//Se Apenas Tiver Uma Opcao de Cavalo
    {
        //REGRAS DO CAVALO
        for(int linha = 0; linha < tamanho_tabuleiro; linha++)//Indo Pelas Linhas
        {
            for(int coluna = 0; coluna < tamanho_tabuleiro; coluna++)//Indo Pelas Colunas
            {
                if(tabuleiro[linha][coluna] == cavalo)//Se Encontrar Um Cavalo
                {
                    //Testa para ver se ele obedece as regras do cavalo
                    if(abs(linha - destino_peca[0]) + abs(coluna - destino_peca[1]) == 3)
                    {
                        //Limitando o Cavalo a mover apenas 1 ou 2 casas na direcao horizontal(Um Tipo De L)
                        //E 2 ou 1 cada na direcao vertical
                        if( abs(linha - destino_peca[0]) == 2 && abs(coluna - destino_peca[1]) == 1)
                        {
                            //Troca 'c'ou 'C' por um '\0'
                            //E troca a peca inimiga ou '\0' no destino por 'c' ou 'C'  
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = cavalo;
                            moveu++;
                        }
                        
                        //Se nao moveu na jogada anterior, temos mais uma opcao(Outro Tipo De L)
                        if( abs(linha - destino_peca[0]) == 1 && abs(coluna - destino_peca[1]) == 2 && moveu == 0)
                        {
                            //Troca 'c'ou 'C' por um '\0'
                            //E troca a peca inimiga ou '\0' no destino por 'c' ou 'C'
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = cavalo;
                            moveu++;
                        }      
                    }
                }
            }
            if(moveu == 1)break;
        }
    }
    return tabuleiro;
}

std::vector<std::vector<char>> bispo(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Tamanho do Tabuleiro
    int tamanho_tabuleiro = tabuleiro.size();

    char bispo;//Peca
    int moveu = 0; //Checa se ocorreu um movimento e interrompe os loops
    
    //Depedendo Da Cor Escolhe Um Char
    if(branco_ou_preto == BRANCO)bispo = 'b';
    if(branco_ou_preto == PRETO)bispo= 'B';
    

    //Um Bispo Que Esta Em Uma Cor So Pode Mover Para Um Lugar Que Pertence A Mesma Cor
    //Nao Adaptei esse metodo caso o peao se transforme em bispo
    //Nao ocorre essa transformacao em nenhum dos jogos (jogo01.pgn,jogo02.pgn e jogo03.pgn)
    // 'b' = QUADRADO BRANCO, 'p' = QUADRADO PRETO
    std::vector<std::vector<char>> cores_tabuleiro
    {
        {'b','p','b','p','b','p','b','p'},
        {'p','b','p','b','p','b','p','b'},
        {'b','p','b','p','b','p','b','p'},
        {'p','b','p','b','p','b','p','b'},
        {'b','p','b','p','b','p','b','p'},
        {'p','b','p','b','p','b','p','b'},
        {'b','p','b','p','b','p','b','p'},
        {'p','b','p','b','p','b','p','b'},  
    };

    //Retorna Linha e Coluna Da Peca em Numeros Para Usar Na Matriz Do Tabuleiro
    //Funcao Presente em "infos_e_jogadas.cpp"
    std::vector<int> destino_peca = destino_da_peca(jogada);
    
    //REGRAS DO BISPO
    for(int linha = 0; linha < tamanho_tabuleiro; linha++)//Indo Pelas Linhas
    {
        for(int coluna = 0; coluna < tamanho_tabuleiro; coluna++)//Indo Pelas Colunas
        {
            if(tabuleiro[linha][coluna] == bispo)//Se Encontrar Um Bispo
            {
                //Se A Cor For A Mesma
                if(cores_tabuleiro[linha][coluna] == cores_tabuleiro[destino_peca[0]][destino_peca[1]])
                {
                    //Troca 'b'ou 'B' por um '\0'
                    //E troca a peca inimiga ou '\0' no destino por 'b' ou 'B'
                    tabuleiro[linha][coluna] = '\0';
                    tabuleiro[destino_peca[0]][destino_peca[1]] = bispo;
                    moveu++;
                }
            }
        }
        if(moveu == 1)break;
    }
    return tabuleiro;
}

std::vector<std::vector<char>> torre(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Tamanho do Tabuleiro
    int tamanho_tabuleiro = tabuleiro.size();

    //Uso Para Ver Se Tem Ambiguidade
    int tamanho_jogada = jogada.size();

    char torre;//Peca
    int moveu = 0; //Checa se ocorreu um movimento e interrompe os loops

    //O Que pode ocorrer caso duas torres possam comer a mesma peca
    int ambiguidade = 0;

    //Depedendo Da Cor Escolhe Um Char
    if(branco_ou_preto == BRANCO)torre = 't';
    if(branco_ou_preto == PRETO)torre = 'T';
    
    //Retorna Linha e Coluna Da Peca em Numeros Para Usar Na Matriz Do Tabuleiro
    //Funcao Presente em "infos_e_jogadas.cpp"
    std::vector<int> destino_peca = destino_da_peca(jogada);

    for(int i = 0; i < tamanho_jogada; i++)
    {
        //Vendo se tem ambiguidade na jogada (duas letras minusculas => jogada[i] -> coluna que a peca estava, jogada[i+1] -> coluna que a peca vai)
        if( (jogada[i] - '0' >= 49 && jogada[i] - '0' <= 57) && (jogada[i+1] - '0' >= 49 && jogada[i+1] - '0' <= 57))
        {
            ambiguidade = 1;
        }
    }
    if(ambiguidade != 0)
    {
        int linha_antiga = 0;
        //Localizacao da coluna no vetor, pois sempre e ex: "Rhe6", sendo h a coluna que a torre estava
        //Funcao Presente em "infos_e_jogadas.cpp"
        int coluna_antiga = coluna_ambiguidade(jogada[1]);
        for(int i = 0; i < tamanho_tabuleiro; i++)//Indo pelas Linhas
        {
            if(tabuleiro[linha_antiga][coluna_antiga] == torre)
            {
                //Troca 't'ou 'T' por um '\0'
                //E troca a peca inimiga ou '\0' no destino por 't' ou 'T'
                tabuleiro[linha_antiga][coluna_antiga] = '\0';
                tabuleiro[destino_peca[0]][destino_peca[1]] = torre;
                break;
            }
            linha_antiga++;
        }
    }
    else//Se Apenas Tiver Uma Opcao de Torre
    {
        for(int linha = 0; linha < tamanho_tabuleiro; linha++)//Indo Pelas Linhas
        {
            for(int coluna = 0; coluna < tamanho_tabuleiro; coluna++)//Indo Pelas Colunas
            {
                if(tabuleiro[linha][coluna] == torre)//Se Encontrar Uma Torre
                {
                    //Limitando a Torre a Mover So Na Horizontal Ou Vertical
                    //Torre andando Somente Na Vertical
                    if(abs(linha - destino_peca[0]) > 0 && coluna - destino_peca[1] == 0)
                    {
                        int peca_no_caminho = 0;
                        //Dependendo Da Ordem, se ele vai de cima para baixo ou de baixo para cima
                        //O multiplicador Inverte as Operacoes De Acordo;
                        int multiplicador = 0;
                        if(linha - destino_peca[0] > 0)multiplicador = 1;//De Cima Para Baixo
                        if(linha - destino_peca[0] < 0)multiplicador = -1;//De Baixo Para Cima
                        //Checando se nao tem alguma peca no caminho da coluna
                        for(int k = 0; k < (linha - destino_peca[0])*multiplicador ; k++)
                        {
                            if(branco_ou_preto == BRANCO)
                            {
                                //Se a Peca Nao for um '\0' ou uma Letra Minuscula(PECA BRANCA)
                                if(tabuleiro[linha+(-k-1)*multiplicador][coluna] != '\0' && tabuleiro[linha+(-k-1)*multiplicador][coluna]  - '0' > 42)peca_no_caminho++;
                            }
                            if(branco_ou_preto == PRETO)
                            {
                                //Se a Peca Nao for um '\0' ou uma Letra Maiscula (PECA PRETA)
                                if(tabuleiro[linha+(-k-1)*multiplicador][coluna]  != '\0' && tabuleiro[linha+(-k-1)*multiplicador][coluna]  - '0' < 42)peca_no_caminho++;
                            }
                            if(peca_no_caminho != 0)break;
                        }
                        //Se nao tiver nenhuma peca, jogada valida
                        if(peca_no_caminho == 0)
                        {
                            //Troca 't'ou 'T' por um '\0'
                            //E troca a peca inimiga ou '\0' no destino por 't' ou 'T'
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = torre;
                            moveu++;
                        }
                    }
                    //Se nao moveu na jogada anterior, temos mais uma opcao (MOVENDO NA HORIZONTAL)
                    if(linha - destino_peca[0] == 0 && abs(coluna - destino_peca[1]) > 0 && moveu == 0)
                    {
                        int peca_no_caminho = 0;
                        //Dependendo Da Ordem, se ele vai da direita para a esquerda ou da esquerda para a direita
                        //O multiplicador Inverte as Operacoes De Acordo
                        int multiplicador = 0;
                        if(coluna - destino_peca[1] > 0)multiplicador = 1;//Da Direita Para A Esqueda
                        if(coluna - destino_peca[1] < 0)multiplicador = -1;//Da Esquerda Para A Direita
                        //Checando se nao tem alguma peca no caminho da linha
                        for(int k = 0 ; k < (coluna - destino_peca[1])*multiplicador; k++)
                        {
                            if(branco_ou_preto == BRANCO)
                            {
                                //Se a Peca Nao for um '\0' ou uma Letra Minuscula(PECA BRANCA)
                                if(tabuleiro[linha][coluna + (- k - 1)*multiplicador] != '\0' && tabuleiro[linha][coluna+(- k - 1)*multiplicador] - '0' > 42)peca_no_caminho++;
                            }
                            if(branco_ou_preto == PRETO)
                            {
                                //Se a Peca Nao for um '\0' ou uma Letra Maiscula (PECA PRETA)
                                if(tabuleiro[linha][coluna + (- k - 1)*multiplicador] != '\0' && tabuleiro[linha][coluna + (- k - 1)*multiplicador] - '0' < 42)peca_no_caminho++;
                            }
                    
                            if(peca_no_caminho != 0)break;
                        }
                        //Se nao tiver nenhuma peca, jogada valida
                        if(peca_no_caminho == 0)
                        {
                            //Troca 't'ou 'T' por um '\0'
                            //E troca a peca inimiga ou '\0' no destino por 't' ou 'T'
                            tabuleiro[linha][coluna] = '\0';
                            tabuleiro[destino_peca[0]][destino_peca[1]] = torre;
                            moveu++;
                        }
                    }        
                }
            }
            if(moveu == 1)break;
        }
    }
    return tabuleiro;
}

std::vector<std::vector<char>> rainha(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Tamanho do Tabuleiro
    int tamanho_tabuleiro = tabuleiro.size();

    char rainha;//Peca
    int moveu = 0; //Checa se ocorreu um movimento e interrompe os loops
    
    //Depedendo Da Cor Escolhe Um Char
    if(branco_ou_preto == BRANCO)rainha = 'q';
    if(branco_ou_preto == PRETO)rainha = 'Q';
    
    //Retorna Linha e Coluna Da Peca em Numeros Para Usar Na Matriz Do Tabuleiro
    //Funcao Presente em "infos_e_jogadas.cpp"
    std::vector<int> destino_peca = destino_da_peca(jogada);

    for(int linha = 0; linha < tamanho_tabuleiro; linha++)//Indo Pelas Linhas
    {
        for(int coluna= 0; coluna < tamanho_tabuleiro; coluna++)//Indo Pelas Colunas
        {
            if(tabuleiro[linha][coluna] == rainha)//Se Encontrar Uma Rainha
            {
                //Rainha anda N casas, mas como as jogadas ja sao validas, apenas precisamos achar a rainha
                //E move-la para a casa dada
                //E como tem apenas uma Rainha, nao temos ambiguidade 
                //Nao fiz o casa que o peao se transforma em rainha
                //Nos jogos (jogo01.pgn,jogo02.pgn e jogo03.pgn) nao temos essas transformacoes
                //Troca 'q'ou 'Q' por um '\0'
                //E troca a peca inimiga ou '\0' no destino por 'q' ou 'Q'
                tabuleiro[linha][coluna] = '\0';
                tabuleiro[destino_peca[0]][destino_peca[1]] = rainha;
                moveu++;
            }
        }
        if(moveu == 1)break;
    }
    return tabuleiro;
}

std::vector<std::vector<char>> rei(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Tamanho do Tabuleiro
    int tamanho_tabuleiro = tabuleiro.size();

    char rei; //Peca
    int moveu = 0; //Checa se ocorreu um movimento e interrompe os loops
    
    //Depedendo Da Cor Escolhe Um Char
    if(branco_ou_preto == BRANCO)rei = 'k';
    if(branco_ou_preto == PRETO)rei = 'K';
    
    //Retorna Linha e Coluna Da Peca em Numeros Para Usar Na Matriz Do Tabuleiro
    //Funcao Presente em "infos_e_jogadas.cpp"
    std::vector<int> destino_peca = destino_da_peca(jogada);

    for(int linha = 0; linha  < tamanho_tabuleiro; linha++)//Indo Pelas Linhas
    {
        for(int coluna = 0; coluna < tamanho_tabuleiro; coluna++)//Indo Pelas Colunas
        {
            if(tabuleiro[linha][coluna] == rei)//Se Encontrar Um Rei
            {
                if(abs(linha - destino_peca[0]) == 0 && abs(coluna - destino_peca[1]) == 1)
                {
                    //Rei so anda apenas uma casa em qualquer ocasiao
                    //E como tem apenas um Rei, nao temos ambiguidade
                    //Troca 'k'ou 'K' por um '\0'
                    //E troca a peca inimiga ou '\0' no destino por 'k' ou 'K' 
                    tabuleiro[linha][coluna] = '\0';
                    tabuleiro[destino_peca[0]][destino_peca[1]] = rei;
                    moveu++;
                }
                if(abs(linha - destino_peca[0]) == 1 && abs(coluna - destino_peca[1]) == 0)
                {
                    //Rei so anda apenas uma casa em qualquer ocasiao
                    //E como tem apenas um Rei, nao temos ambiguidade
                    //Troca 'k'ou 'K' por um '\0'
                    //E troca a peca inimiga ou '\0' no destino por 'k' ou 'K'  
                    tabuleiro[linha][coluna] = '\0';
                    tabuleiro[destino_peca[0]][destino_peca[1]] = rei;
                    moveu++;
                }
                if(abs(linha - destino_peca[0]) == 1 && abs(coluna - destino_peca[1]) == 1)
                {
                    //Rei so anda apenas uma casa em qualquer ocasiao
                    //E como tem apenas um Rei, nao temos ambiguidade
                    //Troca 'k'ou 'K' por um '\0'
                    //E troca a peca inimiga ou '\0' no destino por 'k' ou 'K'  
                    tabuleiro[linha][coluna] = '\0';
                    tabuleiro[destino_peca[0]][destino_peca[1]] = rei;
                    moveu++;
                }
            }
        }
        if(moveu == 1)break;
    }
    return tabuleiro;
}

std::vector<std::vector<char>> roque_menor(int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Roques sao jogadas padroes, entao as pecas tem estar naquele local exato
    //Como Estou Lendo Um Jogo Entao Todos os Roques Sao Validos
    //Tamanho do Tabuleiro
    char roque_menor;

    //Depedendo Da Cor Escolhe Uma Opcao
    if(branco_ou_preto == BRANCO)roque_menor = BRANCO;
    if(branco_ou_preto == PRETO)roque_menor = PRETO;
    
    if(roque_menor == BRANCO)
    {
        tabuleiro[7][7] = '\0';//Removendo A Torre
        tabuleiro[7][4] = '\0';//Removendo O Rei
        
        tabuleiro[7][5] = 't';//Movendo A Torre
        tabuleiro[7][6] = 'k';//Movendo O Rei
    }
    if(roque_menor == PRETO)
    {
        tabuleiro[0][7] = '\0';//Removendo A Torre
        tabuleiro[0][4] = '\0';//Removendo O Rei
        
        tabuleiro[0][5] = 'T';//Movendo A Torre
        tabuleiro[0][6] = 'K';//Movendo O Rei
    }
    return tabuleiro;
}

std::vector<std::vector<char>> roque_maior(int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Roques sao jogadas padroes, entao as pecas tem estar naquele local exato
    //Como Estou Lendo Um Jogo Entao Todos os Roques Sao Validos
    //Tamanho do Tabuleiro
    char roque_maior;
    
    //Depedendo Da Cor Escolhe Uma Opcao
    if(branco_ou_preto == BRANCO)roque_maior = BRANCO;
    if(branco_ou_preto == PRETO)roque_maior = PRETO;
    

    if(roque_maior == BRANCO)
    {
        tabuleiro[7][0] = '\0';//Removendo A Torre
        tabuleiro[7][4] = '\0';//Removendo O Rei
        
        tabuleiro[7][3] = 't';//Movendo A Torre
        tabuleiro[7][2] = 'k';//Movendo O Rei
    }
    if(roque_maior == PRETO)
    {
        tabuleiro[0][0] = '\0';//Removendo A Torre
        tabuleiro[0][4] = '\0';//Removendo O Rei
        
        tabuleiro[0][3] = 'T';//Movendo A Torre
        tabuleiro[0][2] = 'K';//Movendo O Rei
    }
    return tabuleiro;
}

std::vector<std::vector<char>>  Move_Peca(std::string jogada, int branco_ou_preto, std::vector<std::vector<char>> tabuleiro)
{
    //Funcao Para Chamar as Outras Funcoes que Movem As Pecas
    //Depende Do Char Inicial de cada jogada 
    if(jogada[0] == 'P')tabuleiro = peao(jogada,branco_ou_preto,tabuleiro);
    if(jogada[0] == 'N')tabuleiro = cavalo(jogada,branco_ou_preto,tabuleiro);
    if(jogada[0] == 'B')tabuleiro = bispo(jogada,branco_ou_preto,tabuleiro);
    if(jogada[0] == 'R')tabuleiro = torre(jogada,branco_ou_preto,tabuleiro);
    if(jogada[0] == 'Q')tabuleiro = rainha(jogada,branco_ou_preto,tabuleiro);
    if(jogada[0] == 'K')tabuleiro = rei(jogada,branco_ou_preto,tabuleiro);
    if(jogada == "O-O")tabuleiro = roque_menor(branco_ou_preto,tabuleiro);
    if(jogada == "O-O-O")tabuleiro = roque_maior(branco_ou_preto,tabuleiro);
    
    return tabuleiro; 
}