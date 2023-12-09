/*****************************************************************************************************************
	
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO

	FACULTAD DE ESTUDIOS SUPERIORES ARAGON

	Computadoras y programacion.

	Guillen Hernandez Valeria Guadalupe 321214393

******************************************************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "corrector.h"
#include "stdafx.h"
#define LONGI 32

char abecedario[LONGI + 6] = "abcdefghijklmnñopqrstuvwxyzáéíóú";

/*****************************************************************************************************************

	DICCIONARIO
	char *	szNombre				:	Archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Palabras completas del diccionario
	int		iEstadisticas[]			:	Numero de veces que aparecen las palabras en el diccionario
	int &	iNumElem			:	Num. de elementos en el diccionario

******************************************************************************************************************/

//inicio

void Diccionario
(
	char* szNombre, 
	char szPalabras[][TAMTOKEN],
	int iEstadisticas[], 
	int& iNumElem
)
{
   //arch

	FILE* fp;
	iNumElem = 0;
	int i;

	//datos 

	char lectura, array[TAMTOKEN];

	//arr

	for (i = 0; i < NUMPALABRAS; i++)
		iEstadisticas[i] = 0;

	//arch

	fopen_s(&fp, szNombre, "r");

	//
 
	int contador = 0;

	//sign de punt

	char puntuacion[] = " \t\n\r.,;() ";
	

	//
	 
	if (fp == NULL)
		return;

	
	while ((lectura = fgetc(fp)) != EOF) 
	{
		//

		bool bandera = true;

			//signos de puntuacion 

			if (puntuacion[i] == lectura)
				bandera = false;

		
		if (contador < TAMTOKEN && bandera) {

			// minusculas 

			lectura = tolower(lectura);


			for (i = 0; i < strlen(puntuacion); i++)

			//

			array[contador++] = lectura;
			continue;
		}

		//

		else if (contador == 0)
			continue;

		
		else if (contador == 1 && bandera) 
		{
			contador = 0;
			continue;
		}

		array[contador] = '\0';

		//abecedario 

		for (i = 0; i < iNumElem && !bandera; i++) 
		{

			//compara palabras

			if (strcmp(szPalabras[i], array) == 0) 
			{
				iEstadisticas[i]++;
				bandera = true;
			}
		}
		
		if (!bandera) {

		//szPalabras
		 
			strcpy_s(szPalabras[iNumElem], array);
			iEstadisticas[iNumElem++]++;

		}
		contador = 0;
	}   //

	fclose(fp);


	//

	for (int j = 0; j < iNumElem - 1; j++) 
	{

		for (i = j + 1; i < iNumElem; i++) 
		{

			if (strcmp(szPalabras[j], szPalabras[i]) > 0) 
			{
				strcpy_s(array, szPalabras[j]);
				strcpy_s(szPalabras[j], szPalabras[i]);
				strcpy_s(szPalabras[i], array);
				contador = iEstadisticas[j];
				iEstadisticas[j] = iEstadisticas[i];
				iEstadisticas[i] = contador;
			}
		}
	}
	//

}
//fin

/*****************************************************************************************************************

	char *	szPalabraLeida,						//Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Num. de elementos en la lista

******************************************************************************************************************/

void	ClonaPalabras
(
	char* szPalabraLeida
	char  szPalabrasSugeridas[][TAMTOKEN]
	int& iNumSugeridas
)
{
    //variable

	char aux[TAMTOKEN]; iNumSugeridas = 0;

	//

	strcpy_s(aux, szPalabraLeida);

	//

	for (int i = 0; i < strlen(szPalabraLeida); i++) {

		for (int j = 0; j < LONGI; j++) {
			aux[i] = abecedario[j];

		//lista de palabras

			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		} aux[i] = szPalabraLeida[i];
	}

	//

	int k;
	for (k = 1; k < strlen(szPalabraLeida) + 1; k++) {
		aux[k] = szPalabraLeida[k - 1];

		//espacios 

	} aux[k] = '\0';

	for (int i = 0; i < strlen(szPalabraLeida) + 1; i++) {

		for (int j = 0; j < LONGI; j++) {
			aux[i] = abecedario[j];
			
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}

		aux[i] = szPalabraLeida[i];
	}
	//

	int contador = 0;
	for (int i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {

		for (int j = 0; j < strlen(szPalabraLeida); j++) {
			if (j != i)
				aux[contador++] = szPalabraLeida[j];

			
		} aux[contador] = '\0';
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);

		//

		strcpy_s(aux, szPalabraLeida);

		contador = 0;
	}
	//
	for (int i = 0; i < strlen(szPalabraLeida) - 1; i++) {
		aux[i] = szPalabraLeida[i + 1];
		aux[i + 1] = szPalabraLeida[i];

		
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		//
		strcpy_s(aux, szPalabraLeida);
	}
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);


	//

	for (int j = 0; j < iNumSugeridas - 1; j++) {

		for (int i = j + 1; i < iNumSugeridas; i++) {

			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
			   
				strcpy_s(aux, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
				strcpy_s(szPalabrasSugeridas[i], aux);
			}
		}
	}


}
/*****************************************************************************************************************
	
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista de palabras a sugerir
	int		iPeso[],							//Peso de las palabras 
	int		iNumSugeridas,						//Lista de palabras clonadas
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElem,						//Num. de elementos en el diccionario
	int &	iNumLista)							//Num. de elementos en la szListaFinal


******************************************************************************************************************/

void	ListaCandidatas
(
	char	szPalabrasSugeridas[][TAMTOKEN]
	int		iNumSugeridas
	char	szPalabras[][TAMTOKEN]
	int		iEstadisticas[]
	int		iNumElem
	char	szListaFinal[][TAMTOKEN]
	int		iPeso[]
	int& iNumLista
)
{
	// 
	iNumLista = 0;
	for (int i = 0; i < iNumSugeridas; i++)
	{
		for (int j = 0; j < iNumElem; j++)
		{

			//compara palabras 

			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0)
			{
				//

				bool bandera = false;
				for (int k = 0; k < iNumLista && !bandera; k++)

					if (strcmp(szListaFinal[k], szPalabras[j]) == 0)
						bandera = true;

				if (bandera) continue;

				//

				strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista++] = iEstadisticas[j];
			}
		}
	}

	//
	 
	for (int i = 0; i < iNumLista; i++)
	{
		for (int j = 0; j < iNumLista - 1; j++)
		{
			if (iPeso[j] < iPeso[j + 1])
			{

				int iaux; char caux[50];
				strcpy_s(caux, szListaFinal[j + 1]); iaux = iPeso[j + 1];
				strcpy_s(szListaFinal[j + 1], szListaFinal[j]); iPeso[j + 1] = iPeso[j];
				strcpy_s(szListaFinal[j], caux); iPeso[j] = iaux;
			}
		}
	}
}
