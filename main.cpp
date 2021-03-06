#include <iostream>
#include <string>
#include "Pieza.h"
#include "Peon.h"
#include "Caballo.h"
#include "Rey.h"
#include "Torre.h"
#include "Alfil.h"
#include "Reina.h"
using namespace std;

void inicializar_Piezas(Pieza***);
void imprimir_tablero_Jugador1(Pieza***,string,string);
void imprimir_tablero_Jugador2(Pieza***,string,string);
int conseguir_posicionX(char,bool);
int conseguir_posicionY(char,bool);
bool Coronamiento(int,int,char , Pieza***);
bool enrocarse(int, int, int, int, Pieza***, Torre*, int, int);
bool comer_al_Paso(char,int,int,int,int,Pieza***);

int main(){
    string nombre_jugador1, nombre_jugador2;
    int opcion_usuario;
    char seguir = 's';
    cout << "\nJuego de Ajedrez\n\n";
    while(seguir == 's'){
        cout << "Menu" << endl
             << "[1] Jugar" << endl
             << "[2] Salir" << endl
             << "Seleccione una opcion: ";
        cin >> opcion_usuario;
        cout << endl;
        switch (opcion_usuario){
        case 1:{
            //Jugar
            cout << "Nombre Jugador1: ";
            cin >> nombre_jugador1;
            cout << endl;
            cout << "Nombre Jugador2: ";
            cin >> nombre_jugador2;
            cout << endl;
            //Crear Tablero
            Pieza ***tablero = new Pieza **[8];
            for (int i = 0; i < 8; i++){
                tablero[i] = new Pieza *[8];
                for (int j = 0; j < 8; j++){
                    tablero[i][j] = NULL;
                }
            }
            //Inicializar Tablero
            inicializar_Piezas(tablero);
            //Determinar Juego
            int turno = 1;
            string movimiento_jug1, movimiento_jug2;
            bool terminar_partida = true;
            while(terminar_partida){
                if(turno % 2 != 0){
                    bool movimiento_valido_jug1 = false;
                    while(!movimiento_valido_jug1){
                        //Turno Jugador 1
                        cout << "Turno Jugador 1\n\n"; 
                        //Imprimir Tablero en perspectiva del Jugador 1
                        imprimir_tablero_Jugador1(tablero,nombre_jugador1,nombre_jugador2);
                        cout << "Ingrese: ";
                        cin >> movimiento_jug1;

                        //Fin de Juego por medio de abandonar la partida
                        if(movimiento_jug1 == "bai"){
                            terminar_partida = false;
                            movimiento_valido_jug1 = true;
                            cout << "*Partida finalizada, " << nombre_jugador1 <<" abandonó*\n" << endl;
                        } else {
                            string coordenada_inicial = movimiento_jug1.substr(2,2);
                            string coordenada_final = movimiento_jug1.substr(5);
                            int x_inicial, y_inicial, x_final, y_final;

                            x_inicial = conseguir_posicionX(coordenada_inicial[1],true);
                            y_inicial = conseguir_posicionY(coordenada_inicial[0],true);
                            x_final = conseguir_posicionX(coordenada_final[1], true);
                            y_final = conseguir_posicionY(coordenada_final[0], true);

                            char pieza = movimiento_jug1[0];
                            switch (pieza){
                            case 'P': {
                                Peon* peon = dynamic_cast<Peon*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug1 = peon->validar_movimiento('P',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug1){
                                bool verificar_movimiento_especial = true;
                                //Validar el comer al paso
                                    verificar_movimiento_especial = comer_al_Paso('P',x_inicial,y_inicial,x_final,y_final,tablero);
                                    if(verificar_movimiento_especial){
                                        tablero[x_inicial][y_inicial] = NULL;
                                        tablero[x_final][y_final] = peon; 
                                    } else{
                                        //No realizo el comer al paso pero igual se mueve
                                        //Vamos a ver si se corono
                                        cout << "hola movimiento jugador 1 completado\n";
                                            tablero[x_inicial][y_inicial] = NULL;
                                            tablero[x_final][y_final] = peon;
                                        /*if(Coronamiento(x_final,y_final,'P',tablero)){
                                            //Reina* PeonCoronado = new Reina(); //Parametros de Reina
                                            tablero[x_inicial][y_inicial] = NULL;
                                        } else {
                                        }*/
                                    }    
                                }
                                break;
                            }
                            case 'N': {
                                Caballo* caballo = dynamic_cast<Caballo*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug1 = caballo->validar_movimiento('N',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug1){
                                    cout << "movimiento jugador 1 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = caballo;
                                }
                                break;
                            }
                            case 'K': {
                                Rey* rey = dynamic_cast<Rey*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug1 = rey->validar_movimiento('K',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug1){
                                    cout << "movimiento jugador 1 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = rey;
                                }
                                break;
                            }
                            case 'R': {
                                Torre* torre = dynamic_cast<Torre*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug1 = torre->validar_movimiento('R',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug1){
                                    cout << "movimiento jugador 1 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = torre;
                                }
                                break;
                            }
                            case 'B': {
                                Alfil* alfil = dynamic_cast<Alfil*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug1 = alfil->validar_movimiento('B',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug1){
                                    cout << "movimiento jugador 1 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = alfil;
                                }
                                break;
                            }
                            case 'Q': {
                                Reina* reina = dynamic_cast<Reina*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug1 = reina->validar_movimiento('Q',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug1){
                                    cout << "movimiento jugador 1 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = reina;
                                }
                                break;
                            }
                            default:
                                cout << "Movimiento Invalido -- Eligio una pieza que no le corresponde.\n\n";
                                movimiento_valido_jug1 = false;
                                break;
                            }
                        }
                    }
                    turno++;
                    cout << endl;
                } else {
                    //Turno Jugador 2
                    bool movimiento_valido_jug2 = false;
                    while(!movimiento_valido_jug2){
                        cout << "Turno Jugador 2\n\n";
                        //Imprimir Tablero en perspectiva del Jugador 2
                        imprimir_tablero_Jugador2(tablero,nombre_jugador1,nombre_jugador2);
                        cout << "Ingrese: ";
                        cin >> movimiento_jug2;
                        //Fin de Juego por medio de abandonar la partida
                        if(movimiento_jug2 == "bai"){
                            terminar_partida = false;
                            movimiento_valido_jug2 = true;
                            cout << "*Partida finalizada, " << nombre_jugador2 <<" abandonó*\n" << endl;
                        } else {
                            string coordenada_inicial = movimiento_jug2.substr(2,2);
                            string coordenada_final = movimiento_jug2.substr(5);
                            int x_inicial, y_inicial, x_final, y_final;

                            x_inicial = conseguir_posicionX(coordenada_inicial[1],true);
                            y_inicial = conseguir_posicionY(coordenada_inicial[0],true);
                            x_final = conseguir_posicionX(coordenada_final[1], true);
                            y_final = conseguir_posicionY(coordenada_final[0], true);

                            char pieza_jug2 = movimiento_jug2[0];
                            switch (pieza_jug2){
                            case 'p':{
                                Peon* peon = dynamic_cast<Peon*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug2 = peon->validar_movimiento('p',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug2){
                                    bool verificar_movimiento_especial = true;
                                    //Validar el comer al paso
                                    verificar_movimiento_especial = comer_al_Paso('p',x_inicial,y_inicial,x_final,y_final,tablero);
                                    if(verificar_movimiento_especial){
                                        tablero[x_inicial][y_inicial] = NULL;
                                        tablero[x_final][y_final] = peon; 
                                    } else{
                                        //No realizo el comer al paso pero igual se mueve
                                        cout << "movimiento jugador 2 completado\n";
                                        tablero[x_inicial][y_inicial] = NULL;
                                        tablero[x_final][y_final] = peon;
                                    }
                                }
                            }
                            break;
                            case 'n': {
                                Caballo* caballo = dynamic_cast<Caballo*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug2 = caballo->validar_movimiento('n',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug2){
                                    cout << "movimiento jugador 2 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = caballo;
                                }
                                break;
                            }
                            case 'k': {
                                Rey* rey = dynamic_cast<Rey*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug2 = rey->validar_movimiento('k',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug2){
                                    cout << "movimiento jugador 2 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = rey;
                                }
                                break;
                            }
                            case 'r': {
                                Torre* torre = dynamic_cast<Torre*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug2 = torre->validar_movimiento('r',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug2){
                                    cout << "movimiento jugador 2 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = torre;
                                }
                                break;
                            }
                            case 'b': {
                                Alfil* alfil = dynamic_cast<Alfil*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug2 = alfil->validar_movimiento('b',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug2){
                                    cout << "movimiento jugador 2 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = alfil;
                                }
                                break;
                            }
                            case 'q': {
                                Reina* reina = dynamic_cast<Reina*>(tablero[x_inicial][y_inicial]);
                                movimiento_valido_jug2 = reina->validar_movimiento('q',x_inicial,y_inicial,x_final,y_final,tablero);
                                if(movimiento_valido_jug2){
                                    cout << "movimiento jugador 2 completado\n";
                                    tablero[x_inicial][y_inicial] = NULL;
                                    tablero[x_final][y_final] = reina;
                                }
                                break;
                            }
                            default:
                            cout << "Movimiento Invalido -- Eligio una pieza que no le corresponde.\n\n";
                                movimiento_valido_jug2 = false;
                                break;
                            }
                        }
                    }
                    turno++;
                    cout << endl;
                }
            }
            //Liberar Matriz
            // Libera la matriz
	        for(int i = 0; i < 8; i++){
		        delete[] tablero[i];
		        tablero[i] = NULL;
	        }
	        delete[] tablero;
            break;
        }
        case 2:{
            //Salir de Programa
            cout << "Fin de Programa\n\n";
            seguir = 'n';
            break;
        }    
        default:
        cout << "Ingreso una opcion invalida.\n\n";
            break;
        }
    }
    return 0;
}

void inicializar_Piezas(Pieza*** tablero){
    //Inicializar piezas negras
    //Torres
    tablero[0][0] = new Torre(0,0,'r',"negro");
    tablero[0][7] = new Torre(0,7,'r',"negro");
    //Caballos
    tablero[0][1] = new Caballo(0,1,'n',"negro");
    tablero[0][6] = new Caballo(0,6,'n',"negro");
    //Alfiles
    tablero[0][2] = new Alfil(0,2,'b',"negro");
    tablero[0][5] = new Alfil(0,5,'b',"negro");
    //Reina
    tablero[0][3] = new Reina(0,3,'q',"negro");
    //Rey
    tablero[0][4] = new Rey(0,4,'k',"negro");
    //Peones negros
    for (int i = 0; i < 8; i++){
        tablero[1][i] = new Peon(1, i, 'p',"negro");
    }
    //Inicializar piezas blancas
    //Torres
    tablero[7][0] = new Torre(7,0,'R',"blanco");
    tablero[7][7] = new Torre(7,7,'R',"blanco");
    //Caballos
    tablero[7][1] = new Caballo(7,1,'N',"blanco");
    tablero[7][6] = new Caballo(7,6,'N',"blanco");
    //Alfiles
    tablero[7][2] = new Alfil(7,2,'B',"blanco");
    tablero[7][5] = new Alfil(7,5,'B',"blanco");
    //Reina
    tablero[7][3] = new Reina(7,3,'Q',"blanco");
    //Rey
    tablero[7][4] = new Rey(0,4,'K',"blanco");
    //Peones
    for (int i = 0; i < 8; i++){
        tablero[6][i] = new Peon(6,i,'P',"blanco");
    }
}

bool comer_al_Paso(char peon, int x_inicial, int y_inicial, int x_final, int y_final, Pieza*** tablero){
    bool temp_comeralPaso = true;
    if(peon ==  'P'){
        //Caso Jugador 1
        if( x_inicial == 3 && tablero[x_inicial][y_inicial - 1] == dynamic_cast<Peon*>(tablero[x_inicial][y_inicial - 1]) ){
            //Es un peon a la izquierda
            //Caso Comer Al Paso si hay una pieza a la izquierda
            Peon* peon_rival = dynamic_cast<Peon*>(tablero[x_inicial][y_inicial - 1]);
            if(peon_rival->getTurno() == 1 && peon_rival->getColor() == "negro" ){
                //Validar comer al paso
                if(x_inicial - 1  == x_final && y_inicial - 1 == y_final){
                    temp_comeralPaso = true;
                    tablero[x_inicial][y_inicial - 1] =NULL;
                    tablero[x_inicial][y_inicial] = NULL;
                    cout << "Se comio al peon rival por medio de comer al paso\n\n";
                } else {
                    temp_comeralPaso = false;
                    //No intenta comer al paso
                }
            } else {
                temp_comeralPaso = false;//Hay una pieza o algo
            }
        } else if(x_inicial == 3 && tablero[x_inicial][y_inicial + 1] == dynamic_cast<Peon*>(tablero[x_inicial][y_inicial + 1])){
            //Es un peon a la derecha
            Peon* peon_rival = dynamic_cast<Peon*>(tablero[x_inicial][y_inicial +1]);
            if(peon_rival->getTurno() == 1 && peon_rival->getColor() == "negro" ){
                //Validar comer al paso
                if(x_inicial- 1  == x_final && y_inicial + 1 == y_final){
                    temp_comeralPaso = true;
                    tablero[x_inicial][y_inicial + 1] =NULL;
                    tablero[x_inicial][y_inicial] = NULL;
                    cout << "Se comio al peon rival por medio de comer al paso\n\n";
                } else {
                    temp_comeralPaso = false;
                    //No intenta comer al paso
                }
            } else {
                temp_comeralPaso = false;
            }
        }
    } else {
        //Caso Jugador 2
        if( x_inicial == 5 && tablero[x_inicial][y_inicial - 1] == dynamic_cast<Peon*>(tablero[x_inicial][y_inicial - 1]) ){
            //Es un peon a la izquierda
            //Caso Comer Al Paso si hay una pieza a la izquierda
            Peon* peon_rival = dynamic_cast<Peon*>(tablero[x_inicial][y_inicial - 1]);
            if(peon_rival->getTurno() == 1 && peon_rival->getColor() == "blanco" ){
                //Validar comer al paso
                if(x_inicial + 1  == x_final && y_inicial - 1 == y_final){
                    temp_comeralPaso = true;
                    tablero[x_inicial][y_inicial - 1] =NULL;
                    tablero[x_inicial][y_inicial] = NULL;
                    cout << "Se comio al peon rival por medio de comer al paso\n\n";
                } else {
                    temp_comeralPaso = false;
                    //No intenta comer al paso
                }
            } else {
                temp_comeralPaso = false;
            }
        } else if(x_inicial == 5 && tablero[x_inicial][y_inicial + 1] == dynamic_cast<Peon*>(tablero[x_inicial][y_inicial + 1])){
            //Es un peon a la derecha
            Peon* peon_rival = dynamic_cast<Peon*>(tablero[x_inicial][y_inicial +1]);
            if(peon_rival->getTurno() == 1 && peon_rival->getColor() == "blanco" ){
                //Validar comer al paso
                if(x_inicial +  1  == x_final && y_inicial + 1 == y_final){
                    temp_comeralPaso = true;
                    tablero[x_inicial][y_inicial + 1] =NULL;
                    tablero[x_inicial][y_inicial] = NULL;
                    cout << "Se comio al peon rival por medio de comer al paso\n\n";
                } else {
                    temp_comeralPaso = false;
                    //No intenta comer al paso
                }
            } else {
                temp_comeralPaso = false;
            }
        }


    }
    return temp_comeralPaso;
}

bool enrocarse(int x_in, int y_in, int x_fi, int y_fi, Pieza*** tablero, Torre* torre, int ReyX, int ReyY){
    if(tablero[x_in][y_in] == torre){
        if(x_fi == ReyX && y_fi == ReyY){
            return true;
        }
    }
    return false;
}

bool Coronamiento(int x_final,int y_final, char peon, Pieza*** tablero){
    if (peon == 'P'){
        //Caso Jugador 1
        if(x_final == 0){
            int seleccion_coronacion;
            cout << "Cambiar Peon a:" << endl
                << "[1] Reina" << endl
                << "[2] Caballo" << endl
                << "[3] Alfil" << endl
                << "[4]Torre" << endl
                << "Seleccione una opcion: ";
            cin >> seleccion_coronacion;

            switch (seleccion_coronacion){
            case 1:
                //Reina
                tablero[x_final][y_final] = new Reina(x_final,y_final,'Q',"blanco");
                break;
            case 2:
                //Caballo
                tablero[x_final][y_final] = new Caballo(x_final,y_final,'N',"blanco");
                break;
            case 3:
                //Alfil
                tablero[x_final][y_final] = new Alfil(x_final,y_final,'B',"blanco");
                break;
            case 4:
                //Torre
                tablero[x_final][y_final] = new Torre(x_final,y_final,'R',"blanco");
                break;
            default:
                break;
            }
            cout << "El Peon se corono exitosamente\n\n";
            return true;
        }else {
            return false;
        }
    } else {
        //Caso Jugador 2
    }
}

void imprimir_tablero_Jugador1(Pieza*** tablero, string nombre_jugador1, string nombre_jugador2){
    cout << "   "<< nombre_jugador2 << endl;
    int contador_columna = 8;
    for (int i = 0; i < 8; i++){
        for (int j = -1; j < 8; j++){
            if(j == -1){
                cout << "[" << contador_columna << "] ";
                contador_columna--; 
            } else {
                if(tablero[i][j] == NULL) {
                    if(j== 7){
                        //cout << "|" << i << j << "|";
                        cout << "|   |";
                    } else {
                        //cout << "|" << i << j << "| ";
                        cout << "|   | ";
                    }
                } else {
                    if(j == 7){
                        //cout << "| " << i << j << " |";
                        cout << "| " << tablero[i][j]->getCaracter() << " |";
                    } else {
                        //cout << "| " << i << j << " |";
                        cout << "| " << tablero[i][j]->getCaracter() << " | ";
                    }
                }
            }
        }
        cout << endl;
    }
    cout << "     [a]   [b]   [c]   [d]   [e]   [f]   [g]   [h]" << endl;
    cout << "   " <<nombre_jugador1 << endl;
}

void imprimir_tablero_Jugador2(Pieza ***tablero, string nombre_jugador1, string nombre_jugador_2){
    cout << "   "<<nombre_jugador1 << endl;
    int contador_columna = 1;

    for (int i = 7; i >= 0; i--){
        for (int j = 8; j >=0; j--){
            if(j == 8){
                cout << "[" << contador_columna << "]";
                contador_columna++;
            } else {
                if(tablero[i][j] == NULL) {
                    if(j== 7){
                        //cout << "|" << i << j << "|";
                        cout << "|   |";
                    } else {
                        //cout << "|" << i << j << "| ";
                        cout << "|   | ";
                    }
                } else {
                    if(j == 7){
                        //cout << "| " << i << j << " |";
                        cout << "| " << tablero[i][j]->getCaracter() << " |";
                    } else {
                        //cout << "| " << i << j << " |";
                        cout << "| " << tablero[i][j]->getCaracter() << " | ";
                    }
                }
            }
        }
        cout << endl;
    }
    cout << "    [h]   [g]   [f]   [e]   [d]   [c]   [b]   [a]" << endl;
    cout << "   " <<nombre_jugador_2 << endl;
}

int conseguir_posicionX(char pos_x,bool perspectiva){
    if(perspectiva){
        //Busca en perspectiva del Jugador 1
        switch (pos_x){
        case '8':
            return 0;
            break;
        case '7':
            return 1;
            break;
        case '6':
            return 2;
            break;
        case '5':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '3':
            return 5;
            break;
        case '2':
            return 6;
            break;
        case '1':
            return 7;
            break;       
        default:
        return 9;
            break;
        }
    } else {
        //Busca en perspectiva del Jugador 2
        switch (pos_x){
        case '1':
            return 7;
            break;
        case '2':
            return 6;
            break;
        case '3':
            return 5;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 3;
            break;
        case '6':
            return 2;
            break;
        case '7':
            return 1;
            break;
        case '8':
            return 0;
            break;       
        default:
        return 9;
            break;
        }
    }
}

int conseguir_posicionY(char pos_y,bool perspectiva) {
    if(perspectiva){
        //Perspectiva Jugador 1
        switch (pos_y){
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 'e':
            return 4;
            break;
        case 'f':
            return 5;
            break;
        case 'g':
            return 6;
            break;
        case 'h':
            return 7;
            break;
        default:
            return 9;
            break;
        }
    } else {
        //Perspectiva Jugador 2
        switch (pos_y){
        case 'h':
            return 7;
            break;
        case 'g':
            return 6;
            break;
        case 'f':
            return 5;
            break;
        case 'e':
            return 4;
            break;
        case 'd':
            return 3;
            break;
        case 'c':
            return 2;
            break;
        case 'b':
            return 1;
            break;
        case 'a':
            return 0;
            break;
        default:
            return 9;
            break;
        }
    }
}