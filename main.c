#include<gtk-3.0/gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "./funcoes/cardapio/cardapio.h"
#include"./funcoes/funcionario/funcionario.h"
#include "./funcoes/telas/telas.h"
#include "./funcoes/mesa/mesa.h"
#include "./funcoes/restaurante/restaurante.h"
#include "./funcoes/pedido/pedido.h"

void close_program(GtkWindow *window,GtkBuilder *builder);

void close_window(GtkWindow *window,GtkBuilder *builder);

int main(int argc, char *argv[]){
    //inicializando o gtk
    gtk_init(&argc,&argv);
    //guardando o construtor das telas do sistema no builder do gerenciador
    GtkBuilder *builder = gtk_builder_new_from_file("interfaceEstrutura.glade");
    GError **err;
    gtk_window_set_default_icon_from_file("./imagens/mesas3.png",err);
    // adicionando todas as chamadas de funcoes do sistema
    gtk_builder_add_callback_symbols(builder
                                     ,"descontarDespesa",G_CALLBACK(descontar_despesa)
                                     ,"load_tela_despesa",G_CALLBACK(load_tela_despesa)
                                     ,"finalizar_pedido",G_CALLBACK(finalizar_pedido)
                                     ,"pesquisar_pedido",G_CALLBACK(pesquisar_pedido)
                                     ,"pedido_anterior",G_CALLBACK(pedido_anterior)
                                     ,"proximo_pedido",G_CALLBACK(proximo_pedido)
                                     ,"add_new_pedido",G_CALLBACK(add_new_pedido)
                                     ,"cardapio_anterior",G_CALLBACK(cardapio_anterior)
                                     ,"proximo_cardapio",G_CALLBACK(proximo_cardapio)
                                     ,"load_dados_cardapios",G_CALLBACK(load_dados_cardapios)
                                     ,"adicionar_cardapio",G_CALLBACK(adicionar_cardapio)
                                     ,"addPrato",G_CALLBACK(add_prato)
                                     ,"limpar_pratos",G_CALLBACK(limpar_pratos)
                                     ,"listagem_funcionarios",G_CALLBACK(listagem_funcionarios)
                                     ,"add_funcionario",G_CALLBACK(add_funcionario)
                                     ,"load_dados_restaurante",G_CALLBACK(load_dados_restaurante)
                                     ,"ocupar_mesa",G_CALLBACK(ocupar_mesa)
                                     ,"mesas_anteriores",G_CALLBACK(mesa_anterior)
                                     ,"proximas_mesas",G_CALLBACK(proxima_mesa)
                                     ,"add_new_mesa",G_CALLBACK(add_new_mesa)
                                     ,"delete_mesa",G_CALLBACK(delete_mesa)
                                     ,"pesquisar_mesa",G_CALLBACK(pesquisar_mesa)
                                     ,"limpar_mesa",G_CALLBACK(limpar_mesa)
                                     ,"add_cliente",G_CALLBACK(add_cliente)
                                     ,"load_tela_add_prato",G_CALLBACK(load_tela_add_prato)
                                     ,"load_tela_add_cardapio",G_CALLBACK(load_tela_add_cardapio)
                                     ,"load_tela_add_funcionario",G_CALLBACK(load_tela_add_funcionario)
                                     ,"telaPagarFuncionario",G_CALLBACK(load_pagar_funcionario)
                                     ,"pagarFuncionario",G_CALLBACK(pagar_funcionario)
                                     ,"editarFuncionario",G_CALLBACK(editar_funcionario)
                                     ,"demitirFuncionario",G_CALLBACK(demitir_funcionario)
                                     ,"telaDemitirFuncionario",G_CALLBACK(load_demitir_funcionario)
                                     ,"telaEditarFuncionario",G_CALLBACK(load_editar_funcionario)
                                     ,"load_tela_funcionarios",G_CALLBACK(load_tela_funcionarios)
                                     ,"apagarCardapio",G_CALLBACK(apagar_cardapio)
                                     ,"editar_cardapio",G_CALLBACK(editar_cardapio)
                                     ,"load_tela_editar_prato",G_CALLBACK(load_tela_editar_prato)
                                     ,"load_tela_apagar_cardapio",G_CALLBACK(load_tela_deletar_cardapio)
                                     ,"load_tela_cardapios",G_CALLBACK(load_tela_cardapios)
                                     ,"load_add_new_mesa",G_CALLBACK(load_add_new_mesa)
                                     ,"load_add_new_pedido",G_CALLBACK(load_add_new_pedido)
                                     ,"close_window",G_CALLBACK(close_window)
                                     ,"close_program",G_CALLBACK(close_program)
                                     ,NULL);
    //conectando todos os sinais que foram adicionados
    gtk_builder_connect_signals(builder,builder);
    //chamando a funcao para mostrar a tela principal do sistema
    load_tela_principal(builder);
    //liberando o espaco do gerenciador

    gtk_main();
}
//funcao para encerrar o sistema
void close_program(GtkWindow *window,GtkBuilder *builder){
    gtk_main_quit();
}
// funcao para fechar a tela e nao bugar
void close_window(GtkWindow *window,GtkBuilder *builder){
    gtk_widget_set_visible(GTK_WIDGET(window),0);
}
