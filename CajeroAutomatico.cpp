
/* Proyecto final - Programación 1 - TUP - UTN - FR Bahia Blanca -- Eric Ponin -- Julio 2023 */

/*Advertencia: para utilizar el programa deberá contar, dentro de la carpeta donde se vaya a ejecutar, con un archivo: "Usuario.csv", que (a modo de ejemplo) debera tener los siguientes registros:

/* Sugerencia: para una mejor experiencia se recomienda descomentar todos los "system("cls")" y correr el ejecutable (.exe)*/

#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <ctime>

using namespace std;

const string nombreArchivo = "Usuarios.csv";

struct Usuario // estructura para el usuario
{
    string Alias;
    string Nombre;
    string Apellido;
    string CBU;
    int PIN;
    double Saldo;
};

void PantallaStandBy(); // Se declaran Todos los prototipos de las funciones
void PantallaAlias();
bool MenuAlias(string &, vector<Usuario> &, bool &);
void MenuUsuario();
void MenuPrincipal();
void Menu(int &, string &, vector<Usuario> &);
int IngresoNumeroEntero(string);
bool numeroValido(string &, int &);
bool PinValido(int &, string);
void LeerPIN(int &, string &, vector<Usuario> &, bool &, string);
void MostrarSaldo(string &, vector<Usuario> &);
double BuscarSaldo(string &, vector<Usuario> &);
void HacerRetiro(string &, vector<Usuario> &);
void Transferencia(string &, vector<Usuario> &);
void Deposito(string &, vector<Usuario> &);
void guardarArchivoCSV(const string &, const vector<Usuario> &);
bool ingresoOpcion(string);
void CambioClave(string &, vector<Usuario> &);
double IngresoNumeroDouble(string);
bool numeroDoubleValido(const string &, double &);
void RegistroMovimientos(string, string, string, double, double);

vector<Usuario> leerArchivoCSV(const string &nombreArchivo)
{ // crea una funcion tipo vector - Usuario
    vector<Usuario> usuarios;
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea))
    {                             // se utiliza para leer cada línea del archivo y ejecutar un bucle mientras haya líneas disponibles para leer.
        istringstream iss(linea); // crea un objeto de la clase istringstream. Esta clase es parte de la biblioteca <sstream> de C++ y se utiliza para leer y manipular cadenas de texto como si fueran flujos de entrada de datos.
        string campo;             // crea un variable para almacenar temporalmente el texto extraido del archivo
        Usuario usuario;

        getline(iss, campo, ','); // se utiliza para leer un campo del archivo CSV y almacenarlo en la variable campo.
        usuario.Alias = campo;    // se crea un nuevo usuario de tipo Usuario

        getline(iss, campo, ','); // se utiliza para leer un campo del archivo CSV y almacenarlo en la variable campo.
        usuario.Nombre = campo;   // El parámetro ',' se utiliza como delimitador para indicar que el campo debe leerse hasta que se encuentre una coma (','),
                                  //  lo que indica la separación entre campos en el archivo CSV.
        getline(iss, campo, ',');
        usuario.Apellido = campo;

        getline(iss, campo, ',');
        usuario.CBU = campo;

        getline(iss, campo, ',');
        usuario.PIN = stoi(campo);

        getline(iss, campo, ',');
        usuario.Saldo = stod(campo);

        usuarios.push_back(usuario); // es una función miembro de la clase vector que agrega un elemento al final del vector
    }
    archivo.close(); // Finalizada la carga de la lista se cierra el archivo
    return usuarios;
}

// La función de MenuAlias, basicamente es un booleano que devuelve si el alias es valido o no.
int main()
{
    int PIN;
    string alias;
    bool pinValido;
    bool aliasValido;
    vector<Usuario> ListaUsuarios;

    do
    {
        PantallaStandBy();                                          // se muestra la pantalla de espera
        aliasValido = MenuAlias(alias, ListaUsuarios, aliasValido); // se llama a la funcion donde se valida la identidad mediante el alias
        if (aliasValido)                                            // si es valido continua
        {
            MenuUsuario(); // muestra el menu donde se pide el PIN
            LeerPIN(PIN, alias, ListaUsuarios, pinValido, "PIN: ");
            if (pinValido) // si el pin es valido continua
            {
                Menu(PIN, alias, ListaUsuarios); // llama a funcion donde estan las opciones principales del cajero
            }
        }
        if (!aliasValido)
        {
            cout << "El usuario no existe o fue ingresado erroneamente" << endl;
            getch(); // Da tiempo a presionar una tecla par continuar con la ejecución.
        }
    } while (true);
    return 0;
}

void Menu(int &PIN, string &alias, vector<Usuario> &ListaUsuarios)
{
    int opcion = 0;
    do
    {
        MenuPrincipal();                                     // llama a la función MenuPrincipal que contiene el cartel con las opciones a elejir por el usuario
        opcion = IngresoNumeroEntero("Ingrese una Opcion:"); // Ingreso la opción mediante la función que controla que se ingresen valores correctos

        switch (opcion)
        { // El switch gestiona a que funcion deribar el programa segun el número ingresado por el usuario.
        case 1:
            MostrarSaldo(alias, ListaUsuarios);
            break;
        case 2:
            Deposito(alias, ListaUsuarios);
            break;
        case 3:
            HacerRetiro(alias, ListaUsuarios);
            break;
        case 4:
            Transferencia(alias, ListaUsuarios);
            break;
        case 5:
            CambioClave(alias, ListaUsuarios);
            break;
        case 0:
            cout << "Cerrando sesion." << endl; // muestra el cartel de "Saliendo" antes de terminar el programa.
            cout << "Muchas gracias!" << endl;
            break;
        default:
            cout << "Opcion incorrecta! Intentelo denuevo" << endl; // cualquier opción diferente de los números mostrados dispara el cartel de opción incorrecta.
        }
        getch(); // Da tiempo a presionar una tecla par continuar con la ejecución.
        //system("cls"); // Limpia la pantalla para volver a mostrar solo el menú principal, esta comentado porque solo funciona con el ejecutable(.exe)
    } while (opcion != 0);
}

void PantallaStandBy() // Función que contiene el cartel inicial del cajero
{
    //system("cls");
    cout << endl;
    cout << "    -----*********************************************************************************----" << endl;
    cout << "    -----************************** CAJERO AUTOMATICO DISPONIBLE *************************----" << endl;
    cout << "    -----                         PRESIONE UNA TECLA PARA COMENZAR                        ----" << endl;
    cout << "    ------------------------------------------------------------------------------------------" << endl;
    cout << "    ----                                                                                  ----" << endl;
    cout << "    -----********************************************************************************-----" << endl;
    cout << endl;
    getch();
}
void PantallaAlias() // Función que contiene el cartel pidiendo alias del cajero
{
    //system("cls");
    cout << endl;
    cout << "    -----*********************************************************************************----" << endl;
    cout << "    -----********************************* CAJERO AUTOMATICO *****************************----" << endl;
    cout << "    -----                           INGRESE SU ALIAS PARA CONTINUAR                       ----" << endl;
    cout << "    ------------------------------------------------------------------------------------------" << endl;
    cout << "    ----                                                                                  ----" << endl;
    cout << "    -----********************************************************************************-----" << endl;
    cout << endl;
}
void MenuUsuario() // Función que contiene el cartel pidiendo PIN del cajero
{
    //system("cls");
    cout << endl;
    cout << "    -----*********************************************************************************----" << endl;
    cout << "    -----********************************* CAJERO AUTOMATICO *****************************----" << endl;
    cout << "    -----                               INSERTE SU PIN POR FAVOR                          ----" << endl;
    cout << "    ------------------------------------------------------------------------------------------" << endl;
    cout << "    ----                                                                                  ----" << endl;
    cout << "    -----********************************************************************************-----" << endl;
    cout << endl;
}

void MenuPrincipal() // Función que contiene el cartel general de opciones
{
    //system("cls");
    cout << endl;
    cout << "    -----*********************************************************************************----" << endl;
    cout << "    -----********************************* CAJERO AUTOMATICO *****************************----" << endl;
    cout << "    -----               SELECCIONE EL TIPO DE OPERACION QUE DESEA REALIZAR                ----" << endl;
    cout << "    ------------------------------------------------------------------------------------------" << endl;
    cout << "    ---- 1 * CONSULTAR SALDO                                                             ----" << endl;
    cout << "    -----                                                                                 ----" << endl;
    cout << "    ---- 2 * REALIZAR DEPOSITO                                                            ----" << endl;
    cout << "    -----                                                                                 ----" << endl;
    cout << "    ---- 3 * RETIRO DE EFECTIVO                                                           ----" << endl;
    cout << "    -----                                                                                 ----" << endl;
    cout << "    ---- 4 * REALIZAR TRANSFERENCIA                                                       ----" << endl;
    cout << "    -----                                                                                 ----" << endl;
    cout << "    ---- 5 * CAMBIO DE CLAVE                                                              ----" << endl;
    cout << "    -----                                                                                 ----" << endl;
    cout << "    ---- 0 * SALIR                                                                        ----" << endl;
    cout << "    -----********************************************************************************-----" << endl;
    cout << endl;
}

void LeerPIN(int &PIN, string &alias, vector<Usuario> &ListaUsuarios, bool &pinValido, string cartel) // esta funcion controla el PIN ingresado por el usuario y verifica si esta en la base de datos
{
    pinValido = false;
    bool pinVa = false;
    int intentos = 0;
    do
    {
        pinVa = PinValido(PIN, cartel);        // llama a la funcion que controla que el pin ingresado sea entero y de 4 digitos
        for (Usuario &usuario : ListaUsuarios) // recorremos la lista y nos posicionamos en el usuario logueado
        {
            if (usuario.PIN == PIN && pinVa && usuario.Alias == alias) // controlando que ambos campos de verificacion sean los correctos
            {
                pinValido = true;
            }
        }
        if (!pinValido) // si no es valido muestra un cartel y cuenta las veces que se intento realizar el logueo
        {
            if (intentos < 2)
            {
                cout << "PIN incorrecto. Intente nuevamente." << endl;
            }
            intentos++;
        }
        if (intentos == 3) // cuando llega a 3 intentos fallidos cierra sesion
        {
            cout << "Supero la cantidad de intentos permitidos.." << endl;
            cout << "Cerrando sesion" << endl;
            getch();
        }
    } while (!pinValido && intentos != 3);
}
// Lee el archivo y espera que el usuario ingrese su alias para validarlo
bool MenuAlias(string &alias, vector<Usuario> &ListaUsuarios, bool &aliasValido)
{
    ListaUsuarios = leerArchivoCSV(nombreArchivo); // llama a la funcion para leer el archivo y llenar la lista
    aliasValido = false;

    PantallaAlias();
    cout << "Alias: ";
    cin >> alias;
    for (Usuario &usuario : ListaUsuarios) // recorremos el la lista
    {
        if (usuario.Alias == alias) // buscamos y si encontramos el alias mostramos el saludo con el nombre del usuario
        {
            cout << "Hola " << usuario.Nombre << endl;
            getch();
            aliasValido = true; // si se encontro el alias se cambia a true el alias valido
            break;
        }
    }
    return aliasValido; // devuelve el valor tru o false deacuaerdo a si se encontro o no el alias ingresado
}

bool PinValido(int &pin, string cartel) // esta funcion controla que el PIN sean numeros enteros y 4 digitos
{
    int resto = 0, contador;
    bool valido = false;
    do
    {
        contador = 0;
        pin = IngresoNumeroEntero(cartel); // llama a la funcion que devuelve un numero entero valido ingresado por el usuario
        resto = pin;
        while (resto > 0)
        {
            resto = resto / 10;
            contador++; // cuenta la cantidad de digitos que tiene el numero ingresado
        }
        if (contador != 4)
        {
            cout << "El PIN debe tener cuatro digitos.." << endl;
        }
        else
        {
            valido = true;
        }
    } while (contador != 4);

    return valido; // devuelve true o false si es ingresado un valor valido o no de PIN
}

int IngresoNumeroEntero(string cartel) // Función con la que genero un ingreso con "cartel" de parametro
{
    string cadena;
    int numero;
    bool valido;
    do
    {
        cout << cartel; // muestro el cartel pasado por parametro en la llamada a la funcion
        cin >> cadena;
        valido = numeroValido(cadena, numero); // llamo la funcion numeroValido para controlar que sea un digito correcto la misma al ser booleana me permite realizar el bucle
        if (!valido)
        {
            cout << endl; // para solicitar un nuevo ingreso si es incorrecto
            cout << "Ingreso Incorrecto, intente nuevamente.." << endl;
        }
    } while (!valido); // se repetira el bucle hasta que se ingrese un digito correcto por teclado

    return numero; // la función de tipo entera se lleva el número ingresado como retorno
}

bool numeroValido(string &cadena, int &numero) // función que controla el ingreso por teclado, como parametro recibe un dato de tipo string y
{                                              // devuelve un dato de tipo entero si se ingreso un digito de ese tipo, ademas de cambiar el estado de la funcion a true.
    bool esValido = false, valido = false;     // declaro las variables necesarias para realizar el proceso
    int i = 0, largo = cadena.length();        // declaro un indice y un tope que me lo da el largo del string ingresado

    while (i < largo && !esValido)
    { // con un mietras recorro cada caracter de la cadena y comparo que no sea un caracter difirente de un numero del 0 al 9
        if (cadena[i] != '0' && cadena[i] != '1' && cadena[i] != '2' && cadena[i] != '3' && cadena[i] != '4' && cadena[i] != '5' && cadena[i] != '6' && cadena[i] != '7' && cadena[i] != '8' && cadena[i] != '9')
        {
            esValido = true; // si ingresa en esta condicon es porque encontro un caracter diferente a un numero cualquiera este sea y esto nos saca del ciclo while
        }
        else
        {
            valido = true; // si no encontro ningun caracter diferente a los 10 digitos decimales le asigna true a la variable "valido"
        }
        i++; // incrementa el indice para poder recorrer todo el string
    }
    if (valido)
    { // si la variable "valido" esta en true utilizo la funcion "stoi" que convierte el string a entero y se lo asigno a la variable "numero"
        numero = stoi(cadena);
    }

    return valido; // retorno el valor de la variable "valido"
}
void guardarArchivoCSV(const string &nombreArchivo, const vector<Usuario> &usuarios) // esta funcion se encarga de guardar en el archivo los movimientos realizados
{
    ofstream archivo(nombreArchivo); // se crea el objeto de tipo ofstream para la manipulacion del archivo en modo de escritura
    if (archivo.is_open())
    {
        for (const Usuario &usuario : usuarios) // recorre la lista
        {
            archivo << usuario.Alias << "," // escribe los diferentes campos del struct separados por coma que se añaden entre cada campo
                    << usuario.Nombre << ","
                    << usuario.Apellido << ","
                    << usuario.CBU << ","
                    << usuario.PIN << ","
                    << usuario.Saldo << "\n";
        }
        archivo.close(); // se cierra el archivo
        cout << "Operacion realizada correctamente." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// Función para imprimir el saldo
void MostrarSaldo(string &alias, vector<Usuario> &ListaUsuarios)
{
    //system("cls");
    cout << endl;
    cout << "    -----*********************************************************************************----" << endl;
    cout << "    -----*************************** SU SALDO DISPONIBLE ES: *****************************----" << endl;
    cout << "                                        $ " << BuscarSaldo(alias, ListaUsuarios) << "         " << endl;
    cout << "    ------------------------------------------------------------------------------------------" << endl;
    cout << "    ----                                                                                  ----" << endl;
    cout << "    -----********************************************************************************-----" << endl;
    cout << endl;
}

// Función que devuelve el saldo del usuario
double BuscarSaldo(string &alias, vector<Usuario> &ListaUsuarios)
{
    double saldo;
    for (Usuario &usuario : ListaUsuarios) // recorremos la lista
    {
        if (usuario.Alias == alias) // nos ubicamos en el usuario logueado
        {
            saldo = usuario.Saldo; // le asignamos el saldo del usuario a la variables saldo
            break;
        }
    }
    return saldo; // la funcion retorna el valor del saldo del usuario logueado
}

void HacerRetiro(string &alias, vector<Usuario> &ListaUsuarios) // Funcion que gestiona el retiro de dinero en efectivo del cajero
{
    double NuevoSaldo, SaldoActual, Retiro = 0;
    bool RetiroCorrecto = false;

    SaldoActual = BuscarSaldo(alias, ListaUsuarios); // llama a la funcion para poder mostrar el saldo actual
    cout << "Su saldo actual es: ";
    cout << SaldoActual << endl;
    do
    {
        Retiro = IngresoNumeroDouble("Cuanto dinero desea retirar?: "); // mediante la funcion INgreseNumeroDouble se solicita el monto
        if (Retiro > SaldoActual)
        {
            RetiroCorrecto = false;
            cout << "El monto ingresado supera el saldo disponible." << endl;
        }
        else
        {
            NuevoSaldo = SaldoActual - Retiro; // se calcula el nuevo saldo
            for (Usuario &usuario : ListaUsuarios)
            {
                if (usuario.Alias == alias) // nos ubicamos en la posicion del usuario logueado
                {
                    usuario.Saldo = NuevoSaldo; // se asigna el nuevo saldo
                    cout << "Retire el efectivo." << endl;
                    getch();
                    RegistroMovimientos(usuario.Apellido, usuario.Nombre, " Retiro de Efectivo -", Retiro, usuario.Saldo); // Realiza el registro de la operacion enviando los campos correspondientes
                }
            }

            RetiroCorrecto = true;
        }
    } while (RetiroCorrecto != true);
    cout << "Su saldo actual es: $ ";
    cout << BuscarSaldo(alias, ListaUsuarios) << endl; // muestra el saldo por pantalla
    guardarArchivoCSV(nombreArchivo, ListaUsuarios);   // lllama a la funcion para guardar los cambios en el archnivo
}

void Transferencia(string &alias, vector<Usuario> &ListaUsuarios) // funcion que gestiona la transferencia de dinero a otras cuentas mediante el numero de CBU
{
    string TranferCBU;
    double NuevoSaldo, SaldoActual, Retiro = 0;
    bool CBUencontrado = false, RetiroCorrecto = false;

    SaldoActual = BuscarSaldo(alias, ListaUsuarios); // llama a la funcion BuscarSaldo para mostrar el saldo por pantalla
    cout << "Su saldo actual es: $ ";
    cout << SaldoActual << endl;
    if (SaldoActual == 0) // si no tiene saldo no le permite realizar la transferencia
    {
        cout << "No tiene saldo." << endl;
    }
    else
    {
        do
        {
            Retiro = IngresoNumeroDouble("Cuanto dinero desea transferir?: "); // mediante la llamada a numeroDouble se ingresa el monto a transferir
            cout << endl;
            if (Retiro > SaldoActual) // se controla que el monto ingresado no supere el monto disponible
            {
                RetiroCorrecto = false;
                cout << "El monto ingresado supera el saldo disponible." << endl;
            }
            else
            {
                RetiroCorrecto = true;
            }
        } while (RetiroCorrecto != true); // si el monto a retirar es conrrecto realiza un bucle para solicitar el ingrese del CBU destino

        if (RetiroCorrecto)
        {
            for (Usuario &Cliente : ListaUsuarios) // recorremos la lista
            {
                if (Cliente.Alias == alias) // nos ubicamos en la posicion del usuaria logueado
                {
                    cout << ("Ingrese CBU del destinatario: ");
                    cin >> TranferCBU;

                    for (Usuario &destinatario : ListaUsuarios) // recorremos nuevamente la lista de clientes pero esta vez para buscar el CBU destino
                    {
                        if (destinatario.CBU == TranferCBU && destinatario.CBU != Cliente.CBU) // Sin encontramos el CBU destino que no sea el del Usuario logueado entramos
                        {
                            CBUencontrado = true;
                            cout << "Va a Transferir $" << Retiro << " a " << destinatario.Apellido << " " << destinatario.Nombre << " " << endl;
                            if (ingresoOpcion("Confirma? (Si/No): ")) // mostramos los datos del destinatario de la transferencia y el monto que vamos a transferir
                            {                                         // si acepta la transferencia se realizan las operaciones y luego guardado y registro de las mismas
                                Cliente.Saldo = Cliente.Saldo - Retiro;
                                destinatario.Saldo = destinatario.Saldo + Retiro;
                                guardarArchivoCSV(nombreArchivo, ListaUsuarios);
                                RegistroMovimientos(Cliente.Apellido, Cliente.Nombre, " Transferencia -", Retiro, Cliente.Saldo); // Realiza el registro de la operacion enviando los campos correspondientes
                            }
                            cout << "Saliendo.." << endl;
                        }
                    }
                }
            }
            if (!CBUencontrado)
            {
                cout << "CBU Erroneo!   Saliendo.." << endl;
            }
        }
    }
}

bool ingresoOpcion(string cartel) // Funcion que controla el ingreso por teclado de la opcion(si/no) y devuelve un valor booleano
{
    string ingreso;
    string opcion = "";
    bool op = false;
    do
    {
        opcion = "";
        cout << cartel; // muestra el cartel que se ingreso en la llamada
        cin >> ingreso;

        for (char c : ingreso) // recorre cada caracter del ingreso por teclado
        {
            opcion += tolower(c); // convierte los caracteres a minuscula
        }

    } while (opcion != "no" && opcion != "si"); // el bucle se mantiene hasta que se ingrese por teclado un (si o un no)

    if (opcion == "no")
    {
        op = false; // si la opcion ingresada es "no" devuelve el valor falso a la funcion
    }
    else
    {
        op = true; // si la opcion ingresada es "si" devuelve el valor verdadero a la funcion
    }
    return op;
}

void Deposito(string &alias, vector<Usuario> &ListaUsuarios) // Funcion que gestiona el Deposito de efectivo en la cuenta del usuario
{
    double NuevoSaldo = 0, SaldoActual = 0, deposito = 0;
    bool decision;

    SaldoActual = BuscarSaldo(alias, ListaUsuarios); // llama a la funcion BuscarSaldo para luego mostrarlo en pnatalla
    cout << "Su saldo actual es: ";
    cout << SaldoActual << endl;

    deposito = IngresoNumeroDouble("Cuanto dinero desea depositar?: "); // se solicita el monto del dinero a depositar
    cout << "Va a depositar: $ " << deposito << endl;
    decision = ingresoOpcion("Continua?(Si/No) : ");
    if (decision)
    {
        NuevoSaldo = SaldoActual + deposito;   // se calcula el nuevo saldo
        for (Usuario &usuario : ListaUsuarios) // se recorre la lista
        {
            if (usuario.Alias == alias) // nos ubicamos en el ud=suario logueado
            {
                usuario.Saldo = NuevoSaldo; // realizamos la asignacion del nuevo saldo
                cout << "Deposito Realizado" << endl;
                cout << "Su saldo actual es: $ ";
                cout << BuscarSaldo(alias, ListaUsuarios) << endl;
                getch();                                                                                      // da la opcion de presionar una tecla antes de continuar
                guardarArchivoCSV(nombreArchivo, ListaUsuarios);                                              // guarda los nuevos datos en el archivo
                RegistroMovimientos(usuario.Apellido, usuario.Nombre, " Deposito ", deposito, usuario.Saldo); // genera un registro del movimiento
            }
        }
    }
    else
    {
        cout << "Saliendo.. ";
    }
}

void CambioClave(string &alias, vector<Usuario> &ListaUsuarios) // funcion que gestiona el cambio de PIN del cliente
{
    int Pin;
    bool pinva, pinvalido;
    LeerPIN(Pin, alias, ListaUsuarios, pinvalido, "Ingrese PIN Actual: "); // lla a la funcion LeerPIN para solicitar nuevamente el PIN actual
    for (Usuario &usuario : ListaUsuarios)                                 // recorremos la lista de usuarios
    {
        if (usuario.PIN == Pin) // corroboramos que el pin ingresado es el que corresponde con el usuario logueado
        {
            PinValido(Pin, "Ingrese Nuevo PIN: ");
            usuario.PIN = Pin; // asigna el nuevo PIN al campo correspondiente
            pinva = true;
            RegistroMovimientos(usuario.Apellido, usuario.Nombre, " Cambio de PIN ", 0, 0); // Realiza el registro de la operacion enviando los campos correspondiente
        }
    }
    if (pinva) // si el es correcto se muestra
    {
        cout << "Nuevo PIN registrado con exito" << endl;
        guardarArchivoCSV(nombreArchivo, ListaUsuarios);
    }
    else
    {
        cout << "PIN No coincide" << endl;
    }
}

bool numeroDoubleValido(const string &cadena, double &numero) // Valida que un numero en formato string sea de tipo Double y lo convierte a este formato
{
    bool InValido = false, valido = false;
    int i = 0, largo = cadena.length();
    int puntoCount = 0; // Contador de puntos decimales

    while (i < largo && !InValido)
    {
        if (cadena[i] != '.' && (cadena[i] < '0' || cadena[i] > '9'))
        {
            InValido = true; // Se encontró un caracter inválido (diferente de '.' y dígitos)
        }
        else if (cadena[i] == '.')
        {
            puntoCount++;
            if (puntoCount > 1)
            {
                InValido = true; // Se encontró más de un punto decimal
            }
        }
        else
        {
            valido = true; // Se encontró un dígito válido
        }
        i++;
    }

    if (valido && !InValido && puntoCount <= 1) // si cumple todas las condiciones se pasa a realizar el cambio de cadena a double
    {
        numero = stod(cadena); // Se convierte la cadena a double
        return true;           // retorna verdadera la funcion
    }
    return false; // si no cumple con las condiciones va a retoranar falso la funcion
}

double IngresoNumeroDouble(string cartel) // llama a la funcion que tranasforma un string a Double y lo devuelve a la funcion
{                                         // de esta manera es mas sencilla su utilizacion en las llamadas.
    string cadena;
    double numero;
    bool valido;
    do
    {
        cout << cartel;
        cin >> cadena;
        valido = numeroDoubleValido(cadena, numero); // llama a la funcion numeroDoubleValido para validar el ingreso y devolver el campo en formato double y el valor tru o false de dicho ingreso
        if (!valido)
        {
            cout << endl;
            cout << "Ingreso incorrecto, intente nuevamente.." << endl;
        }
    } while (!valido);

    return numero;
}
void RegistroMovimientos(string apellido, string nombre, string operacion, double mov, double saldo)
{ // Esta funcion graba los movimientos en un archivo de registro txt, si no existe lo crea
    time_t now = time(0);
    string Fecha = ctime(&now);
    ofstream archivo;
    archivo.open("Registro.txt", ios::app); // Abrir el archivo en modo de anexar

    if (archivo.fail())
    { // si hay un error en el archivo se mostrara un cartel
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }
    archivo << "------------------------------------------" << endl; // imprime en el archivo txt los campos siguientes
    archivo << "Fecha y Hora: " << Fecha;
    archivo << "Nombre: " << apellido << " " << nombre << endl;
    archivo << "Movimiento: " << operacion << mov << endl;
    archivo << "Saldo: $ " << saldo << endl;
    archivo.close(); // Cerrar el archivo
}