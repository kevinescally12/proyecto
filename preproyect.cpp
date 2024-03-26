#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

void mensajeDespedida() {
    cout << "Gracias por visitar la Fundación Dejando Huellas. ¡Hasta luego!" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class Animal {
public:
    string nombre;
    string codigo;
    string fecha;
    string raza;
    int edad;
    bool lleno;

    Animal() {
        lleno = false;
    }

    virtual void ingresar() = 0;
    virtual void mostrar() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class Perro : public Animal {
public:
    void ingresar() override {
        cout << "Ingresando un perro..." << endl;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Codigo: ";
        cin >> codigo;
        cout << "Fecha de ingreso: ";
        cin >> fecha;
        cout << "Raza: ";
        cin >> raza;
        cout << "Edad: ";
        cin >> edad;
        lleno = true;
    }

    void mostrar() override {
        cout << "Perro: " << nombre << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Fecha de ingreso: " << fecha << endl;
        cout << "Raza: " << raza << endl;
        cout << "Edad: " << edad << endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class Gato : public Animal {
public:
    void ingresar() override {
        cout << "Ingresando un gato..." << endl;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Codigo: ";
        cin >> codigo;
        cout << "Fecha de ingreso: ";
        cin >> fecha;
        cout << "Raza: ";
        cin >> raza;
        cout << "Edad: ";
        cin >> edad;
        lleno = true;
    }

    void mostrar() override {
        cout << "Gato: " << nombre << endl;
        cout << "Codigo: " << codigo << endl;
        cout << "Fecha de ingreso: " << fecha << endl;
        cout << "Raza: " << raza << endl;
        cout << "Edad: " << edad << endl;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class Fundacion {
private:
    vector<Animal*> animales;

public:
    void menu();
    void listar();
    void adopcion();
    void guardarDatos();
    void cargarDatos();
    void eliminarAnimal(const string& codigo);
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void Fundacion::menu() {
    char opcion;
    do {
        cout << "\nMENU PRINCIPAL\n";
        cout << "(1) Ingresar perro\n";
        cout << "(2) Ingresar gato\n";
        cout << "(3) Listar animales\n";
        cout << "(4) Mostrar estado de adopcion\n";
        cout << "(5) Guardar datos\n";
        cout << "(6) Cargar datos\n";
        cout << "(7) Eliminar animal\n";
        cout << "(8) Salir\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch(opcion) {
            case '1': {
                Perro* perro = new Perro();
                perro->ingresar();
                animales.push_back(perro);
                break;
            }
            case '2': {
                Gato* gato = new Gato();
                gato->ingresar();
                animales.push_back(gato);
                break;
            }
            case '3':
                listar();
                break;
            case '4':
                adopcion();
                break;
            case '5':
                guardarDatos();
                break;
            case '6':
                cargarDatos();
                break;
            case '7': {
                string codigo;
                cout << "Ingrese el codigo del animal a eliminar: ";
                cin >> codigo;
                eliminarAnimal(codigo);
                break;
            }
            case '8':
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
                break;
        }
    } while(opcion != '8');
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void Fundacion::listar() {
    cout << "\nLISTA DE ANIMALES\n";
    for (int i = 0; i < animales.size(); i++) {
        animales[i]->mostrar();
        cout << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void Fundacion::adopcion() {
    string cod;
    cout << "Ingrese el codigo del animal: ";
    cin >> cod;
    for (int i = 0; i < animales.size(); i++) {
        if (animales[i]->codigo == cod) {
            if (animales[i]->edad > 10) {
                cout << "El animal no es factible para adopcion." << endl;
            } else {
                cout << "El animal es factible para adopcion." << endl;
            }
            return;
        }
    }
    cout << "Animal no encontrado." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void Fundacion::guardarDatos() {
    ofstream archivo("datos_animales.txt",ios::out | ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    for (int i = 0; i < animales.size(); i++) {
        if (animales[i]->lleno) {
            archivo << "P" << endl; 
            archivo << animales[i]->nombre << endl;
            archivo << animales[i]->codigo << endl;
            archivo << animales[i]->fecha << endl;
            archivo << animales[i]->raza << endl;
            archivo << animales[i]->edad << endl;
            archivo << animales[i]->lleno << endl;
        }
    }

    archivo.close();
    cout << "Datos guardados en archivo correctamente." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void Fundacion::cargarDatos() {
    ifstream archivo("datos_animales.txt");
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    for (auto animal : animales) {
        delete animal;
    }
    animales.clear();

    char tipo;
    while (archivo >> tipo) {
        Animal* nuevoAnimal;
        if (tipo == 'P') {
            nuevoAnimal = new Perro();
        } else if (tipo == 'G') {
            nuevoAnimal = new Gato();
        } else {
            cout << "Error: Tipo de animal desconocido." << endl;
            return;
        }

        archivo.ignore(); 
        getline(archivo, nuevoAnimal->nombre);
        getline(archivo, nuevoAnimal->codigo);
        getline(archivo, nuevoAnimal->fecha);
        getline(archivo, nuevoAnimal->raza);
        archivo >> nuevoAnimal->edad;
        archivo >> nuevoAnimal->lleno;
        archivo.ignore(); 

        animales.push_back(nuevoAnimal);
    }

    archivo.close();
    cout << "Datos cargados desde archivo correctamente." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void Fundacion::eliminarAnimal(const string& codigo) {
    for (auto it = animales.begin(); it != animales.end(); ++it) {
        if ((*it)->codigo == codigo) {
            delete *it; 
            animales.erase(it); 
            cout << "Animal eliminado correctamente." << endl;
            return;
        }
    }
    cout << "Animal no encontrado." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    setlocale(LC_ALL,"spanish.UTF-8");
    Fundacion fundacion;
    cout << "\n\n";
    cout << "*****************************************" << endl;
    cout << "******  FUNDACION DEJANDO HUELLAS  ******" << endl;
    cout << "*****************************************" << endl;

    fundacion.menu();
    atexit(mensajeDespedida);
    return 0;
}