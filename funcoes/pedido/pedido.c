#include<gtk-3.0/gtk/gtk.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "../mesa/mesa.h"
#include "../cardapio/cardapio.h"
#include "./pedido.h"
#include "../restaurante/restaurante.h"
//estrutura do pedido
struct pedido{
  char nomeCardapio[100];
  char idPratos[100];
  float valorPedido;
  int numeroMesa;
};
struct no{
    Pedido dado;
    struct no *prox;
};
struct lista_pedidos{
    No *inicio;
};
//funcao para adicionar um novo pedido
void add_new_pedido(GtkButton* button, GtkBuilder *builder){
    GtkWidget *etrNomeCardapio = GTK_WIDGET(gtk_builder_get_object(builder,"etrNomeCardapio"));
    GtkWidget *etrNumeroPratos = GTK_WIDGET(gtk_builder_get_object(builder,"etrNumeroPratos"));
    GtkWidget *etrNumeroMesa= GTK_WIDGET(gtk_builder_get_object(builder,"etrNumeroMesa"));
    //fazendo pesquisa para saber se existe um cardapio com aquele nome
    int idCardapio =pesquisar_cardapio(gtk_entry_get_text(etrNomeCardapio),builder);
    //testando para saber se existe msm
    if(idCardapio!=-1){
        //salvando a string com os numeros dos pratos que foram digitados
        char *numeroPratos = (char *) malloc((strlen(gtk_entry_get_text(etrNumeroPratos))+2)*sizeof(char));
        strcpy(numeroPratos,gtk_entry_get_text(etrNumeroPratos));
        //adicionando uma virgula no final da string para facilitar a comparacao
        strcat(numeroPratos,",");
        /*contadores para percorrer a string no for, a string que sera convertida
        para int e outro para a quantidade de itens no vetor de pratos */
        int i,cont=0,contstr=0;
        //string que guardara os numeros para conversao
        char numero[10]="";
        //inicializando o vetor para guardar os ids dos pratos
        int *vetPratos = (int *) malloc(cont*sizeof(int));
        //for para fazer a separacao dos ids na string digitada
        for(i=0;i<strlen(numeroPratos);i++){
            //quando uma virgula for encontrada a string numero sera convertida
            if(numeroPratos[i]==','){
                contstr=0;
                cont++;
                vetPratos = realloc(vetPratos,cont*sizeof(int));
                vetPratos[cont-1] = atoi(numero);
                strcpy(numero,"");
            //quando nao existir virgula o valor sera guardado na string de numero
            }else{
                numero[contstr] = numeroPratos[i];
            }
        }
        //variavel para guardar o valor da conta
        float conta=0;
        //conferindo se existem pratos mesmo
        if(vetPratos[0]!=0){
            //pegando a quantidade de pratos daquele cardapio
            int qtdPratos = qtd_pratos(idCardapio);
            //pegando os pratos daquele cardapio
            Prato *pratos = criar_pratos(qtdPratos);
            ler_pratos(idCardapio,pratos,qtdPratos);

            //andando pelo vetor de pratos
            for(i=0;i<cont;i++){
                //vendo se os pratos existem msm naquele cardapio
                int idPrato=busca_binaria_pratos(vetPratos[i],0,qtdPratos-1,pratos);
                //quando um prato nao existir sera recebido o numero -1
                if(idPrato==-1){
                    //a mensagem de que aquele prato nao existe sera mostrada na tela
                    char aviso[50];
                    snprintf(aviso,50,"O prato de id %d nao existe neste cardapio",vetPratos[i]);
                    tela_aviso(builder,aviso);
                    return;
                }
                //enquanto existir pratos compativeis o valor deles sera acrescentado na conta
                get_valor_prato(&conta,pratos,idPrato);
            }

            //pegando o numero da mesa e fazendo a busca para saber se ela existe
            int qtdMesas = qtd_mesas();
            Mesa *mesas =criar_mesa(qtdMesas);
            ler_mesas(qtdMesas,mesas);
            int numeroMesa = atoi(gtk_entry_get_text(etrNumeroMesa));
            int idx = busca_binaria_mesas(numeroMesa,0,qtdMesas-1,mesas);
            // se existir a funcao busca binaria mesas retornara um valor diferente de -1
            if(idx!=-1){
                //conferindo se existe um cliente naquela mesa
                if(get_status_mesa(mesas,idx)==1){
                    update_conta_mesa(mesas,&conta,idx);
                    //gerando um pedido para ser salvo
                    Pedido p;
                    strcpy(p.idPratos,gtk_entry_get_text(etrNumeroPratos));
                    strcpy(p.nomeCardapio,gtk_entry_get_text(etrNomeCardapio));
                    p.numeroMesa = get_numero_mesa(mesas,idx);
                    p.valorPedido = conta;
                    salvar_pedido(&p);

                    load_pedidos(builder,1);
                    //carregando as mesas na tela com a conta do cliente alterada
                    load_mesas(builder);
                    gtk_entry_set_text(etrNomeCardapio,"");
                    gtk_entry_set_text(etrNumeroPratos,"");
                    gtk_entry_set_text(etrNumeroMesa,"");
                    tela_sucesso(builder,"O pedido foi cadastrado com sucesso");
                //serie de avisos caso as condicoes anteriores nao sejam satisfeitas
                }else{
                    tela_aviso(builder,"A mesa nao possui cliente");
                }
            }else{
                tela_aviso(builder,"Esta mesa nao esta cadastrada");
            }
        }else{
            tela_aviso(builder,"Nao e possivel cadastrar um pedido sem pratos");
        }
    }else{
        tela_aviso(builder,"Nao foi possivel encontrar este cardapio");
    }

}
//funcao para carregar os pedidos
void load_pedidos(GtkBuilder *builder,int idx){
    GtkWidget *lblMesa = GTK_WIDGET(gtk_builder_get_object(builder,"labelMesaPedido"));
    GtkWidget *lblPedido = GTK_WIDGET(gtk_builder_get_object(builder,"labelPedido"));
    GtkWidget *lblTotal = GTK_WIDGET(gtk_builder_get_object(builder,"labelTotal"));
    GtkWidget *lblNumeroPedido = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroPedido"));

    char numero[10];
    snprintf(numero,10,"%d",idx);
    gtk_label_set_text(lblNumeroPedido,numero);

    if(qtd_pedidos()!=0){
        Lista_pedidos pedidos = ler_pedidos();
        int idx = atoi(gtk_label_get_text(lblNumeroPedido))-1;
        Pedido pedidoP = pesquisaPed(pedidos,idx);
        char numeroMesa[10];
        snprintf(numeroMesa,10,"%d",pedidoP.numeroMesa);
        gtk_label_set_text(lblMesa,numeroMesa);
        char pedido[100];
        snprintf(pedido,100," %s %s",pedidoP.nomeCardapio,pedidoP.idPratos);
        gtk_label_set_text(lblPedido,pedido);
        char total[20];
        snprintf(total,20," RS %.2f",pedidoP.valorPedido);
        gtk_label_set_text(lblTotal,total);
    }else{
        gtk_label_set_text(lblMesa,"");
        gtk_label_set_text(lblPedido,"");
        gtk_label_set_text(lblTotal,"");
    }


}
//funcao para pesquisar um pedido
Pedido pesquisaPed(Lista_pedidos pedidos,int pos){
    int cont=0;
    No *pi;
    for(pi=pedidos.inicio;cont!=pos;pi=pi->prox){
        cont++;
    }
    return pi->dado;
}
//funcao para deletar um pedido
void deletar_pedido(Lista_pedidos *pedidos,int pos){
    int cont = 0;
    No *pi;
    No *pa=NULL;
    for(pi=pedidos->inicio;pi!=NULL && cont!=pos;pi=pi->prox){
        pa=pi;
        cont++;
    }
    if(pa==NULL){
        pedidos->inicio = pi->prox;
        free(pi);
    }else{
        pa->prox =pi->prox;
        free(pi);
    }
}
//funcao para ir para o pedido anterior
void pedido_anterior(GtkButton *button, GtkBuilder *builder){
    int qtdPedidos =qtd_pedidos();
    if(qtdPedidos!=0){
        GtkWidget *lblNumeroPedido = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroPedido"));
        int numero = atoi(gtk_label_get_text(lblNumeroPedido))-1;
        if(numero==0){
            numero = qtdPedidos;
        }
        load_pedidos(builder,numero);
    }
}
//funcao para ir para o proximo pedido
void proximo_pedido(GtkButton *button, GtkBuilder *builder){
    int qtdPedidos =qtd_pedidos();
    if(qtdPedidos!=0){
        GtkWidget *lblNumeroPedido = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroPedido"));
        int numero = atoi(gtk_label_get_text(lblNumeroPedido))+1;
        if(numero>qtdPedidos){
            numero = 1;
        }
        load_pedidos(builder,numero);
    }
}
//funcao para salvar um pedido
void salvar_pedido(Pedido *p){
    if(qtd_pedidos()==0){
        FILE *file = fopen("./dados/pedidos.b","wb");
        fwrite(p,sizeof(Pedido),1,file);
        fclose(file);
    }else{
        FILE *file = fopen("./dados/pedidos.b","ab");
        fwrite(p,sizeof(Pedido),1,file);
        fclose(file);
    }
}
//funcao para salvar todos os pedidos de uma lista
void salvar_pedidos(Lista_pedidos *pedidos){
    FILE *file = fopen("./dados/pedidos.b","wb");
    No *pi;
    for(pi=pedidos->inicio;pi!=NULL;pi=pi->prox){
        fwrite(&pi->dado,sizeof(Pedido),1,file);
    }
    fclose(file);
}
//funcao para fazer a leitura dos pedidos no arquivo
Lista_pedidos ler_pedidos(){
        Lista_pedidos pedidos;
        pedidos.inicio = NULL;
        FILE *file = fopen("./dados/pedidos.b","rb");
        No *ped = (No*) malloc(sizeof(No));
        while(fread(&ped->dado,sizeof(Pedido),1,file)){
            if(pedidos.inicio==NULL){
                ped->prox = pedidos.inicio;
                pedidos.inicio = ped;
                ped = (No*) malloc(sizeof(No));
            }else{
                No *pi;
                for(pi=pedidos.inicio;pi->prox!=NULL;pi=pi->prox);
                ped->prox = pi->prox;
                pi->prox = ped;
                ped = (No*) malloc(sizeof(No));
            }

        }
        return pedidos;
        fclose(file);
}
//funcao para saber a quantidade de pedidos
int qtd_pedidos(){
    FILE *file = fopen("./dados/pedidos.b","rb");
    int qtd=0;
    if(file!=NULL){
        Pedido p;
        while(fread(&p,sizeof(Pedido),1,file)){
            qtd++;
        }
    }
    return qtd;
}
//funcao para pesquisarum pedido
void pesquisar_pedido(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrPesquisaPedido = GTK_WIDGET(gtk_builder_get_object(builder,"etrPesquisaPedido"));
    int numeroMesaPedido = atoi(gtk_entry_get_text(etrPesquisaPedido));
    if(numeroMesaPedido!=0){
        Lista_pedidos pedidos = ler_pedidos();
        No *pi;
        int cont=0;
        for(pi=pedidos.inicio;pi!=NULL && pi->dado.numeroMesa!=numeroMesaPedido;pi=pi->prox){
            cont++;
        }
        if(pi!=NULL){
            GtkWidget *lblNumeroPedido = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroPedido"));
            load_pedidos(builder,cont);
        }else{
            tela_aviso(builder,"A mesa informada nao possui pedidos");
        }
    }else{
        tela_aviso(builder,"Mesa nao identificada");
    }
}
//funcao para finalizar pedido
void finalizar_pedido(GtkButton *button,GtkBuilder *builder){
    GtkWidget *labelNumero = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroPedido"));
    int idx = atoi(gtk_label_get_text(labelNumero))-1;
    if(qtd_pedidos()!=0){
        Lista_pedidos pedidos= ler_pedidos();

        Pedido ped = pesquisaPed(pedidos,idx);

        Restaurante *rest = ler_restaurante();
        set_caixa(ped.valorPedido,rest);
        save_restaurante(rest);

        int qtdMesas = qtd_mesas();
        Mesa *mesas = criar_mesa(qtdMesas);
        ler_mesas(qtdMesas,mesas);

        int idxMesa = busca_binaria_mesas(ped.numeroMesa,0,qtdMesas-1,mesas);
        ped.valorPedido = ped.valorPedido*-1;
        update_conta_mesa(mesas,&ped.valorPedido,idxMesa);

        deletar_pedido(&pedidos,idx);
        salvar_pedidos(&pedidos);
        if(idx==0){
            load_pedidos(builder,1);
        }else{
            load_pedidos(builder,idx);
        }
        load_mesas(builder);
        load_caixa(builder);
    }
}
