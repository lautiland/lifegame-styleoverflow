#include <iostream>
#include "principal.h"
using namespace std;

void bienvenida()
{
    cout << endl
         << endl;
    cout << "       ______ _     _                              _        _               _     _       " << endl;
    cout << "      |  ____| |   (_)                            | |      | |             (_)   | |      " << endl;
    cout << "      | |__  | |    _ _   _  ___  __ _  ___     __| | ___  | | __ _  __   ___  __| | __ _ " << endl;
    cout << "      |  __| | |   | | | | |/ _ \\/ _` |/ _ \\   / _` |/ _ \\ | |/ _` | \\ \\ / / |/ _` |/ _` |" << endl;
    cout << "      | |____| |   | | |_| |  __/ (_| | (_) | | (_| |  __/ | | (_| |  \\ V /| | (_| | (_| |" << endl;
    cout << "      |______|_|   | |\\__,_|\\___|\\__, |\\___/   \\__,_|\\___| |_|\\__,_|   \\_/ |_|\\__,_|\\__,_|" << endl;
    cout << "                  _/ |            __/ |                                                   " << endl;
    cout << "                 |__/            |___/                                                    " << endl;
    cout << endl
         << endl
         << endl;
}

ModoDeJuego configurar()
{
    ModoDeJuego configuracion;
    int opcion;
    cout << "Elija una configuracion para las dimensiones del Tablero:" << endl;
    cout << "1: Configuracion manual." << endl;
    cout << "2: Tablero de 5x5x5 con estandares bajos de generacion de celulas." << endl;
    cout << "3: Tablero de 10x10x10 con estandares medios de generacion de celulas." << endl;
    cout << "4: Tablero de 20x20x20 con estandares altos de generacion de celulas." << endl
         << endl;
    cin >> opcion;
    cout << endl;

    switch (opcion)
    {
    case 1:
        configuracion = manual;
        break;
    case 2:
        configuracion = configuracion1;
        break;
    case 3:
        configuracion = configuracion2;
        break;
    case 4:
        configuracion = configuracion3;
        break;
    default:
        break;
    }
    return configuracion;
}

//------------------------>
AccionTurno preguntarTurno(Tablero *partida)
{
    int respuesta;
    cout << "Indique la accion deseada para el siguiente turno: " << endl;
    cout << "1: Continuar el juego." << endl;
    cout << "2: Reiniciar la partida." << endl;
    cout << "3: Terminar el juego." << endl << endl;
    cin >> respuesta;
    cout << endl;
    switch (respuesta)
    {
    case 1:
        partida->getTurno()->siguienteTurno();
        return continuar;
        break;
    case 2:
        partida->~Tablero();
        return reiniciar;
        break;
    case 3:
        partida->~Tablero();
        return terminar;
        break;

    default:
        return preguntarTurno(partida);
        break;
    }
};

int imagenesBitmap(Tablero *tablero)
{
    for (unsigned int i = 0; i < tablero->getLargo(); i++)
    {
        BMP imagen;
        imagen.SetSize(tablero->getAncho()*32, tablero->getAlto()*32);
        imagen.SetBitDepth(8);

        for (unsigned int j = 0; j < tablero->getAncho(); j++)
            for (unsigned int k = 0; k < tablero->getAlto(); k++)
            {
                for (unsigned int l = 0; l < 32; l++){

                    for (unsigned int m = 0; m < 32; m++){
                        imagen(j+l, k+m)->Red = tablero->getTablero()->obtener(i+1)->obtener(j+1)->obtener(k+1)->getCelula()->getGen1();
                        imagen(j+l, k+m)->Blue = tablero->getTablero()->obtener(i+1)->obtener(j+1)->obtener(k+1)->getCelula()->getGen2();
                        imagen(j+l, k+m)->Green = tablero->getTablero()->obtener(i+1)->obtener(j+1)->obtener(k+1)->getCelula()->getGen3();

                    }

                }
                
            }
        char nombre[] = {'P', 'a', 'g', 'i', 'n', 'a', '_', char(49+i), '.', 'b', 'm', 'p', '\0'};
        const char * pagina = &nombre[0];

        imagen.WriteToFile(pagina);
    };
    

    return 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    AccionTurno sigTurno;
    do{
        bienvenida();

        Tablero *partida = new Tablero(configurar());

        partida->definirCelulasVivas();
        imagenesBitmap(partida);
        partida->imprimirTablero();

        sigTurno = preguntarTurno(partida);

        while (sigTurno == continuar){

            partida->resolverTurno();
            imagenesBitmap(partida);
            partida->imprimirTablero();
            sigTurno = preguntarTurno(partida);
        }

    }while (sigTurno == reiniciar);

    return 0;
}
