#include<iostream>
#include<stdlib.h>
#include<conio.h>

/*UFA-ESPE
* Crear un programa que realice una sobrecarga del operador &&
* Dylan Tipán, Jeremy Cadena
* 15/05/2022
* 15/05/2022
* Grupo 14
* https://github.com/JeremyCadena/Grupo-14-Estructura-de-Datos-4683 efsolis@espe.edu.ec
*/

using namespace std;
double nota1,nota2,nota3;
class Asignatura{
	private:
		double nota1, nota2, nota3;
	public:
		Asignatura(double,double,double);
		bool operator&&(Asignatura M2);
		
};

int main(){
	Asignatura Materia1(11.56,14.10,18.67), Materia2(14.86,17.36,19.24);
	if(Materia1&&Materia2){
		cout<<"La materia 2 tiene un mejor promedio"<<endl;
	}
	else{
		cout<<"La materia 1 tiene un mejor promedio"<<endl;
	}
	return 0;
}

Asignatura::Asignatura(double nt1,double nt2,double nt3){
	nota1=nt1;
	nota2=nt2;
	nota3=nt3;
}

bool Asignatura::operator&&(Asignatura M2){
	if((nota1+nota2+nota3)/3<(M2.nota1+M2.nota2+M2.nota3)){
		return true;
	}
	else{
		return false;
	}
}
