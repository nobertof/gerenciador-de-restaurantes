#ifndef RESTAURANTE_H_INCLUDED
#define RESTAURANTE_H_INCLUDED
typedef struct restaurante Restaurante;

void load_dados_restaurante(GtkWindow *window, GtkBuilder *builder);

void load_caixa(GtkBuilder *builder);

void tela_sucesso(GtkBuilder *builder,char msg[100]);

void tela_aviso(GtkBuilder *builder, char msg[100]);

void get_caixa(float*caixa,Restaurante *rest);

void set_caixa(float caixa, Restaurante *rest);

void set_aumento_func_mes(float aumento, Restaurante *rest);

void get_aumento_func_mes(float *aumento,Restaurante *rest);

Restaurante* ler_restaurante();

void save_restaurante(Restaurante *rest);

void descontar_despesa(GtkButton *button, GtkBuilder *builder);
#endif // RESTAURANTE_H_INCLUDED
