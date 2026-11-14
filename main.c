#include <stdio.h>
#include <string.h>

void adicionar(){
    FILE*arquivo;
    arquivo=fopen("inventory.txt","a");
    
    if(arquivo==NULL){
        printf ("erro ao abrir o arquivo");
        return;
    }
    char nome[50];
    int quant;
    printf ("Digite o nome do Item:");
    getchar();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome,"\n")]='\0';
    
    printf ("Digite a quantidade:");
    scanf ("%d", &quant);
    fprintf (arquivo,"%s\n %d\n", nome, quant);
    fclose (arquivo);
    printf ("Item adicionado com sucesso!\n");
}

int carregarItens(
    char nome[100][50],
    int quant[100]){
    FILE*arquivo;
        arquivo=fopen("inventory.txt","r");
        if (arquivo==NULL){
            printf ("Erro ao abrir o arquivo");
            return -1;
        }
        int contador=0;
        
        while (fgets(nome[contador],100,arquivo)!=NULL){
            nome[contador][strcspn(nome[contador],
            "\n")]='\0';
            if(fscanf(arquivo,"%d",&quant[contador])!=1){
                break;
            }
            fgetc(arquivo);
            contador++;
        }
        fclose(arquivo);
        return contador;
}

int removerItens(char nome[100][50],
    int quant[100], int contador){
        char nome2[50];
        int quantidadeRemover;
        
        printf("Digite o nome do Item:");
        getchar();
        fgets(nome2,sizeof(nome2),stdin);
        nome2[strcspn(nome2,"\n")]='\0';
        
        printf("Digite a quantidade a ser removida:");
        scanf("%d",&quantidadeRemover);
        
        int encontrado=0;
        for(int i=0; i<contador; i++){
            if (strcmp(nome[i], nome2)==0){
                encontrado=1;
                if(quantidadeRemover <= quant[i]){
                    quant[i]= quant[i]-quantidadeRemover;
                    if (quant[i]==0){
                        for (int j=i+1; j<contador; j++){
                            strcpy(nome[j-1], nome[j]);
                            quant[j-1]=quant[j];
                        }
                        contador--;
                        printf("Item removido do estoque!\n");
                    } else {
                        printf("Quantidade atualizada com sucesso!\n");
                    }
                } else {
                    printf("Estoque insuficiente.");
                    printf("Quantidade disponivel: %d\n", quant[i]);
                } break;
            }
        } if (encontrado==0){
            printf("Item não encontrado.\n");
        }
        return contador;
    
}
void salvarItens(char nome[100][50], int quant[100],
int contador){
    FILE*arquivo;
    arquivo=fopen("inventory.txt","w");
    if (arquivo==NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    for (int i=0; i<contador; i++){
        fprintf(arquivo, "%s\n %d\n", nome[i], quant[i]);
    }
    fclose(arquivo);
}
void listar(){
    
    FILE*arquivo;
    arquivo=fopen("inventory.txt","r");
    if (arquivo==NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    printf ("========================\n");
    printf ("  Estoque atual\n");
    printf ("========================\n");
    
    char nome[50];
    int quant, contador=0;
   while (fgets(nome,sizeof(nome), arquivo)!=NULL){
       
       nome [strcspn(nome,"\n")]='\0';
       if (fscanf(arquivo,"%d",&quant)!=1){
           break;
       }
        printf ("Nome: %s\n", nome);
        printf ("Quantidade: %d\n", quant);
        contador++;
       fgetc(arquivo);
    }
    if (contador==0){
        printf("O estoque está vazio.\n");
    }
    fclose(arquivo);
}
void sair(){
    printf("Obrigado por usar o controle de Estoques! Até a próxima.");
}


int main() {
    char nome[100][50];
    int quant[100];
     float n;
    char resposta;
    
   do {
       printf ("===========================\n");
    printf("   Controle de Estoques\n");
    printf ("===========================\n");
    printf("Selecione uma opção:\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Estoque\n");
    printf("4. Sair\n");
    printf("Opção:");
    
    do {
        if (scanf ("%f", &n)!=1){
            printf ("Entrada invalida! Tente novamente.");
            while (getchar() != '\n');
            n = 0;
        }
    else if  (n<1 || n>4 || n!=(int)n){
        printf ("Entrada invalida! Tente novamente.");
    }
    } while (n<1 || n>4 || n!=(int)n);
    
    if (n==1){
        adicionar();
    }
    else if (n==2){
        int contador=carregarItens(nome,quant);
       if (contador!=-1){ 
           contador = removerItens(nome,quant,contador);
        salvarItens(nome,quant,contador);
       }
    }
    else if(n==3){
        listar();
    }
    else if (n==4){
        sair();
        return 0;
    }
    if (n>=1 && n<=3){
            printf("Deseja realizar outra operação?(s/n)");
            scanf(" %c", &resposta);
        if (resposta!='s'){
            sair();
            return 0;
        }
    }
   } while (resposta=='s');
    return 0;
}
