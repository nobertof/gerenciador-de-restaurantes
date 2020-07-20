#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED
typedef struct pedido Pedido;

typedef struct no No;

typedef struct lista_pedidos Lista_pedidos;

void add_new_pedido(GtkButton* button, GtkBuilder *builder);

void salvar_pedido(Pedido *p);

void load_pedidos(GtkBuilder *builder);

void pedido_anterior(GtkButton *button, GtkBuilder *builder);

void proximo_pedido(GtkButton *button, GtkBuilder *builder);

Lista_pedidos ler_pedidos();

void salvar_pedidos(Lista_pedidos *pedidos);

int qtd_pedidos();

void pesquisar_pedido(GtkButton *button,GtkBuilder *builder);

void finalizar_pedido(GtkButton *button,GtkBuilder *builder);

Pedido pesquisaPed(Lista_pedidos pedidos,int pos);
#endif // PEDIDO_H_INCLUDED
