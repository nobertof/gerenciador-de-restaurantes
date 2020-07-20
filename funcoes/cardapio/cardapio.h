#ifndef CARDAPIO_H_INCLUDED
#define CARDAPIO_H_INCLUDED
typedef struct cardapio Cardapio;

typedef struct prato Prato;

void adicionar_cardapio(GtkButton *button,GtkBuilder *builder);

void apagar_cardapio(GtkButton *button,GtkBuilder *builder);

void editar_cardapio(GtkButton *button,GtkBuilder *builder);

void add_prato(GtkButton *button,GtkBuilder *builder);

void load_dados_cardapios(GtkWindow *window,GtkBuilder *builder);

void proximo_cardapio(GtkButton *button,GtkBuilder *builder);

void cardapio_anterior(GtkButton *button,GtkBuilder *builder);

void load_pratos(GtkBuilder *builder);

void load_prato(GtkBuilder *builder);

void salvar_cardapio(Cardapio *c);

void salvar_prato(int card,Prato *p);

void salvar_pratos(int card,Prato *p,int qtd);

int qtd_cardapios();

int qtd_pratos(int card);

void ler_cardapios(Cardapio *c,int qtd);

void salvar_cardapios(Cardapio *c,int qtd);

int busca_binaria_pratos(int idPrato,int i,int f,Prato *p);

void ler_pratos(int card, Prato *p,int qtd);

void limpar_pratos(GtkButton *button,GtkBuilder *builder);

void zerar_pratos(int idx,GtkBuilder *builder);
#endif // CARDAPIO_H_INCLUDED
