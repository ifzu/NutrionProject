//MENIU NUTRITIONAL
//bazat pe tabelul cu alimente "tabel_nutrienti"
//Se introduc produsele gramajul => se obtin nutrientii pentru fiecare produs
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define MAX 10000 //nr produse maxim
#define LEN 100 //lungime sir max
FILE* f; //pentru detalii gen numere
FILE *g; //pentru alimente
int numberOfAl;

typedef struct Tabel{
	double proprietati[18];
}Tabel;

typedef struct Aliment{
	char nume[200];
}Aliment;

Aliment aliment[300];
Tabel tabel[300];

char *removeDuplicates(char* sir, int len){
	int i;
	int index = 0;
	for (i = 0; i < len; i++){
		int j;
		for (j = 0; j < i;j++)
		if (sir[i] == sir[j])
			break;

		if (j == i)
			sir[index++] = sir[i];
		
	}

	return sir;
}

char* removeDoubleSpaces(char* str){
	int nr = 0;
	int i;
	char* p = (char*)malloc(strlen(str));
	int k = 0;

	for (i = 0; i < strlen(str); i++){
		if (str[i] == ' ')
			nr++;

		if (nr == 2){
			nr = 0;
			continue;
		}
		
		p[k++] = str[i];
	}
	p[k] = '\0';
	return p;
}

char* replaceTabsWithSpaces(char* source){
	char* aux = (char*)malloc(sizeof(char)* 100);
	int contor = 0;
	for (int i = 0; i < strlen(source); i++){
		if (source[i] == '\t'){
			aux[contor++] = ' ';
			continue;
		}
		aux[contor++] = source[i];
	}
	aux[contor] = '\0';
	return aux;
}

void printLetterByLetter(char* str){
	for (int i = 0; i < strlen(str); i++)
		printf("%c\n", str[i]);
	
}
void removeSpaces(char *str)
{

	int count = 0;

	
	for (int i = 0; str[i]; i++)
	if (str[i] != ' ')
		str[count++] = str[i]; 
	str[count] = '\0';
}

void citire_produse(){
	if ((g = fopen("produse.txt", "r")) == NULL){
		printf("Eroare la deschidere fisier");
		exit(1);
	}
	
	while (!feof(g)){
		char* pos;
		char buffer[150];
		fgets(buffer, 150, g);
		removeSpaces(buffer);
		if ((pos = strchr(buffer, '\n')) != NULL)
			*pos = '\0';
		strcpy(aliment[numberOfAl].nume, buffer);
	//	tabel[numberOfAl].aliment[strlen(buffer)-1] = '\0';
		numberOfAl++; 
	}
	fclose(g);

}


void citire_valori(){
	if ((f = fopen("nutr.txt", "r")) == NULL){
		printf("Eroare la deschidere fisier");
		exit(1);
	}
	

	for (int i = 0; i < 172; i++){
		int k = 0;
		
		char* pos;
		char* buffer = (char*)malloc(sizeof(char)* 100);
		fgets(buffer, 100, f);
		buffer = replaceTabsWithSpaces(buffer);
		char *p = strtok(buffer, " ");
		while (p){
			double temp = strtod(p, NULL);
			tabel[i].proprietati[k] = temp;
			k++;
			p = strtok(NULL, " ");
		}

	}
	fclose(f);
}


void main_routine(char* tab[],int n,float* gramaje){
	float suma[18];
	for (int i = 0; i < 18; i++)
		suma[i] = 0;

   	for (int i = 0; i < n; i++){
		for (int j = 0; j < numberOfAl; j++){
			if (strstr(aliment[j].nume, tab[i])){
				float rez = 0;
				printf("%s ", aliment[j].nume);
				for (int m = 0; m < 18; m++){
					
					rez = (gramaje[i] *tabel[j].proprietati[m]) / 100;
					suma[m] += rez;
					printf("%.3f ", rez);
				} 
				printf("\n"); 
			}

		}
	}  

	printf("\nTOTAL:\n");
	for (int i = 0; i < 18; i++)
		printf("%.3f ", suma[i]);
}





int main(){
	char *string_database[10] = { '\0' };
	int contor = 0;
	char buffer[300] = " ";
	float gramaje[100];
	
	citire_produse(); //citire produse
	
	citire_valori(); //citire valori
	printf("PASI DE URMAT\n");
	printf("1.Se introduc numele alimentelor din tabel fara spatiu intre ele de exemplu:'painealba'\n");
	printf("Se apasa enter si se introduce urmatorul produs\n");
	printf("Pentru a se oprirea introducerea produselor se introduce EOF\n");
	printf("2.Se introduc gramajele folosind . inloc de , pentru numere rationale\n");
	
	while (strcmp(buffer, "EOF") != 0){
		fgets(buffer, 30, stdin);
		char *pos;
		if ((pos = strchr(buffer, '\n')) != NULL)
			*pos = '\0';
		if (strcmp(buffer, "EOF") == 0)
			break;

		string_database[contor] = (char*)malloc(sizeof(char)*strlen(buffer));
		strcpy(string_database[contor], buffer);
		contor++;
		printf("\n");
	}  
	printf("Introduceti gramajele:\n");
	for (int i = 0; i < contor; i++)
		scanf("%f", &gramaje[i]);
	//system("cls");
	main_routine(string_database, contor,gramaje);    


	return 0;
	
}