#include "menustrab.h"
#include "infos_e_jogadas.h"
#include "procurarfile.h"

int main(int argc, char* argv[])
{
    if(argc > 1) //Se tiver mais que a string do ".exe"
    {
        std::vector<std::string> jogos;//Armazena todos os nomes de arquivos ".pgn" existentes como string  
        jogos = lista_de_pgns(".");//Acessando A Pasta que o ".exe" esta

        int tamanho_jogos = jogos.size();//Tamanho do vetor jogos
        int encontrou = 0;//Se o arquivo ".pgn" que o usuario colocou existir na pasta/folder, o valor de encontrou sera 1

        if(tamanho_jogos == 0)//Inicializa o Menu Normalmente
        {
            std::cout << "Nao existe nenhum arquivo '.pgn' na pasta" << std::endl;
            std::cout << "O programa sera inicializado normalmente, aperte qualquer tecla para continuar" << std::endl;
            getch();
            std::vector<std::vector<std::string>> infos_e_jogadas;
            IMenu Menu(infos_e_jogadas);
        }
        else//Caso exista algum arquivo ".pgn" na pasta/folder
        {
            for(int i = 0; i < tamanho_jogos; i++)
            {
                if(jogos[i] == argv[1])//Se o arquivo existir na pasta, valor de encontrou vira 1
                {
                    encontrou ++;
                }
            }
            if(encontrou > 0)//Se o arquivo existir na pasta
            {
                std::vector<std::vector<std::string>> infos_e_jogadas;

                infos_e_jogadas = v_linhas_arquivo(argv[1]);
                int tamanho_infos_e_jogadas = infos_e_jogadas.size();//Se o tamanho for !=0, foi possivel abrir o arquivo


                if(tamanho_infos_e_jogadas > 0)//Foi possivel abrir o arquivo,inicia o Menu com o jogo que o usuario colocou 
                {
                    IMenu Menu(infos_e_jogadas);  
                }
                else//Se nao foi possivel abrir o arquivo, inicia o Menu, mas sem o jogo que o usuario colocou
                {
                    std::cout << "O seu jogo nao pode ser aberto" << std::endl;
                    std::cout << "O programa sera inicializado normalmente, aperte qualquer tecla para continuar" << std::endl; 
                    getch();
                    IMenu Menu(infos_e_jogadas); 
                }
            }
            else//Se o arquivo nao existir na pasta, Inicializa o Menu Normalmente com o aviso "nao existe/foi encontrado o arquivo ".pgn" na pasta/folder"
            {
                std::cout << "Seu jogo nao foi encontrado" << std::endl;
                std::cout << "O programa sera inicializado normalmente, aperte qualquer tecla para continuar" << std::endl;
                getch();
                std::vector<std::vector<std::string>> infos_e_jogadas;
                IMenu Menu(infos_e_jogadas); 
            }
        }

    }
    else //Caso so tenha a string com o ".exe"
    {
        std::vector<std::vector<std::string>> infos_e_jogadas;
        IMenu Menu(infos_e_jogadas); 
        //Se nao passar nenhum parametro ele inicia com o MENU INICIAL, Sem executar o jogo direto
    }
    return 0;
}