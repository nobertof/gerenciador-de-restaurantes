#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED
typedef struct no No;

typedef struct lista Lista_funcionarios;

typedef struct funcionario Funcionario;

void add_funcionario(GtkButton *button,GtkBuilder *builder);

void editar_funcionario(GtkButton *button,GtkBuilder *builder);

void pagar_funcionario(GtkButton *button,GtkBuilder *builder);

No* pesquisar_funcionario(Lista_funcionarios *lista, char rg[]);

void demitir_funcionario(GtkButton *button,GtkBuilder *builder);

void deletar_funcionario(GtkBuilder *builder,Lista_funcionarios *lista, char rg[30]);

void listagem_funcionarios(GtkWindow *window,GtkBuilder *builder);

void print_funcionarios_tela(GtkBuilder * builder);

int qtd_funcionarios();

void salvar_funcionario(Funcionario *f);

Lista_funcionarios ler_funcionarios();

void salvar_funcionarios(Lista_funcionarios *lista);
#endif // FUNCIONARIO_H_INCLUDED
