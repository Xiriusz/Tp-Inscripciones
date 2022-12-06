#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
using namespace std;

struct Alumnos{
    int Legajo;
    char NomyAp[30];
    int Antiguedad;
};
struct Materias{
    int CodM;
    char Nombre[30];
    int Capacidad;
};
struct Inscrip{
    int Legajo;
    int CodM;
};
struct MateriaAntiguedadAcumulada {
    int CodM;
    int CantAlum;
    int AntiguedadAcumulada;
};
struct Nodo {
    Nodo *sig;
    Alumnos NodoAlum;
};
struct MateriaAlumno{
    int CodM;
    int Legajo;
    int Antiguedad;
};

void genAlumnos();
void lecAlumnos();
void genMaterias();
void lecMaterias();
void genInscrip();
void lecInscrip();
vector<MateriaAntiguedadAcumulada> antiguedadAcumulada(vector<MateriaAlumno>);
void antiguedadPromedio(vector<MateriaAlumno>);
bool BuscSecuAlum(int, vector <Alumnos>);
bool BuscSecuMat(int, vector <Materias>);
bool busqSecuInsc(int, vector<Inscrip>);
int matSinInscrip(vector<Materias>, vector<Inscrip>);

int main() {
    int resp;
    std::cout << "Hello, World!" << std::endl;
    cout << "Bienvenido, por favor seleccione la accion deseada \n";
    cout << "Opcion 0) Salir\n";
    cout << "Opcion 1) Ingresar datos de alumnos\n";
    cout << "Opcion 2) Leer datos de alumnos \n";
    cout << "Opcion 3) Ingresar datos de Materias \n";
    cout << "Opcion 4) Leer datos de Materias \n";
    cout << "Opcion 5) Ingresar datos de Inscripciones \n";
    cout << "Opcion 6) Leer datos de Inscripciones \n";
    cout << "Opcion 7) Ejecutar inscripciones" << endl;
    cout << "Opcion 8) Cantidad de materias sin inscriptos" << endl;
    cout << "Opcion 9) Promedio antiguedad de inscriptos por materia" << endl;
    cout << "Opcion 10) Alumnos no inscriptos por exceder capacidad" << endl;
    cin >> resp;

    cin >> resp;
    switch (resp) {
        case 0:
            exit(1);
        case 1:
            genAlumnos();
            break;
        case 2:
            lecAlumnos();
            break;
        case 3:
            genMaterias();
            break;
        case 4:
            lecMaterias();
            break;
        case 5:
            genInscrip();
            break;
        case 6:
            lecInscrip();
            break;
        case 7:
            break;
        case 10:
            antiguedadPromedio(vector<MateriaAlumno>);
            break;
        case 8:
            matSinInscrip(vector<Materias>,vector<Inscrip>);
            break;

    }
    cout<<"Muchas gracias por utilizar el programa"<<endl;
    return 0;
}

// Generacion de Archivos y Lectura
void genAlumnos(){
    Alumnos aPersona;
    FILE *Alumnos;
    Alumnos= fopen("Alumnos.dat","wb");
        cout << "Ingrese legajo ( 0 para detener la grabacion de datos) \n";
        cin >> aPersona.Legajo;
        while(aPersona.Legajo != 0) {
            cout << "Ingrese Nombre " << endl;
            cin >> aPersona.NomyAp;
            cout << "Ingrese antiguedad" << endl;
            cin >> aPersona.Antiguedad;
            fwrite(&aPersona, sizeof(aPersona), 1, Alumnos);
            cout << "Ingrese legajo ( 0 para detener la grabacion de datos)" << endl;
            cin >> aPersona.Legajo;

        }
        fclose(Alumnos);
        cout << "Datos ingresados correctamente" << endl;

}
void lecAlumnos(){
    Alumnos aPersona;
    FILE *Alumnos;
    Alumnos = fopen("Alumnos.dat", "rb");
    if (Alumnos == NULL){
        cout << "No se puede abrir el archivo \n";
}
    cout << "Listado de alumnos de sistemas \n";
    cout << "Legajo" << " " << "Nombre" << " " << "Antiguedad " <<"\n";
    fread(&aPersona,sizeof(aPersona),1,Alumnos);
    while (!feof(Alumnos)){
    cout << aPersona.Legajo << "     " << aPersona.NomyAp << "     " << aPersona.Antiguedad << "\n";
        fread(&aPersona,sizeof(aPersona),1,Alumnos);
    }
    fclose(Alumnos);
    cout << "Lectura completada" << endl;
}
void genMaterias(){
    Materias aMateria;
    FILE *Materias;
    Materias= fopen("Materias.dat","wb");
        cout << "Ingrese codigo de la materia ( 0 para detener la grabacion de datos)" << endl;
        cin >> aMateria.CodM;
    while(aMateria.CodM != 0){
        cout<<"Ingrese nombre de la materia "<< endl;
        cin>>aMateria.Nombre;
        cout<<"Ingrese capacidad" <<endl;
        cin>>aMateria.Capacidad;
        fwrite(&aMateria,sizeof(aMateria),1,Materias);
        cout << "Ingrese codigo de la materia ( 0 para detener la grabacion de datos) \n";
        cin >> aMateria.CodM;
    }
    fclose(Materias);
    cout << "Datos ingresados correctamente" << endl;
}
void lecMaterias(){
    Materias aMateria;
    FILE *Materias;
    Materias = fopen("Materias.dat", "rb");
    if (Materias == NULL){
        cout << "No se puede abrir el archivo \n";
    }
    cout << "Listado de alumnos de sistemas \n";
    cout << "Codigo" << " " << "Nombre" << " " << "Capacidad" <<"\n";
    fread(&aMateria,sizeof(aMateria),1,Materias);
    while (!feof(Materias)){
        cout << aMateria.CodM << "     " << aMateria.Nombre << "     " << aMateria.Capacidad << "\n";
        fread(&aMateria,sizeof(aMateria),1,Materias);
    }
    fclose(Materias);
    cout << "Lectura completada" << endl;
}
void genInscrip(){
    Inscrip aInscrip;
    FILE *Inscripciones;
    Inscripciones= fopen("Inscripciones.dat","wb");
        cout << "Ingrese legajo ( 0 para detener la grabacion de datos) \n";
        cin >> aInscrip.Legajo;
     while(aInscrip.Legajo != 0){
        cout<<"Ingrese Codigo de la materia "<<endl;
        cin>>aInscrip.CodM;
        fwrite(&aInscrip,sizeof(aInscrip),1,Inscripciones);
         cout << "Ingrese legajo ( 0 para detener la grabacion de datos) "<<endl;
         cin >> aInscrip.Legajo;
    }

    fclose(Inscripciones);
    cout << "Datos ingresados correctamente" << endl;
}
void lecInscrip(){
    FILE *Inscripciones;
    Inscrip aInscrip;
    Inscripciones = fopen("Inscripciones.dat", "rb");
    if (Inscripciones == NULL){
        cout << "No se puede abrir el archivo \n";
    }
    cout << "Listado de alumnos de sistemas \n";
    cout << "Legajo" << " " << "Materia" << " " <<"\n";
    fread(&aInscrip,sizeof(aInscrip),1,Inscripciones);
    while (!feof(Inscripciones)){
        cout << aInscrip.Legajo << "     " << aInscrip.CodM << "     " << "\n";
        fread(&aInscrip,sizeof(aInscrip),1,Inscripciones);
    }
    fclose(Inscripciones);
    cout << "Lectura completada" << endl;
}
// Busquedas Secuenciales
bool BuscSecuAlum(int numBusq, vector <Alumnos> alumno) {
    bool band = false;
    for (int i = 0; i < alumno.size(); ++i) {
        if (alumno[i].Legajo == numBusq){
            band = true;
            break;
        }
    }
    return band;
}
bool BuscSecuMat(int numBusq, vector <Materias> materia) {
    bool band = false;
    for (int i = 0; i < materia.size(); ++i) {
        if (materia[i].CodM == numBusq){
            band = true;
            break;
        }
    }
    return band;
}
bool busqSecuInsc(int numBusq, vector<Inscrip> inscripciones) {
    bool band = false;
    for (int i = 0; i < inscripciones.size(); ++i) {
        if (inscripciones[i].CodM == numBusq){
            band = true;
            break;
        }
    }
    return band;

}
// Funciones para Informe
int matSinInscrip( vector<Inscrip> inscripciones, vector<Materias> materias) {
    int materiasSinInscriptos = 0;
    for (int i = 0; i < materias.size(); i++) {
        if(!busqSecuInsc(materias[i].CodM, inscripciones))
            materiasSinInscriptos++;
    }

    return materiasSinInscriptos;
}
vector<MateriaAntiguedadAcumulada> antiguedadAcumulada(vector<MateriaAlumno> materiaAlumno) {
    bool materiaEncontrada;
    vector<MateriaAntiguedadAcumulada> antiguedadAcumulada;
    for (int i = 0; i < materiaAlumno.size(); i++) {
        materiaEncontrada = false;
        for (int j = 0; j < antiguedadAcumulada.size(); j++) {
            if (materiaAlumno[i].CodM == antiguedadAcumulada[j].CodM) {
                materiaEncontrada = true;
                antiguedadAcumulada[j].CantAlum += 1;
                antiguedadAcumulada[j].AntiguedadAcumulada += materiaAlumno[i].Antiguedad;
                break;
            }
        }

        if (!materiaEncontrada) {
            MateriaAntiguedadAcumulada aux = {materiaAlumno[i].CodM, 1, materiaAlumno[i].Antiguedad};
            antiguedadAcumulada.push_back(aux);
        }
    }

    return antiguedadAcumulada;
}

void antiguedadPromedio(vector<MateriaAlumno> materiaAlumno) {
    vector<MateriaAntiguedadAcumulada> antiguedad = antiguedadAcumulada(materiaAlumno);
    cout << "Materia" << " " << "AntiguedadPromedio" << " " <<"\n";
    for (int i = 0; i < antiguedad.size(); i++) {
        float promedio = antiguedad[i].AntiguedadAcumulada / antiguedad[i].CantAlum;
        cout << antiguedad[i].CodM << "     " << promedio << "     " << "\n";
    }
}
void ordenLista (Nodo *&Lista, Alumnos RAlu){
        Nodo *pnuevo = new Nodo();
        pnuevo->NodoAlum = RAlu;

    if((Lista == NULL) ||(pnuevo -> NodoAlum.NomyAp, Lista -> NodoAlum.NomyAp))<0){
        pnuevo-> sig = Lista;
        Lista = pnuevo;
    }else{
        Nodo* pant;
        Nodo* punt = Lista;
        while ((punt != NULL) && ((pnuevo -> NodoAlum.NomyAp, punt -> NodoAlum.NomyAp))>0){
            pant = punt;
            punt = punt -> sig;
        }
        ptrant -> sig = pnuevo;
        pnuevo -> sig = punt;
    }
}
void  informe3(Nodo* Lista){
    cout << "Nombre " << " Legajo" << endl;
    while(Lista != NULL){
        cout << "  " <<Lista->NodoAlum.NomyAp <<"      " << Lista->NodoAlum.Legajo << endl;
        Lista = Lista -> sig;
    }
}
