# OBS
Use o CMD em tela cheia, para caber tudo do programa 
# Controles
W -> Seleciona Opcao a Frente.
S -> Seleciona Opcao a Baixo.
D -> Seleciona Opcao a Direita.
S -> Seleciona Opcao a Esquerda.
ENTER -> Confirma a Opcao.

# Menus

## Menu Inicial (O que contem o tabuleiro)
E Possivel Apenas Selecionar Opcoes para a esquerda e para a direita.
 
### Opcao 1 (Proximo Movimento Ou Reiniciar)
Apos apertar ENTER mostra a proxima jogada (caso tenha algum jogo seleciona ou executado junto com o .exe).
Apos A Ultima Jogada Essa Opcao Se Torna A Opcao De Reiniciar O Jogo,  
fazendo com que o tabuleiro volte ao seu estado de comeco de partida, e a Opcao Volta A Ser Proximo Movimento

### Opcao 2 (Retornar Um Movimento)
Apos apertar ENTER mostra o tabuleiro/jogada anterior (caso tenha ocorrido ao menos uma jogada).

### Opcao 3 (Escolha Um Jogo)
Opcao Que Leva O Usuario Para O Menu de Arquivos / Menu File


### Opcao 4 (Sai Do Programa)
Sai Do Programa

## Menu de Arquivos / Menu File (O que contem as opcoes de selecionar os arquivos)
Mostra todos os arquivos .pgn presentes na pasta do arquivo .exe
E Possivel Apenas Selecionar Opcoes para baixo e para cima.
Apos apertar ENTER em um arquivo .pgn executa ele no tabuleiro do menu opcional

### Opcao Final (Voltar)
Retorna Para O Menu Inicial e Mantem O Jogo e O Tabuleiro Antigo

# Codigo para Compilar O Programa
g++ pecas.cpp infos_e_jogadas.cpp procurarfile.cpp menutrab.cpp keyregistration.cpp filemenu.cpp trabalhoprog1.cpp -o trabalhoprog1 -Wall 