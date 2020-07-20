#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk-3.0/gtk/gtk.h>
#include "cardapio.h"
//estrutura do prato
struct prato{
  int id;
  char nome[100];
  float preco;
};

//estrutura do cardapio
struct cardapio{
 char nome[100];
 int qtdPratos;
};
//funcao para adicionar um novo cardapio
void adicionar_cardapio(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrNomeCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"idNomeCardapio"));
    if(strcmp(gtk_entry_get_text(etrNomeCardapio),"")!=0){
        int qtdPratos = qtd_pratos(qtd_cardapios());
        char nomeCardapio[100];
        strcpy(nomeCardapio,gtk_entry_get_text(etrNomeCardapio));
        if(qtdPratos!=0){
            Cardapio c;

            c.qtdPratos = qtdPratos;
            strcpy(c.nome,nomeCardapio);

            salvar_cardapio(&c);
            load_pratos(builder);
            gtk_entry_set_text(etrNomeCardapio,"");
            tela_sucesso(builder,"O cardapio foi adicionado com sucesso!");
        }else{
            tela_aviso(builder,"O cardapio nao pode ser cadastrado sem pratos ");
        }
    }else{
        tela_aviso(builder,"Para cadastrar o cardapio e necessario um nome");
    }
}
//funcao para apagar cardapio
void apagar_cardapio(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrNome = GTK_WIDGET(gtk_builder_get_object(builder,"etrNomeDeletarCardapio"));
    GtkWidget *numeroCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"numeroCardapio"));
    char nome[100];
    strcpy(nome,gtk_entry_get_text(etrNome));
    int idx = pesquisar_cardapio(nome,builder);
    if(idx!=-1){
        int qtdCardapios = qtd_cardapios();
        Cardapio *cardapios = (Cardapio *) malloc(qtdCardapios*sizeof(Cardapio));
        ler_cardapios(cardapios,qtdCardapios);
        if(idx == qtdCardapios-1){
            zerar_pratos(qtdCardapios-1,builder);
        }else{
            int qtdPratos = qtd_pratos(qtdCardapios-1);
            cardapios[idx] = cardapios[qtdCardapios-1];
            Prato *pratos = (Prato *) malloc(qtdPratos*sizeof(Prato));
            ler_pratos(qtdCardapios-1,pratos,qtdPratos);
            salvar_pratos(idx,pratos,qtdPratos);
            zerar_pratos(qtdCardapios-1,builder);
        }
        char numero[10];
        snprintf(numero,10,"%d",1);
        gtk_label_set_text(numeroCardapio,numero);
        salvar_cardapios(cardapios,qtdCardapios-1);
        load_dados_cardapios(button,builder);
        gtk_entry_set_text(etrNome,"");
        tela_sucesso(builder,"O cardapio foi deletado com sucesso");
    }else{
        tela_aviso(builder,"O cardapio nao foi encontrado");
    }
}
//funcao para editar um prato de um cardapio
void editar_cardapio(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrNomeCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"etrNomeCardapioedt"));
    int idx = pesquisar_cardapio(gtk_entry_get_text(etrNomeCardapio),builder);
    if(idx!=-1){
        int qtdCardapios = qtd_cardapios();
        Cardapio *cardapios = (Cardapio *) malloc(qtdCardapios*sizeof(Cardapio));
        ler_cardapios(cardapios,qtdCardapios);

        Prato *pratos = (Prato*) malloc(cardapios[idx].qtdPratos*sizeof(Prato));
        ler_pratos(idx,pratos,cardapios[idx].qtdPratos);

        GtkWidget *etrNumeroPrato = GTK_WIDGET(gtk_builder_get_object(builder,"etrNumeroPratoedt"));
        int idxPrato = busca_binaria_pratos(atoi(gtk_entry_get_text(etrNumeroPrato)),0,cardapios[idx].qtdPratos-1,pratos);
        if(idxPrato!=-1){
            GtkWidget *etrNomePrato = GTK_WIDGET(gtk_builder_get_object(builder,"etrNomePratoNovo"));
            GtkWidget *etrPrecoPrato = GTK_WIDGET(gtk_builder_get_object(builder,"etrPrecoPratoNovo"));
            if(strcmp(gtk_entry_get_text(etrNomePrato),"")!=0 && strcmp(gtk_entry_get_text(etrPrecoPrato),"")!=0){
                float precoNovo = atof(gtk_entry_get_text(etrPrecoPrato));
                if(precoNovo!=0){
                    strcpy(pratos[idxPrato].nome,gtk_entry_get_text(etrNomePrato));
                    pratos[idx].preco = precoNovo;
                    salvar_pratos(idx,pratos,cardapios[idx].qtdPratos);
                    gtk_entry_set_text(etrNomeCardapio,"");
                    gtk_entry_set_text(etrNumeroPrato,"");
                    gtk_entry_set_text(etrNomePrato,"");
                    gtk_entry_set_text(etrPrecoPrato,"");
                    load_dados_cardapios(button,builder);
                    tela_sucesso(builder,"O prato foi alterado com sucesso!");
                }else{
                    tela_aviso(builder,"O preco do prato nao pode ser 0 ou conter letras");
                }
            }else{
                tela_aviso(builder,"e necessario digitar o novo nome e preco do prato ");
            }
        }else{
            tela_aviso(builder,"O id do prato informado nao foi encontrado no cardapio");
        }
    }else{
        tela_aviso(builder,"O cardapio informado nao existe!");
    }
}
//funcao para adicionar um prato ao cardapio
void add_prato(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrNomePrato = GTK_WIDGET(gtk_builder_get_object(builder,"idNomePrato"));
    GtkWidget *etrPrecoPrato = GTK_WIDGET(gtk_builder_get_object(builder,"idPrecoPrato"));
    float preco = atof(gtk_entry_get_text(etrPrecoPrato));
    if(preco!=0){
        Prato p = {qtd_pratos(qtd_cardapios())+1};
        strcpy(p.nome,gtk_entry_get_text(etrNomePrato));
        p.preco = preco;
        salvar_prato(qtd_cardapios(),&p);
        load_prato(builder);
        gtk_entry_set_text(etrNomePrato,"");
        gtk_entry_set_text(etrPrecoPrato,"");
        tela_sucesso(builder,"Prato adicionado com sucesso!");
    }else{
        tela_aviso(builder,"O prato nao pode custar 0 e nao aceita letras");
    }
}
//funcao para carregar os dados do cardapio
void load_dados_cardapios(GtkWindow *window,GtkBuilder *builder){
    GtkWidget *numeroCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"numeroCardapio"));
    int qtdCardapios = qtd_cardapios();
    if(qtdCardapios>0){
        //pegando o numero do cardapio convertido
        int numero = atoi(gtk_label_get_text(numeroCardapio))-1;
        //alocando memoria para os cardapios
        Cardapio *cardapios =(Cardapio*) malloc(qtdCardapios*sizeof(Cardapio));
        ler_cardapios(cardapios,qtdCardapios);

        //pegando e colocando o nome do cardapio no label de nome
        GtkWidget *nomeCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"idTextoNomeCardapio"));
        gtk_label_set_text(nomeCardapio,cardapios[numero].nome);

        //lendo os pratos do arquivo daquele cardapio
        Prato *pratos = (Prato *) malloc(cardapios[numero].qtdPratos*sizeof(Prato));
        ler_pratos(numero,pratos,cardapios[numero].qtdPratos);
        //pegando os labels da listagem
        GtkWidget *idPrato = GTK_WIDGET(gtk_builder_get_object(builder,"idListPratosCard"));
        gtk_label_set_text(idPrato,"");
        GtkWidget *nomePrato = GTK_WIDGET(gtk_builder_get_object(builder,"nomeListPratosCard"));
        gtk_label_set_text(nomePrato,"");
        GtkWidget *precoPrato = GTK_WIDGET(gtk_builder_get_object(builder,"precoListPratosCard"));
        gtk_label_set_text(precoPrato,"");
        int i;
        //variaveis para guardar os valores dos pratos
        char id[cardapios[numero].qtdPratos*5];
        char nome[cardapios[numero].qtdPratos*100];
        char preco[cardapios[numero].qtdPratos*30];
        //preenchendo os itens do cardapio na listagem na tela de cardapios
        for(i=0;i<cardapios[numero].qtdPratos;i++){

            snprintf(id,5,"%d\n",pratos[i].id);
            strcat(id,gtk_label_get_text(idPrato));
            gtk_label_set_text(idPrato,id);

            snprintf(nome,100,"%s\n",pratos[i].nome);
            strcat(nome,gtk_label_get_text(nomePrato));
            gtk_label_set_text(nomePrato,nome);

            snprintf(preco,30,"RS%.2f\n",pratos[i].preco);
            strcat(preco,gtk_label_get_text(precoPrato));
            gtk_label_set_text(precoPrato,preco);
        }
        free(pratos);
        free(cardapios);
    }else{
        GtkWidget *nomeCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"idTextoNomeCardapio"));
        gtk_label_set_text(nomeCardapio,"");
        GtkWidget *idPrato = GTK_WIDGET(gtk_builder_get_object(builder,"idListPratosCard"));
        gtk_label_set_text(idPrato,"");
        GtkWidget *nomePrato = GTK_WIDGET(gtk_builder_get_object(builder,"nomeListPratosCard"));
        gtk_label_set_text(nomePrato,"");
        GtkWidget *precoPrato = GTK_WIDGET(gtk_builder_get_object(builder,"precoListPratosCard"));
        gtk_label_set_text(precoPrato,"");
    }
}
//funcao para passar para o proximo cardapio
void proximo_cardapio(GtkButton *button,GtkBuilder *builder){
    GtkWidget *numeroCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"numeroCardapio"));
    int numero = atoi(gtk_label_get_text(numeroCardapio))+1;
    if(numero>qtd_cardapios()){
        numero=1;
    }
    char numeroTxt[5];
    itoa(numero,numeroTxt,10);
    gtk_label_set_text(numeroCardapio,numeroTxt);
    load_dados_cardapios(button,builder);
}
//funcao para passar para o cardapio anterior
void cardapio_anterior(GtkButton *button,GtkBuilder *builder){
    GtkWidget *numeroCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"numeroCardapio"));
    int numero = atoi(gtk_label_get_text(numeroCardapio))-1;
    if(numero<1){
        numero=qtd_cardapios();
    }
    char numeroTxt[5];
    itoa(numero,numeroTxt,10);
    gtk_label_set_text(numeroCardapio,numeroTxt);
    load_dados_cardapios(button,builder);
}
//funcao que carrega os pratos na tela de listagem dos cardapios
void load_pratos(GtkBuilder *builder){
    //pegando os labels da tela de listagem dos pratos
    GtkWidget *lblId = GTK_WIDGET(gtk_builder_get_object(builder,"idPrato"));
    gtk_label_set_text(lblId,"");
    GtkWidget *lblNome = GTK_WIDGET(gtk_builder_get_object(builder,"idNome"));
    gtk_label_set_text(lblNome,"");
    GtkWidget *lblPreco = GTK_WIDGET(gtk_builder_get_object(builder,"idValor"));
    gtk_label_set_text(lblPreco,"");
    int qtdPratos = qtd_pratos(qtd_cardapios());
    if(qtdPratos!=0){
        Prato *pratos = (Prato*) malloc(qtdPratos*sizeof(Prato));
        //lendo os pratos
        ler_pratos(qtd_cardapios(),pratos,qtdPratos);
        //criando variaveis de char que aguentem a quantidade de pratos
        char id[qtdPratos*5];
        char nome[qtdPratos*100];
        char preco[qtdPratos*20];
        int i;
        for(i=0;i<qtdPratos;i++){
            //adicionando o id do novo prato na listagem dos pratos
            snprintf(id,5,"%d\n",pratos[i].id);
            strcat(id,gtk_label_get_text(lblId));
            gtk_label_set_text(lblId,id);
            //adicionando o nome do novo prato na listagem dos pratos
            snprintf(nome,100,"%s\n",pratos[i].nome);
            strcat(nome,gtk_label_get_text(lblNome));
            gtk_label_set_text(lblNome,nome);
            //adicionando o preco do novo prato na listagem dos pratos
            snprintf(preco,20,"RS %.2f\n",pratos[i].preco);
            strcat(preco,gtk_label_get_text(lblPreco));
            gtk_label_set_text(lblPreco,preco);
        }
        free(pratos);
    }else{
        gtk_label_set_text(lblId,"");
        gtk_label_set_text(lblNome,"");
        gtk_label_set_text(lblPreco,"");
    }
}
//funcao que carrega o prato adicionado na tela
void load_prato(GtkBuilder *builder){
    int qtdPratos = qtd_pratos(qtd_cardapios());
    if(qtdPratos!=0){
        Prato *pratos = (Prato*) malloc(qtdPratos*sizeof(Prato));
        //lendo os pratos
        ler_pratos(qtd_cardapios(),pratos,qtdPratos);
        //pegando os labels da tela de listagem dos pratos
        GtkWidget *lblId = GTK_WIDGET(gtk_builder_get_object(builder,"idPrato"));
        GtkWidget *lblNome = GTK_WIDGET(gtk_builder_get_object(builder,"idNome"));
        GtkWidget *lblPreco = GTK_WIDGET(gtk_builder_get_object(builder,"idValor"));
        //criando variaveis de char que aguentem a quantidade de pratos
        char id[qtdPratos*5];
        char nome[qtdPratos*100];
        char preco[qtdPratos*20];
        //adicionando o id do novo prato na listagem dos pratos
        snprintf(id,5,"%d\n",pratos[qtdPratos-1].id);
        strcat(id,gtk_label_get_text(lblId));
        gtk_label_set_text(lblId,id);
        //adicionando o nome do novo prato na listagem dos pratos
        snprintf(nome,100,"%s\n",pratos[qtdPratos-1].nome);
        strcat(nome,gtk_label_get_text(lblNome));
        gtk_label_set_text(lblNome,nome);
        //adicionando o preco do novo prato na listagem dos pratos
        snprintf(preco,20,"RS %.2f\n",pratos[qtdPratos-1].preco);
        strcat(preco,gtk_label_get_text(lblPreco));
        gtk_label_set_text(lblPreco,preco);
        free(pratos);
    }
}
//funcao que salva o cardapio no arquivo
void salvar_cardapio(Cardapio *c){
    if(qtd_cardapios()==0){
        FILE *file = fopen("./dados/cardapios.b","wb");
        fwrite(c,sizeof(Cardapio),1,file);
        fclose(file);
    }else{
        FILE *file = fopen("./dados/cardapios.b","ab");
        fwrite(c,sizeof(Cardapio),1,file);
        fclose(file);
    }

}
//funcao que salvao prato que vai ser adicionado
void salvar_prato(int card,Prato *p){
    char caminho[50];
    snprintf(caminho,50,"./dados/pratos/%d.b",card);
    if(qtd_pratos(card)==0){
        FILE *file = fopen(caminho,"wb");
        fwrite(p,sizeof(Prato),1,file);
        fclose(file);
    }else{
        FILE *file = fopen(caminho,"ab");
        fwrite(p,sizeof(Prato),1,file);
        fclose(file);
    }

}
//funcao para salvar mais de um prato
void salvar_pratos(int card,Prato *p,int qtd){
    char caminho[50];
    snprintf(caminho,50,"./dados/pratos/%d.b",card);
    FILE *file = fopen(caminho,"wb");
    fwrite(p,sizeof(Prato),qtd,file);
    fclose(file);

}
//funcao que calcula a quantidade de cardapios
int qtd_cardapios(){
    int qtd=0;
    FILE *file = fopen("./dados/cardapios.b","rb");
    if(file!=NULL){
        struct cardapio c;
        while(fread(&c,sizeof(Cardapio),1,file)){
            qtd++;
        }
    }
    return qtd;
    fclose(file);
}
//funcao que calcula a quantidade de pratos em determinado cardapio
int qtd_pratos(int card){
    int qtd=0;
    char caminho[50];
    snprintf(caminho,50,"./dados/pratos/%d.b",card);
    FILE *file = fopen(caminho,"rb");
    if(file!=NULL){
        Prato p;
        while(fread(&p,sizeof(Prato),1,file)){
            qtd++;
        }
    }
    return qtd;
    fclose(file);
}
//funcao para ler os cardapios
void ler_cardapios(Cardapio *c,int qtd){
    FILE *file = fopen("./dados/cardapios.b","rb");
    if(file!=NULL){
        fread(c,sizeof(Cardapio),qtd,file);
    }
    fclose(file);
}
//salvar Cardapios
void salvar_cardapios(Cardapio *c,int qtd){
    FILE *file = fopen("./dados/cardapios.b","wb");
    fwrite(c,sizeof(Cardapio),qtd,file);
    fclose(file);
}
//funcao para pesquisar um cardapio
int pesquisar_cardapio(char nome[100],GtkBuilder *builder){
    int qtdCardapios = qtd_cardapios();
    Cardapio *cardapios = (Cardapio *) malloc(qtdCardapios*sizeof(Cardapio));
    ler_cardapios(cardapios,qtdCardapios);
    int i;
    for(i=0;i<qtdCardapios;i++){
        if(strcmp(cardapios[i].nome,nome)==0){
            free(cardapios);
            return i;
        }
    }
    free(cardapios);
    return -1;
}
//funcao para pesquisa de pratos de um determinado cardapio
int busca_binaria_pratos(int idPrato,int i,int f,Prato *p){
    if(i>f){
        return -1;
    }
    int meio = (i+f)/2;
    if(p[meio].id==idPrato){
        return meio;
    }else if(p[meio].id>idPrato){
        return busca_binaria_pratos(idPrato,i,meio-1,p);
    }
    return busca_binaria_pratos(idPrato,meio+1,f,p);
}
//funcao para ler os pratos do cardapio no seu determinado arquivo
void ler_pratos(int card,Prato *p,int qtd){
    char caminho[50];
    snprintf(caminho,50,"./dados/pratos/%d.b",card);
    FILE *file = fopen(caminho,"rb");
    if(file!=NULL){
         fread(p,sizeof(Prato),qtd,file);
    }
    fclose(file);
}
//funcao para limpar os dados do cardapio
void limpar_pratos(GtkButton *button,GtkBuilder *builder){
    int qtdCardapios = qtd_cardapios();
    zerar_pratos(qtdCardapios,builder);
}
//funcao para limpar os pratos do arquivo
void zerar_pratos(int idx,GtkBuilder *builder){
    char caminho[50];
    snprintf(caminho,50,"./dados/pratos/%d.b",idx);

    FILE *file = fopen(caminho,"wb");
    Prato *zera = (Prato *) malloc(0*sizeof(Prato));

    fwrite(zera,sizeof(Prato),0,file);
    fclose(file);
    load_pratos(builder);
    free(zera);
}
//funcao para criar pratos
Prato* criar_pratos(int qtd){
    Prato *p = (Prato *) malloc(qtd*sizeof(Prato));
    return p;
}
//funcao para pegar o valor de um prato
void get_valor_prato(float *conta,Prato *pratos,int idPrato){
    *conta+=pratos[idPrato].preco;
}
