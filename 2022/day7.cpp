#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

/*Comandos a implementar
cd / -> retorno a ruta base
cd .. retorno a ruta anterior inmediata
cd x ingreso a una en especifico
ls listar elementos */

long solver(std::vector<std::string> input) {

	//ruta actual
	vector<string> directorio;
	//eda para nombres y sizes (archivos)
	map<string, long> mapsizes;
	long sumaTotal = 0;

	//CORRIMIENTO de la línea
	for (const string& linea : input) {
		//comandos de cd, armado de arbol (CASO 0: Linea empieza con CD)
		if (linea.substr(0, 4) == "$ cd") {
			string destino = linea.substr(5);
			if (destino == "/") directorio = { "/" };
			else if (destino == "..") {
				if (!directorio.empty()) {
					directorio.pop_back();
				}
			}
			else {
				string newdir = (directorio.empty()) ? "" : directorio.back();
				directorio.push_back(newdir + destino + "/");
			}
		}

		//CASO 1: es un archivo, 123 abc file named abc, size 123
		if (isdigit(linea[0])) {
			long sizearch = stol(linea.substr(0, linea.find(" ")));
			for (const string& ruta : directorio) {
				mapsizes[ruta] += sizearch;
			}
		}

	} // A este punto tenemos el arbol ordenado con los sizes en cada uno de los maps

	for (auto const& [ruta, tamano] : mapsizes) {
		if (tamano <= 100000) {
			sumaTotal += tamano;
		}
	}
	return sumaTotal;
}
int main() {

	cout << "Carpeta actual: " << std::filesystem::current_path() << endl;
	ifstream inputFile("input.txt.txt");
	if (!inputFile.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
		return 1;
	}

	vector<string> lines;
	string line;
	while (getline(inputFile, line)) {
		lines.push_back(line);
	}

	cout << "Resultado Final: " << solver(lines) << endl;
	return 0;
}