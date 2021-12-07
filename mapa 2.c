#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct stdados{
	int PROD_CODI;
	int ORG_CODI;
	char PROD_NOME [100];
	char ORG_NOME[100];
	char ORG_NABREV[100];
	char PRODT_DESCR[100];

}stregistro;

void imprimirOriginal(stregistro* dados, int n){

	int i;
	for(i=0;i<n;i++){
		printf("%-6d",dados[i].PROD_CODI);
		printf("%-6d",dados[i].ORG_CODI);
		printf("%-30s",dados[i].PROD_NOME);
		printf("%-80s\t",dados[i].ORG_NOME);
		printf("%-30s",dados[i].ORG_NABREV);
		printf("%-30s",dados[i].PRODT_DESCR);
		printf("\n");
	}
	//printf("\n");
}

int main(){

	setlocale(LC_ALL,"Portuguese");

	int tamanho = 5000;
	int countLinhas = 0;
	int contador = 0, qtd = 0, linha =0;

	char auxArquivo[1024];
	char buf[1024];
	stregistro* dados;

	FILE *arq = fopen("ProdutosAeronauticos_Fabricantes.csv","r");

	dados = (stregistro*)malloc(sizeof(stregistro)* 5000);

	if(arq == NULL)
		printf("Arquivo não encontrado");

	while(fgets(buf,1024,arq)){
		contador = 0;
		countLinhas++;

		if(countLinhas == 1) continue;

		char *campo = strtok(buf, ";");
		while(campo){
			if(contador == 0)	{
				strcpy(auxArquivo,campo);
				dados[linha].PROD_CODI = atoi(auxArquivo);
			}

			if(contador == 1){
				strcpy(auxArquivo,campo);
				dados[linha].ORG_CODI = atoi(auxArquivo);;
			}

			if(contador == 2){
			strcpy(auxArquivo,campo);
				strcpy(dados[linha].PROD_NOME,auxArquivo);
			}

			if(contador == 3){
				strcpy(auxArquivo,campo);
				strcpy(dados[linha].ORG_NOME,auxArquivo);
			}

			if(contador == 4){
				strcpy(auxArquivo,campo);
				strcpy(dados[linha].ORG_NABREV,auxArquivo);
			}

			if(contador == 5){
				strcpy(auxArquivo,campo);
				strcpy(dados[linha].PRODT_DESCR,auxArquivo);
			}

			campo = strtok(NULL,";");
			contador++;
		}
			linha++;
	}

	mergeSort(dados, countLinhas-1, qtd);
	imprimirOriginal(dados, countLinhas);



	fclose(arq);
	return 0;
}
void junta(stregistro* dados, int tam) {

	int i, j, k;
	int meio;

	stregistro* tmp;

	tmp = (stregistro*)malloc(sizeof(stregistro)* tam);

	if (tmp == NULL) {
		exit(1);
	}
	meio = tam / 2;
	i = 0;
	j = meio;
	k = 0;
	while (i < meio && j < tam) {

		if (dados[i].PROD_CODI < dados[j].PROD_CODI) {
			tmp[k] = dados[i];
			++i;
		}
		else {

			tmp[k] = dados[j];
			++j;
		}
		++k;
	}
	if (i == meio) {
		while (j < tam) {

			tmp[k] = dados[j];
			++j;
			++k;
		}
	}
	else {
		while (i < meio) {

			tmp[k] = dados[i];
			++i;
			++k;
		}
	}
	for (i = 0; i < tam; ++i) {

		dados[i] = tmp[i];
	}

	free(tmp);
}


	int mergeSort(stregistro* dados, int tam, int qtd) {
	int meio;
	if (tam > 1) {
		meio = tam / 2;
		qtd = mergeSort(dados, meio, qtd);
		qtd = mergeSort(dados + meio, tam - meio, qtd);
		junta(dados, tam);
	}

	return(qtd+1);
}




