#include<gtk-3.0/gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"mesa.h"
#include"../restaurante/restaurante.h"
enum statusMesa{VAZIA,OCUPADA};
//estrutura dos clientes
struct cliente{
  char nome[100];
  float conta;
};
//estrutura das mesas
struct mesa{
  int numero;
  Cliente c;
  enum statusMesa status;
};
//funcao para adicionar uma nova mesa
void add_new_mesa(GtkButton *button,GtkBuilder *builder){
    //pegando as caixas de entrada da tela de adicionar mesa
    GtkWidget *etrNumeroMesa = GTK_WIDGET(gtk_builder_get_object(builder,"numeroMesaetr"));
    GtkWidget *etrNomeCliente = GTK_WIDGET(gtk_builder_get_object(builder,"nomeClienteMesaetr"));

    //conferindo se a caixa do numero da mesa esta vazia
    if(strcmp(gtk_entry_get_text(etrNumeroMesa),"")!=0){
        int numeroMesa = atoi(gtk_entry_get_text(etrNumeroMesa));
        int idx = -1;
        int qtd = qtd_mesas();
        if(qtd!=0){
            Mesa *mesas=(Mesa *) malloc(qtd*sizeof(Mesa));;
            ler_mesas(qtd_mesas(),mesas);
            idx = busca_binaria_mesas(numeroMesa,0,qtd_mesas()-1,mesas);
        }


        //conferindo se foi digitado letras ao inves de numeros
        if(numeroMesa!=0 && idx== -1){

            //convertendo o conteudo da caixa de entrada para int e criando a mesa
            int numeroMesa = atoi(gtk_entry_get_text(etrNumeroMesa));
            Cliente cliM;
            cliM.conta=0;
            strcpy(cliM.nome,"");
            strcpy(cliM.nome,gtk_entry_get_text(etrNomeCliente));
            //conferindo se tem alguem na mesa e definindo o status dela
            Mesa novaMesa;
            if(strcmp(cliM.nome,"")==0){
                novaMesa.numero =numeroMesa;
                novaMesa.c=cliM;
                novaMesa.status=VAZIA;
            }else{
                novaMesa.numero =numeroMesa;
                novaMesa.c=cliM;
                novaMesa.status=OCUPADA;
            }
            salvar_mesa(&novaMesa);
            //limpando as caixas de entrada
            gtk_entry_set_text(etrNomeCliente,"");
            gtk_entry_set_text(etrNumeroMesa,"");

            //informando que a mesa foi adicionada com sucesso atraves da funcao
            tela_sucesso(builder,"A mesa foi adicionada com sucesso");

        }else if(idx!= -1){
            tela_aviso(builder,"Esta mesa ja existe no sistema");
        }else{
            //mostrando a tela de aviso atraves da funcao
            tela_aviso(builder,"O numero da mesa nao pode ser 0 e nao deve conter letras");
        }

    }else{
        //mostrando a tela de aviso a partir da funcao feita
        tela_aviso(builder,"Para adicionar uma mesa e necessario o numero da mesa");
    }
    load_mesas(builder);
}
//funcao para limpar uma mesa
void limpar_mesa(GtkButton *button,GtkBuilder *builder){
    //pegando o numero da mesa
    GtkWidget *lblNumeroTelaMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
    Mesa *mesas =(Mesa *) malloc(qtd_mesas()*sizeof(Mesa));
    ler_mesas(qtd_mesas(),mesas);
    //pegando o valor do label do numero da tela da mesa e diminuindo 1 para pegar o id da mesa no vetor
    int idxMesa = atoi(gtk_label_get_text(lblNumeroTelaMesa))-1;

    //conferindo se o cliente da mesa pagou sua conta
    if(mesas[idxMesa].c.conta==0){
        //pegando o botao ocupar para mostrar na tela
        GtkWidget *btnOcupar = GTK_WIDGET(gtk_builder_get_object(builder,"btnOcupar"));
        //deixando o botao limpar oculto
        gtk_widget_set_visible(button,FALSE);
        //mostrando o botao ocupar
        gtk_widget_set_visible(btnOcupar,TRUE);
        //deixando o nome do cliente da mesa vazio
        strcpy(mesas[idxMesa].c.nome,"");
        //mudando o status da mesa
        mesas[idxMesa].status = VAZIA;
        //atualizando o vetor das mesas
        update_mesas(mesas,qtd_mesas());
        //carregando as mesas
        load_mesas(builder);
        tela_sucesso(builder,"Mesa limpa com sucesso!");
    }else{
        //mostrando aviso caso tenha um pedido pendente daquele cliente
        tela_aviso(builder,"O cliente ainda nao pagou a conta");
    }
}
//funcao para ocupar uma mesa
void ocupar_mesa(GtkButton *button,GtkBuilder *builder){
    //mostrando e escondendo a caixa de itens para ocupar a mesa
    GtkWidget *ocupar = GTK_WIDGET(gtk_builder_get_object(builder,"ocupar"));
    if(gtk_widget_get_visible(ocupar)){
        gtk_widget_set_visible(ocupar,FALSE);
    }else{
        gtk_widget_set_visible(ocupar,TRUE);
    }
}
//funcao para adicionar um cliente a uma mesa
void add_cliente(GtkButton *button,GtkBuilder *builder){
    //pegando a caixa de entrada e o label de navegacao das mesas
    GtkWidget *lblNumeroTelaMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
    GtkWidget *etrAddCliente = GTK_WIDGET(gtk_builder_get_object(builder,"etrAddCliente"));
    int qtd = qtd_mesas();
    Mesa *mesas =(Mesa *) malloc(qtd*sizeof(Mesa));
    ler_mesas(qtd,mesas);
    //convertendo label para o indice da posicao do vetor de mesas
    int numeroMesa = atoi(gtk_label_get_text(lblNumeroTelaMesa))-1;
    //conferindo se a caixa de entrada possui algum conteudo
    if(strcmp(gtk_entry_get_text(etrAddCliente),"")!=0){

        //copiando o texto da caixa de entrada para a mesa naquela posicao
        strcpy(mesas[numeroMesa].c.nome,gtk_entry_get_text(etrAddCliente));
        //mudando o status da mesa para ocupada
        mesas[numeroMesa].status =OCUPADA;
        //buscando a caixa de itens para ocupar a mesa
        GtkWidget *ocupar = GTK_WIDGET(gtk_builder_get_object(builder,"ocupar"));
        //deixando a caixa de entrada vazia
        gtk_entry_set_text(etrAddCliente,"");
        //escondendo a caixa de itens para ocupar a mesa
        gtk_widget_set_visible(ocupar,FALSE);
        //mostrando a tela de sucesso ao para ocupar a mesa
        tela_sucesso(builder,"Sucesso ao ocupar a mesa");
    }else{
        //mostrando o aviso na tela
        tela_aviso(builder,"Para ocupar a mesa e necessario o nome do funcionario");
    }
    //atualizando as mesas
    update_mesas(mesas,qtd_mesas());
    //recarregando as mesas na tela
    load_mesas(builder);
}
//funcao para voltar a mesa
void mesa_anterior(GtkButton *button,GtkBuilder *builder){
    GtkWidget *lblNumeroTelaMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
    if(qtd_mesas()>1){
        int numeroMesa = atoi(gtk_label_get_text(lblNumeroTelaMesa))-1;
        if(numeroMesa<1){
            numeroMesa = qtd_mesas();
        }
        char numeroMesaTxt[10];
        itoa(numeroMesa,numeroMesaTxt,10);
        gtk_label_set_text(lblNumeroTelaMesa,numeroMesaTxt);
        load_mesas(builder);
    }
}
//funcao para passar a mesa
void proxima_mesa(GtkButton *button,GtkBuilder *builder){
    GtkWidget *lblNumeroTelaMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
    if(qtd_mesas()>1){
        int numeroMesa = atoi(gtk_label_get_text(lblNumeroTelaMesa))+1;
        if(numeroMesa>qtd_mesas()){
            numeroMesa = 1;
        }
        char numeroMesaTxt[10];
        itoa(numeroMesa,numeroMesaTxt,10);
        gtk_label_set_text(lblNumeroTelaMesa,numeroMesaTxt);
        load_mesas(builder);
    }
}
//funcao que salva uma nova mesa no arquivo
void salvar_mesa(Mesa *novaMesa){
    //conferindo se tem mais de um objeto no arquivo
    if(qtd_mesas()==0){
        //se nao tiver nada no arquivo entao é feita a  primeira adicao
        FILE *file = fopen("./dados/mesas.b","wb");
        fwrite(novaMesa,sizeof(Mesa),1,file);
        fclose(file);
    }else{
        //adicionando a nova mesa no final do arquivo
        FILE *file = fopen("./dados/mesas.b","ab");
        fwrite(novaMesa,sizeof(Mesa),1,file);
        fclose(file);
    }
}
//funcao para atualizar os dados das mesas caso seja alterado algo durante a execucao
void update_mesas(Mesa *mesas,int qtd){
    FILE *file = fopen("./dados/mesas.b","wb");
    fwrite(mesas,sizeof(Mesa),qtd,file);
    fclose(file);
}
//funcao para deletar uma mesa
void delete_mesa(GtkButton *button,GtkBuilder *builder){
    int qtd = qtd_mesas();
    if(qtd>0){
        GtkWidget *lblNumeroTelaMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
        Mesa *mesasA= (Mesa *) malloc(qtd*sizeof(Mesa));
        ler_mesas(qtd,mesasA);
        int idxMesa = atoi(gtk_label_get_text(lblNumeroTelaMesa));
        idxMesa=idxMesa-1;
        if(mesasA[idxMesa].c.conta==0){
            int i;
            Cliente cliM = {"",0};
            Mesa *mesas = (Mesa *) malloc((qtd-1)*sizeof(Mesa));
            for(i=0;i<qtd-1;i++){
                mesas[i].c = cliM;
                mesas[i].numero =0;
                mesas[i].status =VAZIA;
            }
            int cont =0;
            for(i=0;i<qtd;i++){
                if(i!=idxMesa){
                    mesas[cont] = mesasA[i];
                    cont++;
                }
            }
            update_mesas(mesas,cont);
            char numeroTxt[10];
            if(idxMesa==0){
                itoa(idxMesa+1,numeroTxt,10);
            }else{
                itoa(qtd-1,numeroTxt,10);
            }
            gtk_label_set_text(lblNumeroTelaMesa,numeroTxt);
            tela_sucesso(builder,"Mesa deletada com sucesso");
            load_mesas(builder);
        }else{
            tela_aviso(builder,"A mesa possui um cliente com conta");
        }
    }
}
//funcao para fazer a pesquisa de uma mesa pelo nome do cliente ou numero da mesa
void pesquisar_mesa(GtkButton *button,GtkBuilder *builder){
    GtkWidget *lblNumeroMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
    GtkWidget *etrPesquisar = GTK_WIDGET(gtk_builder_get_object(builder,"etrPesquisarMesa"));
    int numeroMesa = atoi(gtk_entry_get_text(etrPesquisar));
    int idx=-1;
    int qtd = qtd_mesas();
    Mesa *mesas= (Mesa *) malloc(qtd*sizeof(Mesa));
    ler_mesas(qtd,mesas);
    if(numeroMesa!=0){
        idx = busca_binaria_mesas(numeroMesa,0,qtd_mesas()-1,mesas);
    }else{
        char nomeCliente[100];
        strcpy(nomeCliente,gtk_entry_get_text(etrPesquisar));
        int i;
        for(i=0;i<qtd_mesas();i++){
            if(strcmp(mesas[i].c.nome,nomeCliente)==0){
                idx = i;
            }
        }
    }
    if(idx!=-1){
        char idxTxt[5];
        itoa(idx+1,idxTxt,10);
        gtk_label_set_text(lblNumeroMesa,idxTxt);
        load_mesas(builder);
    }else{
        tela_aviso(builder,"A mesa nao existe!");
    }

}
//funcao de busca binaria recursiva das mesas
int busca_binaria_mesas(int numeroMesa,int i, int f, Mesa *mesas){
    if(i>f){
        return -1;
    }
    int meio = (i+f)/2;
    if(mesas[meio].numero==numeroMesa){
        return meio;
    }else if(mesas[meio].numero>numeroMesa){
        return busca_binaria_mesas(numeroMesa,i,meio-1,mesas);
    }
    return busca_binaria_mesas(numeroMesa,meio+1,f,mesas);
}
//funcao para ordenar as mesas
void ordenar_mesas(Mesa *mesas,int qtd){
    int i,j;
    for(i=0;i<qtd;i++){
        int imenor = i;
        for(j=i+1;j<qtd;j++){
            if(mesas[imenor].numero>mesas[j].numero){
                imenor = j;
            }
        }
        Mesa temp = mesas[i];
        mesas[i] = mesas[imenor];
        mesas[imenor]=temp;
    }
}

//funcao para carregar a mesa na tela
void load_mesas(GtkBuilder *builder){
    //buscando a quantidade de mesas para pegar do arquivo
    int qtd = qtd_mesas();
    //pegando widgets para controle na tela
    GtkWidget *lblMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblMesa"));
    GtkWidget *botoes = GTK_WIDGET(gtk_builder_get_object(builder,"itensMesa"));
    GtkWidget *imgMesa = GTK_WIDGET(gtk_builder_get_object(builder,"imgMesa"));
    GtkWidget *lblCliente = GTK_WIDGET(gtk_builder_get_object(builder,"lblCliente"));
    GtkWidget *ocupar = GTK_WIDGET(gtk_builder_get_object(builder,"ocupar"));
    GtkWidget *lblConta = GTK_WIDGET(gtk_builder_get_object(builder,"idConta"));
    //se o arquivo existir sera feita a busca
    if(qtd!=0){
        Mesa *mesas = (Mesa*) malloc(qtd*sizeof(Mesa));
        ler_mesas(qtd,mesas);
        //guardando as mesas no restaurante
        ordenar_mesas(mesas,qtd);
        //pegando o label que mostra o numero da pagina da mesa atual
        GtkWidget *lblNumeroTelaMesa = GTK_WIDGET(gtk_builder_get_object(builder,"lblNumeroTelaMesa"));
        //convertendo o conteudo do label para inteiro e diminuindo um para ser a posicao da mesa no vetor
        int idxMesa = atoi(gtk_label_get_text(lblNumeroTelaMesa))-1;

        // conferindo se o valor do idx e menor do que a quantidade
        if(idxMesa<qtd){
            //pegando botoes para controlar qual aparece
            GtkWidget *btnLimpar = GTK_WIDGET(gtk_builder_get_object(builder,"btnLimpar"));
            GtkWidget *btnOcupar = GTK_WIDGET(gtk_builder_get_object(builder,"btnOcupar"));

            //criando uma variavel que vai guardar o numero da mesa convertido em char
            char numeroMesa[20];

            //convertendo o numero da mesa para char para que seja colocado no label
            itoa(mesas[idxMesa].numero,numeroMesa,10);
            gtk_label_set_text(lblMesa,numeroMesa);
            //mudando os componentes para cada status de mesa
            if(mesas[idxMesa].status==VAZIA){
                gtk_label_set_text(lblCliente,"vazia");
                gtk_image_set_from_file(imgMesa,"./imagens/mesas2.png");
                gtk_widget_set_visible(botoes,TRUE);
                gtk_widget_set_visible(btnLimpar,FALSE);
                gtk_widget_set_visible(btnOcupar,TRUE);
                gtk_label_set_text(lblConta,"0");
            }else{
                gtk_label_set_text(lblCliente,mesas[idxMesa].c.nome);
                gtk_image_set_from_file(imgMesa,"./imagens/mesas3.png");
                gtk_widget_set_visible(botoes,TRUE);
                gtk_widget_set_visible(btnLimpar,TRUE);
                gtk_widget_set_visible(btnOcupar,FALSE);
                char conta[30];
                snprintf(conta,30,"RS %.2f",mesas[idxMesa].c.conta);
                gtk_label_set_text(lblConta,conta);
            }
        }
        gtk_widget_set_visible(ocupar,FALSE);
        free(mesas);
    }else{
        gtk_label_set_text(lblCliente,"");
        gtk_label_set_text(lblMesa,"0");
        gtk_label_set_text(lblConta,"");
        gtk_image_set_from_file(imgMesa,"./imagens/mesas1.png");
        gtk_widget_set_visible(botoes,FALSE);
        gtk_widget_set_visible(ocupar,FALSE);
    }
}

void ler_mesas(int qtd,Mesa *mesas){
    //alocando um espaco para a quantidade de mesas que tem no arquivo
    FILE *file = fopen("./dados/mesas.b","rb");
    if(file!=NULL){
        //lendo as mesas
        fread(mesas,sizeof(Mesa),qtd,file);
        fclose(file);
    }
}

// funcao que retorna a quantidade de mesas no arquivo
int qtd_mesas(){
    int qtd = 0;
    FILE *file = fopen("./dados/mesas.b","rb");
    if(file!=NULL){
        Mesa m;
        while(fread(&m,sizeof(Mesa),1,file)){
            qtd++;
        }
    }
    return qtd;
    fclose(file);
}

void update_conta_mesa(Mesa *mesas,float *conta,int idx){
    //guardando o valor da conta daquele cliente
    mesas[idx].c.conta += *conta;
    update_mesas(mesas,qtd_mesas());
}

Mesa* criar_mesa(int qtd){
    Mesa *m = (Mesa*) malloc(qtd*sizeof(Mesa));
    return m;
}

int get_status_mesa(Mesa *mesas,int idx){
    return mesas[idx].status;
}

int get_numero_mesa(Mesa *mesas,int idx){
    return mesas[idx].numero;
}

