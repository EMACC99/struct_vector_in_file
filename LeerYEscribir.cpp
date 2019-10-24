#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "menu_txts.h"

using namespace std;

/* Falta poner cuando tienes mas de un nombre, lo que se me ocurre es poner un while para tomar hasta Age:
@ ya que tiene formato preestablecio
@ 
@ 
*/


struct Persona{
    int age;
    string name;
};

void print_struct(const vector <Persona> &P){
    for (int i = 0; i < P.size(); ++i)
        cout << i+1 <<" Name: " << P[i].name << " Age: " << P[i].age << endl;
}

void add_person(vector<Persona> &P){

    Persona new_person;

    cout << "Nombre de la persona: " << endl;
    cin >> new_person.name;
    cout << "Edad de la persona" << endl;
    cin >> new_person.age;

    P.push_back(new_person);
    
}


void add_person_from_file(vector<Persona>&P, const vector<string> &A){
    
    Persona new_person;
    new_person.name = A[1];
    new_person.age = stoi(A[3]);
    P.push_back(new_person);

}


void write_person_with_format(const string &Ruta, const vector<Persona> & P){
    ofstream PersonFile;

    // PersonFile.open(Ruta, ios_base::app); //hacer append
    PersonFile.open(Ruta); //sobreescribir el archivo

    for (int i = 0; i < P.size(); ++i){
        PersonFile <<"Name: " <<  P[i].name << "  Age: " << P[i].age;
        PersonFile << endl;
    }
    PersonFile.close();
}


template<char delimiter>
class delimited_by_char: public string{};


vector <string> splitted_by_char(string &c){
    istringstream iss(c);
    const char delimiter = ' '; //puedes cambiar el valor para que separe por otras cosas
    vector<string> splitted ((istream_iterator<delimited_by_char<delimiter>>(iss)), istream_iterator<delimited_by_char<delimiter>>());

    return splitted;

}

void read_person(const string &Ruta, vector<Persona> &P){

    vector<string> temp;
    
    ifstream PersonFile;
    PersonFile.open(Ruta, ifstream::in);

    if (!PersonFile.is_open())
        cout << "No pude abrir el archivo" << endl;
    
    string line;
    while(getline(PersonFile, line)){
        temp = splitted_by_char(line);
        add_person_from_file(P, temp);
        temp.clear();

    }

    PersonFile.close();
}

void remove_person(const int &pos, vector <Persona> &P){
    P.erase(P.begin() + pos);
}



int main(){

    vector <Persona> P;
    string Ruta;
    Ruta = nombre_archivo();
    read_person(Ruta, P); //Leer del archivo
    
    int option = 0x00;
    while (option != 4){
        option = menu();
        switch (option){
            case 1:
                print_struct(P);
                break;
            case 2:
                int n;
                cout << "Número de Personas que desea añadir" << endl;
                cin >> n;
                for (int i = 0; i<n; ++i)
                    add_person(P);
                break;

            case 3:
                print_struct(P);
                int pos;
                cout << "Indice que quieres eliminar" << endl;
                cin >> pos;
                remove_person(pos - 1, P);
                break;

            case 4:
                cout << "saliendo..." << endl;
                break;

            default:
                cout << "opcion incorrecta";
                break;
        }
    }
    write_person_with_format(Ruta, P);
    return 0;
}