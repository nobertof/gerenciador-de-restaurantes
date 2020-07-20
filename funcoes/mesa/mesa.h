#ifndef MESA_H_INCLUDED
#define MESA_H_INCLUDED
typedef struct mesa Mesa;

typedef struct cliente Cliente;

void add_new_mesa(GtkButton *button,GtkBuilder *builder);

void limpar_mesa(GtkButton *button,GtkBuilder *builder);

void ocupar_mesa(GtkButton *button,GtkBuilder *builder);

void add_cliente(GtkButton *button,GtkBuilder *builder);

void mesa_anterior(GtkButton *button,GtkBuilder *builder);

void proxima_mesa(GtkButton *button,GtkBuilder *builder);

void salvar_mesa(Mesa *novaMesa);

void update_mesas(Mesa *mesas,int qtd);

void delete_mesa(GtkButton *button,GtkBuilder *builder);

void pesquisar_mesa(GtkButton *button,GtkBuilder *builder);

int busca_binaria_mesas(int numeroMesa,int i, int f, Mesa *mesas);

void ordenar_mesas(Mesa *mesas,int qtd);

void load_mesas(GtkBuilder *builder);

int qtd_mesas();
#endif // MESA_H_INCLUDED
