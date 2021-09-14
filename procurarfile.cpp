#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <string>

std::vector<std::string> lista_de_pgns(const char *path)
{
    std::vector<std::string> pgns;//Vetor que contem os nomes dos pgns
    int tamanho_pgns = 0; // Tamanho do Vetor "pgns"
    int tamanho_pgns_i = 0; //Tamanho da string contida no vetor "pgns" no indice "i"

    struct dirent *arquivoE;
    DIR *diretorio = opendir(path);//Pointeiro para o diretorio

    if (diretorio == NULL)//Se nao tem nada no diretorio
    {
        return pgns;
    }
    
    //Caso Tenha Algo No Diretorio
    int i = 0;
    while((arquivoE= readdir(diretorio)) != NULL)
    {
        pgns.push_back(arquivoE->d_name); //Nome do Arquivo colocado no vetor de string
        tamanho_pgns = pgns.size();       //Tamanho do vetor de strings
        tamanho_pgns_i = pgns[i].size();  //Tamanho do nome do arquivo
        
        if(tamanho_pgns_i >= 4)//menor arquivo possivel e ".pgn"
        {
            if(pgns[i].substr(tamanho_pgns_i-3, 3) == "pgn")//Se o arquivo tiver "pgn" no final, nao retiramos tiramos do vetor
            {
                i++;
            }
            else//Caso contrario
            {
                pgns.pop_back();
                i = tamanho_pgns-1;    
            }
        }
        else//Se o nome do arquivo tiver um tamanho menor que 4, retiramos do vetor
        {
            pgns.pop_back();
            i = tamanho_pgns-1; 
        }
    }

    closedir(diretorio);
    return pgns;
}