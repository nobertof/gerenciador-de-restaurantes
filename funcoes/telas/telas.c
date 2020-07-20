#include<gtk-3.0/gtk/gtk.h>
#include "./telas.h"
#include "../cardapio/cardapio.h"
#include "../funcionario/funcionario.h"
//funcao que carrega a tela principal
void load_tela_principal(GtkBuilder *builder){
    GtkWidget  *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaPrincipal"));
    gtk_window_set_title(window,"Tela Principal");
    gtk_widget_show(window);
}
//carrega a tela para demitir um funcionario
void load_demitir_funcionario(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarFuncionario"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensPagarFuncionario"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDemitirFuncionario"));
    gtk_widget_set_visible(itens,TRUE);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaFuncionarios"));
    gtk_window_set_title(window,"Funcionarios");
    print_funcionarios_tela(builder);
    gtk_widget_show(window);
}
//funcao para mostrar tela de editar um funcionario
void load_editar_funcionario(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDemitirFuncionario"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensPagarFuncionario"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarFuncionario"));
    gtk_widget_set_visible(itens,TRUE);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaFuncionarios"));
    gtk_window_set_title(window,"Funcionarios");
    print_funcionarios_tela(builder);
    gtk_widget_show(window);
}
//funcao para mostrar a tela de pagar funcionarios
void load_pagar_funcionario(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDemitirFuncionario"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarFuncionario"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensPagarFuncionario"));
    gtk_widget_set_visible(itens,TRUE);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaFuncionarios"));
    gtk_window_set_title(window,"Funcionarios");
    print_funcionarios_tela(builder);
    gtk_widget_show(window);
}
//funcao para carregar a tela de funcionarios
void load_tela_funcionarios(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarFuncionario"));
    gtk_widget_set_visible(itens,FALSE);

    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDemitirFuncionario"));
    gtk_widget_set_visible(itens,FALSE);

    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensPagarFuncionario"));
    gtk_widget_set_visible(itens,FALSE);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaFuncionarios"));
    gtk_window_set_title(window,"Funcionarios");
    gtk_widget_show(window);
}
//funcao para carregar a tela de adicionar funcionario
void load_tela_add_funcionario(GtkButton *button, GtkBuilder *builder){
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaAddFuncionario"));
    gtk_window_set_title(window,"Adicionar funcionario");
    gtk_widget_show(window);
}
//funcao para carregar a tela para atualizar um prato do cardapio
void load_tela_editar_prato(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDeletarCardapio"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarPrato"));
    gtk_widget_set_visible(itens,TRUE);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaCardapios"));
    gtk_window_set_title(window,"Cardapios");
    gtk_widget_show(window);
}
//funcao para carregar a tela de deletar cardapio
void load_tela_deletar_cardapio(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDeletarCardapio"));
    gtk_widget_set_visible(itens,TRUE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarPrato"));
    gtk_widget_set_visible(itens,FALSE);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaCardapios"));
    gtk_window_set_title(window,"Cardapios");
    gtk_widget_show(window);
}
//funcao para carregar a tela de cardapios
void load_tela_cardapios(GtkButton *button, GtkBuilder *builder){
    GtkWidget *itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensDeletarCardapio"));
    gtk_widget_set_visible(itens,FALSE);
    itens = GTK_WIDGET(gtk_builder_get_object(builder,"itensEditarPrato"));
    gtk_widget_set_visible(itens,FALSE);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaCardapios"));
    gtk_window_set_title(window,"Cardapios");
    gtk_widget_show(window);
}
// funcao que carrega a tela para adicao de pratos
void load_tela_add_prato(GtkButton *button, GtkBuilder *builder){
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaAddPrato"));
    gtk_window_set_title(window,"Adicionar um novo prato");
    gtk_widget_show(window);
}
//funcao que carrega a tela para adicionar cardapio
void load_tela_add_cardapio(GtkButton *button, GtkBuilder *builder){
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaAddCardapio"));
    gtk_window_set_title(window,"Adicionar novo cardapio");
    load_pratos(builder);
    gtk_widget_show(window);
}
// funcao para carregar a tela de adicionar um novo pedido
void load_add_new_pedido(GtkButton *button, GtkBuilder *builder){
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder,"telaAddPedido"));
    gtk_window_set_title(window,"Adicionar novo pedido");
    gtk_widget_show(window);
}
// funcao para carregar a tela de adicionar uma nova mesa
void load_add_new_mesa(GtkButton *button, GtkBuilder *builder){
    GtkWidget *window= GTK_WIDGET(gtk_builder_get_object(builder,"telaAddMesa"));
    gtk_window_set_title(window,"Adicionar nova mesa ");
    gtk_widget_show(window);
}
//funcao para carregar a tela de despesas
void load_tela_despesa(GtkButton *button, GtkBuilder *builder){
    GtkWidget *window= GTK_WIDGET(gtk_builder_get_object(builder,"telaDespesa"));
    gtk_window_set_title(window,"Despesa");
    gtk_widget_show(window);
}
