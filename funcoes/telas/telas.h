#ifndef TELAS_H_INCLUDED
#define TELAS_H_INCLUDED
void load_tela_principal(GtkBuilder *builder);

void load_demitir_funcionario(GtkButton *button, GtkBuilder *builder);

void load_editar_funcionario(GtkButton *button, GtkBuilder *builder);

void load_pagar_funcionario(GtkButton *button, GtkBuilder *builder);

void load_tela_funcionarios(GtkButton *button, GtkBuilder *builder);

void load_tela_add_funcionario(GtkButton *button, GtkBuilder *builder);

void load_tela_editar_prato(GtkButton *button, GtkBuilder *builder);

void load_tela_deletar_cardapio(GtkButton *button, GtkBuilder *builder);

void load_tela_cardapios(GtkButton *button, GtkBuilder *builder);

void load_tela_add_prato(GtkButton *button, GtkBuilder *builder);

void load_tela_add_cardapio(GtkButton *button, GtkBuilder *builder);

void load_add_new_pedido(GtkButton *button, GtkBuilder *builder);

void load_add_new_mesa(GtkButton *button, GtkBuilder *builder);

void load_tela_despesa(GtkButton *button, GtkBuilder *builder);
#endif // TELAS_H_INCLUDED
