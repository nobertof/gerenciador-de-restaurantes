#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gtk-3.0/gtk/gtk.h>
#include"./restaurante.h"
#include"../mesa/mesa.h"
struct restaurante{
    float caixa;
    float aumento_func_mes;
};
//funcao que carrega os dados do restaurante na tela
void load_dados_restaurante(GtkWindow *window, GtkBuilder *builder){
    load_mesas(builder);
    load_pedidos(builder);
    load_caixa(builder);
}
void load_caixa(GtkBuilder *builder){
    Restaurante *rest = ler_restaurante();
    char textoCaixa[50];
    snprintf(textoCaixa,50,"RS %.2f",rest->caixa);

    GtkWidget *lblCaixa = GTK_WIDGET(gtk_builder_get_object(builder,"labelCaixa"));
    gtk_label_set_text(lblCaixa,textoCaixa);
}
//mostra tela de sucesso com a mensagem passada
void tela_sucesso(GtkBuilder *builder,char msg[100]){
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaSucesso"));
    GtkWidget *lblSucesso = GTK_WIDGET(gtk_builder_get_object(builder,"lblSucesso"));
    gtk_window_set_title(window,"Sucesso");
    gtk_label_set_text(lblSucesso,msg);
    gtk_widget_show(window);
}
//mostra a tela de aviso com a mensagem passada
void tela_aviso(GtkBuilder *builder, char msg[100]){
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaAviso"));
    GtkWidget *lblAviso = GTK_WIDGET(gtk_builder_get_object(builder,"lblAviso"));
    gtk_window_set_title(window,"Importante");
    gtk_label_set_text(lblAviso,msg);
    gtk_widget_show(window);
}

void get_caixa(float *caixa,Restaurante *rest){
    *caixa = rest->caixa;
}

void set_caixa(float caixa, Restaurante *rest){
    rest->caixa += caixa;
}

void set_aumento_func_mes(float aumento, Restaurante *rest){
    rest->aumento_func_mes = aumento;
}

void get_aumento_func_mes(float *aumento,Restaurante *rest){
    *aumento = rest->aumento_func_mes;
}

Restaurante* ler_restaurante(){
    FILE *file = fopen("./dados/restaurante.b","rb");
    Restaurante *rest = (Restaurante *) malloc(sizeof(Restaurante));
    rest->caixa=0;
    rest->aumento_func_mes=0;
    if(file!=NULL){
        fread(rest,sizeof(Restaurante),1,file);
    }
    fclose(file);
    return rest;
}

void save_restaurante(Restaurante *rest){
    FILE *file = fopen("./dados/restaurante.b","wb");
    fwrite(rest,sizeof(Restaurante),1,file);
    fclose(file);
}

void descontar_despesa(GtkButton *button, GtkBuilder *builder){
    GtkWidget *etrValorDespesa = GTK_WIDGET(gtk_builder_get_object(builder,"etrDescontarDespesa"));
    float valorDespesa = atof(gtk_entry_get_text(etrValorDespesa));
    if(valorDespesa!=0){
        Restaurante *rest = ler_restaurante();
        set_caixa(valorDespesa*-1,rest);
        save_restaurante(rest);
        gtk_entry_set_text(etrValorDespesa,"");
        load_caixa(builder);
        tela_sucesso(builder,"O valor da despesa foi descontado");
    }else{
        tela_aviso(builder,"O valor da despesa deve ser maior do que 0 e nao deve conter letras");
    }
}
