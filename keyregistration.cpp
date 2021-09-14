#include "keyregistration.h"
//Isso E Do Meu Jogo Por Isso Esta Em Ingles (Vou Colocar No Github)
// Screen/Button Registration in Initial Menus
int keyregistration()//Gets keyboard input
{
    int key = 0;    
    
    key = getch();//Key input

    //Enter Value = 13
    if(key != 13)
    {
        if(key  == 87 || key == 119){key = UP;return key;}//"W" Key Value
        if(key  == 83 || key == 115){key = DOWN;return key;} //"S" Key Value
        if(key  == 65 || key == 97){key = LEFT;return key;} //"A" Key Value
        if(key  == 68 || key == 100){key = RIGHT;return key;} //"D" Key Value
        return 0;
    }
    else
    {
        key = ENTER;
        return key;
    }
}