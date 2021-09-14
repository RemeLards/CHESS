#include "infos_e_jogadas.h"

//Faz o processo de checar se o arquivo abriu, e retorna as informacoes e jogadas 
std::vector<std::vector<std::string>> v_linhas_arquivo(std::string arquivo)
{
    std::ifstream arquivoE;
    std::string linha;
    std::vector<std::string> v_linhas;

    std::vector<std::vector<std::string>> informacoes_e_jogadas;

    arquivoE.open(arquivo);//Abre o arquivo

    if(arquivoE.is_open())//Se o pgn esta aberto
    {
        while(getline(arquivoE,linha))
        {
            v_linhas.push_back(linha);//Coloca as linhas do pgn no vetor de strings, sendo cada linha um indice
        }
        arquivoE.close();
        informacoes_e_jogadas = info_e_jog(v_linhas);//Separa as o PGN em um vetor com as informacoes iniciais e um vetor com as jogadas
        return informacoes_e_jogadas;
    }
    else//Se nao foi possivel abrir o arquivo
    {
        return informacoes_e_jogadas;
        //Caso nao foi possivel abrir o arquivo, o tamanho da informacoes_e_jogadas sera 0;
    }
}

//Retorna O Vetor Contendo As Informacoes E Jogadas para a funcao "v_linhas_arquivo"
std::vector<std::vector<std::string>> info_e_jog(std::vector<std::string> v_linhas)//Retorna as informacoes iniciais e as jogadas
{
    std::vector<std::string> informacoes;
    std::vector<std::string> rodadas;
    std::vector<std::string> jogadas;

    int tamanho_v_linhas = 0;//Tamanho do vetor que contem as linhas do pgn
    int tamanho_v_linhas_i = 0;//Tamanho da string contida na linha do pgn
    
    int tamanho_rodadas = 0;//Tamanho do vetor rodadas
    int tamanho_rodadas_i = 0;//Tamanho da string contida no vetor de rodadas

    int inicio_string = 0;//Marca o Inicio da string (usado no vetor rodadas)
    int separador = 0; //Separa as informacoes inicias das jogadas

    tamanho_v_linhas = v_linhas.size();

    //Separando as informacoes
    for(int i = 0; i < tamanho_v_linhas;i++)//Linha
    {
        tamanho_v_linhas_i = v_linhas[i].size();//Tamanho Da String
        
        if(tamanho_v_linhas_i == 0)
        {
            separador = i;//Linha contendo nada no pgn (tamanho = 0)
            break;
        }
        
        for(int j = 0; j < tamanho_v_linhas_i;j++)//String Da Linha
        {      
            if(v_linhas[i][j] == '[' || (v_linhas[i][j] == '\"' && v_linhas[i][j-1] == ' '))
            {
                inicio_string = j+1;//Comeca No Caracter Apos O '[' ou apos as aspas
            }
            if((v_linhas[i][j] == ' '  && v_linhas[i][j+1] == '\"' )|| (v_linhas[i][inicio_string-1] == '\"'  && v_linhas[i][j] == ']'))
            {
                if(v_linhas[i][j] == ' '  && v_linhas[i][j+1] == '\"' )
                {
                    informacoes.push_back(v_linhas[i].substr(inicio_string,j - inicio_string));//Pegando a primeira informacao da tupla, EX: White,Round,etc      
                }
                else
                {
                    //Pegando a segunda informacao da tupla sem as aspas, EX: 1/2-1/2
                    // tem o "-1" pois ele iria incluir as aspas do final (o que nao quero), logo preciso colocar -1 no final 
                    informacoes.push_back(v_linhas[i].substr(inicio_string,j - inicio_string - 1));  
                }
                     
            }  
        }
    }
    inicio_string = 0; //Para evitar erros
    

    //Separando as Rodadas
    for(int i = separador+1; i < tamanho_v_linhas;i++)//Linha
    {
        tamanho_v_linhas_i = v_linhas[i].size();//Tamanho Da String
        
        for(int j = 0; j < tamanho_v_linhas_i;j++)//String Da Linha
        {      
            if(v_linhas[i][j] == '.')
            {
                inicio_string = j+1;//Comeca No Caracter Apos O Ponto
            }
            if((v_linhas[i][j] == ' ' && v_linhas[i][j+1] - '0' <=9 )|| j == tamanho_v_linhas_i-1)//Se for um ' ' e depois um numero, ou chegar no final da string
            {
                if(v_linhas[i][j] == ' ' && v_linhas[i][j+1] - '0' <=9)///Se for um ' ' e depois um numero
                {
                rodadas.push_back(v_linhas[i].substr(inicio_string,j-inicio_string));//Adiciona a rodada num outro vetor de string contendo as rodadas
                
                inicio_string += j-inicio_string ;//O Inicio Da String Comeca no Final Da Rodada Adicionada, fiz isso devido a um erro quando chegava na ultima rodada
                }

                else//Se chegar no final da string
                {
                rodadas.push_back(v_linhas[i].substr(inicio_string,j-inicio_string+1));//Adiciona a rodada num outro vetor de string contendo as rodadas
                
                inicio_string += j-inicio_string+1;//O Inicio Da String Comeca no Final Da Rodada Adicionada, fiz isso devido a um erro quando chegava na ultima rodada   
                }
            }
        }
    }
    inicio_string = 0; //Para evitar erros

    //Temos um problema, apos a ultima rodada o programa armazena um ' ' no penultimo indice do vetor
    //e um espaco no resultado da partida(ultimo indice do vetor). EX: " 1/2 - 1/2", sendo que não queremos o espaço inicial.
    //Mas para ficar mais facil a analise jogada a jogada, irei criar um vetor chamado "jogada", e irei
    //ir ate o antepenultimo indice do vetor rodadas
    
    tamanho_rodadas = rodadas.size();
    int qnt_espaco = 0;//Quantidade de espacos
    int t_jogadas = 0;//Tamanho do vetor jogadas, comeco de -1 pois aumento incremento +1 cada vez que adiciona uma jogada
    for(int i = 0; i < tamanho_rodadas-2; i++)//Tirando os dois ultimos vetores, como explicado acima
    {
        tamanho_rodadas_i = rodadas[i].size();//Tamanho Da String
        
        for(int j = 0; j < tamanho_rodadas_i; j++)//String Da Rodada
        {
            if(rodadas[i][j] == ' ')//Se tem Duas Jogadas
            {
                t_jogadas++; 
                jogadas.push_back(rodadas[i].substr(0,j));//Primeira Jogada da Linha
                if(jogadas[t_jogadas-1][0] - '0' >= 49)jogadas[t_jogadas-1].insert(jogadas[t_jogadas-1].begin(), 'P');//Se for um peao, adiciono o Prefixo "P"

                t_jogadas++;
                jogadas.push_back(rodadas[i].substr(j+1,tamanho_rodadas_i - (j+1)));//Segunda Jogada
                if(jogadas[t_jogadas-1][0] - '0' >= 49)jogadas[t_jogadas-1].insert(jogadas[t_jogadas-1].begin(), 'P');//Se for um peao, adiciono o Prefixo "P"
                
                qnt_espaco +=1;//Quantos ' ' foram encontrados (no caso so tem como ser 1)
            }
            if(j == tamanho_rodadas_i-1 && qnt_espaco == 0)//Se Tem Apenas Uma Jogada
            {
                t_jogadas++;
                jogadas.push_back(rodadas[i].substr(0,j+1));// Unica Jogada  
                if(jogadas[t_jogadas-1][0] - '0' >= 49)jogadas[t_jogadas-1].insert(jogadas[t_jogadas-1].begin(), 'P');//Se for um peao, adiciono o Prefixo "P"
            }
        }
        qnt_espaco = 0;
    }
    
    std::vector<std::vector<std::string>> return_informacoes_e_jogadas; //Criei esse vetor pois podemos apenas retornar uma variavel
    return_informacoes_e_jogadas.push_back(informacoes);//Colocando o Vetor de Informacoes
    return_informacoes_e_jogadas.push_back(jogadas); //Colocando o Vetor de Jogadas
    
    return return_informacoes_e_jogadas;
}

//Coluna que remove a ambiguidade
//E Faz O Programa Escolher A Peca Certa
int coluna_ambiguidade(char coluna)
{
    int coluna_peca;
    if(coluna == 'a')coluna_peca=0;
    if(coluna == 'b')coluna_peca=1;
    if(coluna == 'c')coluna_peca=2;
    if(coluna == 'd')coluna_peca=3;
    if(coluna == 'e')coluna_peca=4;
    if(coluna == 'f')coluna_peca=5;
    if(coluna == 'g')coluna_peca=6;
    if(coluna == 'h')coluna_peca=7;
    return  coluna_peca;
}

std::vector<int> linha_coluna(char coluna, char linha)//Retorna Linha E Coluna Da Jogada
{
    std::vector<int> coluna_linha_numero;
    if(linha == '1')coluna_linha_numero.push_back(7);
    if(linha == '2')coluna_linha_numero.push_back(6);
    if(linha == '3')coluna_linha_numero.push_back(5);
    if(linha == '4')coluna_linha_numero.push_back(4);
    if(linha == '5')coluna_linha_numero.push_back(3);
    if(linha == '6')coluna_linha_numero.push_back(2);
    if(linha == '7')coluna_linha_numero.push_back(1);
    if(linha == '8')coluna_linha_numero.push_back(0);
    
    if(coluna == 'a')coluna_linha_numero.push_back(0);
    if(coluna == 'b')coluna_linha_numero.push_back(1);
    if(coluna == 'c')coluna_linha_numero.push_back(2);
    if(coluna == 'd')coluna_linha_numero.push_back(3);
    if(coluna == 'e')coluna_linha_numero.push_back(4);
    if(coluna == 'f')coluna_linha_numero.push_back(5);
    if(coluna == 'g')coluna_linha_numero.push_back(6);
    if(coluna == 'h')coluna_linha_numero.push_back(7);
    

    return coluna_linha_numero;
}

std::vector<int> destino_da_peca(std::string jogada)//Retorna O Destino Da Peca No Tabuleiro
{
    std::vector<int> linha_coluna_numero;
    int tamanho_jogada = jogada.size();
    for(int i = 0; i < tamanho_jogada; i++)
    {
        //Se for uma letra e depois um numero, transforma eles em numeros em numero da coluna e linha, respectivamente
        if(jogada[i] - '0' >= 49 && jogada[i+1] - '0' <= 9) linha_coluna_numero = linha_coluna(jogada[i],jogada[i+1]);
    }

    return linha_coluna_numero;
}

//Traduz As Pecas Para Portugues
//Menos Rei e Rainha, Pois Ambos Comecam Com R
char peca_ptbr(char peca)
{
    if(peca == 'P')return peca;
    if(peca == 'N')return 'C';
    if(peca == 'B')return peca;
    if(peca == 'R')return 'T';
    //Deixei os mesmos pois Rainha e Rei os dois possuem R
    if(peca == 'Q')return peca;
    if(peca == 'K')return peca;

    return '\0';
}