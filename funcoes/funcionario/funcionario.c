#include<gtk-3.0/gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"./funcionario.h"
#include"../restaurante/restaurante.h"
//estrutura do funcionario
struct funcionario{
  char nome[100];
  char rg[30];
  float salario;
  int funcionario_mes;
};
//estrutura para o no da lista de funcionarios
struct no{
    Funcionario dado;
    struct no *prox;
};
//estrutura para a lista de funcionarios
struct lista{
    No *inicio;
};
//funcao para adicionar um novo funcionario
void add_funcionario(GtkButton *button,GtkBuilder *builder){
    GtkWidget *nome = GTK_WIDGET(gtk_builder_get_object(builder,"nomeFuncionarioetr"));
    GtkWidget *rg = GTK_WIDGET(gtk_builder_get_object(builder,"rgFuncionarioetr"));
    GtkWidget *salario = GTK_WIDGET(gtk_builder_get_object(builder,"salarioFuncionarioetr"));

    if(strcmp(gtk_entry_get_text(nome),"")!=0 && strcmp(gtk_entry_get_text(rg),"")!=0 && strcmp(gtk_entry_get_text(salario),"")!=0){
        float salarioF = atof(gtk_entry_get_text(salario));
        if(salario!=0){
            Funcionario f;
            strcpy(f.nome,gtk_entry_get_text(nome));
            strcpy(f.rg,gtk_entry_get_text(rg));
            f.salario = salarioF;
            f.funcionario_mes=0;
            salvar_funcionario(&f);
            gtk_entry_set_text(nome,"");
            gtk_entry_set_text(rg,"");
            gtk_entry_set_text(salario,"");
            tela_sucesso(builder,"O funcionario foi cadastrado com sucesso");
        }else{
            tela_aviso(builder,"O salario deve conter apenas numero e ser maior do que 0");
        }
    }else{
        tela_aviso(builder,"Preencha os campos corretamente");
    }
}
//funcao para editar funcionario
void editar_funcionario(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrRg = GTK_WIDGET(gtk_builder_get_object(builder,"etrRgEditar"));
    GtkWidget *etrNovoRg = GTK_WIDGET(gtk_builder_get_object(builder,"etrNovoRgEditar"));
    GtkWidget *etrNovoNome = GTK_WIDGET(gtk_builder_get_object(builder,"etrNovoNomeEditar"));
    GtkWidget *etrNovoSalario = GTK_WIDGET(gtk_builder_get_object(builder,"etrNovoSalarioEditar"));
    if(strcmp(gtk_entry_get_text(etrRg),"")!=0 && strcmp(gtk_entry_get_text(etrNovoRg),"")!=0 && strcmp(gtk_entry_get_text(etrNovoNome),"")!=0 && strcmp(gtk_entry_get_text(etrNovoSalario),"")!=0){

        Lista_funcionarios funcionarios = ler_funcionarios();
        No *pi = pesquisar_funcionario(&funcionarios,gtk_entry_get_text(etrRg));

        if(pi!=NULL){
            float novoSalario = atof(gtk_entry_get_text(etrNovoSalario));
            if(novoSalario!=0){

                strcpy(pi->dado.rg,gtk_entry_get_text(etrNovoRg));
                strcpy(pi->dado.nome,gtk_entry_get_text(etrNovoNome));
                pi->dado.salario = novoSalario;
                salvar_funcionarios(&funcionarios);
                print_funcionarios_tela(builder);
                gtk_entry_set_text(etrRg,"");
                gtk_entry_set_text(etrNovoRg,"");
                gtk_entry_set_text(etrNovoNome,"");
                gtk_entry_set_text(etrNovoSalario,"");
                tela_sucesso(builder,"Sucesso ao editar o funcionario");
            }else{
                tela_aviso(builder,"O salario do funcionario nao pode conter letras");
            }
        }else{
            tela_aviso(builder,"O funcionario com esse rg nao foi encontrado");
        }
    }else{
        tela_aviso(builder,"E necessario preencher todos os campos para editar um funcionario");
    }
}
//funcao para pagar um funcionario
void pagar_funcionario(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrRg = GTK_WIDGET(gtk_builder_get_object(builder,"etrRgPagar"));
    char rg[30];
    strcpy(rg,gtk_entry_get_text(etrRg));
    Lista_funcionarios funcionarios = ler_funcionarios();
    No *pi = pesquisar_funcionario(&funcionarios,rg);
    if(pi!=NULL){
        Restaurante *rest =ler_restaurante();
        set_caixa(pi->dado.salario*-1,rest);
        save_restaurante(rest);
        load_caixa(builder);
        tela_sucesso(builder,"Sucesso ao pagar o funcionario");
        gtk_entry_set_text(etrRg,"");
    }else{
        tela_aviso(builder,"Nao foi possivel pagar o funcionario ");
    }
}
//funcao para pesquisar um funcionario
No* pesquisar_funcionario(Lista_funcionarios *lista, char rg[]){
    No *pi;
    for(pi=lista->inicio; pi!=NULL && strcmp(pi->dado.rg,rg) != 0;pi =pi->prox);
    return pi;
}
//funcao para demitir funcionario
void demitir_funcionario(GtkButton *button,GtkBuilder *builder){
    GtkWidget *etrRg = GTK_WIDGET(gtk_builder_get_object(builder,"etrRgDemitirFuncionario"));
    char rg[30];
    strcpy(rg,gtk_entry_get_text(etrRg));
    Lista_funcionarios funcionarios= ler_funcionarios();
    deletar_funcionario(builder,&funcionarios,rg);
    print_funcionarios_tela(builder);
    gtk_entry_set_text(etrRg,"");
}
//deletar funcionario
void deletar_funcionario(GtkBuilder *builder,Lista_funcionarios *lista, char rg[]){
    No *pi;
    No *pa=NULL;
    for(pi=lista->inicio;pi!=NULL && strcmp(pi->dado.rg,rg)!=0;pi=pi->prox){
        pa=pi;
    }
    if(pi!=NULL){
        if(pa==NULL){
            lista->inicio = pi->prox;
            free(pi);
            salvar_funcionarios(lista);
        }else{
            pa->prox = pi->prox;
            free(pi);
            salvar_funcionarios(lista);
        }
        tela_sucesso(builder,"Sucesso ao demitir o funcionario ");
    }else{
        tela_aviso(builder,"O funcionario informado nao esta cadastrado");
    }
}
//funcao que faz a listagem dos funcionarios
void listagem_funcionarios(GtkWindow *window,GtkBuilder *builder){
    print_funcionarios_tela(builder);
}
//funcao para printar os funcionarios na tela
void print_funcionarios_tela(GtkBuilder * builder){
    GtkWidget *rglbl = GTK_WIDGET(gtk_builder_get_object(builder,"rgFuncionariolbl"));
    gtk_label_set_text(rglbl,"");

    GtkWidget *nomelbl = GTK_WIDGET(gtk_builder_get_object(builder,"nomeFuncionariolbl"));
    gtk_label_set_text(nomelbl,"");

    GtkWidget *salariolbl = GTK_WIDGET(gtk_builder_get_object(builder,"salarioFuncionariolbl"));
    gtk_label_set_text(salariolbl,"");

    int qtd = qtd_funcionarios();
    if(qtd>0){
        Lista_funcionarios funcionarios = ler_funcionarios();
        int i;
        char rg[qtd*30];
        char nome[qtd*100];
        char salario[qtd*30];
        No *pi;
        for(pi=funcionarios.inicio;pi!=NULL;pi=pi->prox){
            snprintf(rg,30,"%s\n",pi->dado.rg);
            strcat(rg,gtk_label_get_text(rglbl));
            gtk_label_set_text(rglbl,rg);

            snprintf(nome,30,"%s\n",pi->dado.nome);
            strcat(nome,gtk_label_get_text(nomelbl));
            gtk_label_set_text(nomelbl,nome);

            snprintf(salario,30,"%.2f\n",pi->dado.salario);
            strcat(salario,gtk_label_get_text(salariolbl));
            gtk_label_set_text(salariolbl,salario);
        }
    }
}
//funcao para contar a quantidade de funcionarios no arquivo
int qtd_funcionarios(){
    int qtd = 0;
    FILE *file = fopen("./dados/funcionarios.b","rb");
    Funcionario f;
    if(file!=NULL){
        while(fread(&f,sizeof(Funcionario),1,file)){
            qtd++;
        }
    }
    return qtd;
}
//funcao para salvar um funcionario
void salvar_funcionario(Funcionario *f){
    if(qtd_funcionarios()==0){
        FILE *file = fopen("./dados/funcionarios.b","wb");
        fwrite(f,sizeof(Funcionario),1,file);
        fclose(file);
    }else{
        FILE *file = fopen("./dados/funcionarios.b","ab");
        fwrite(f,sizeof(Funcionario),1,file);
        fclose(file);
    }
}
//funcao para ler funcionarios
Lista_funcionarios ler_funcionarios(){
    FILE *file = fopen("./dados/funcionarios.b","rb");
    Lista_funcionarios lista;
    lista.inicio =NULL;
    No *pi;
    if(file!=NULL){
            Funcionario f;
            while(fread(&f,sizeof(Funcionario),1,file)){
                No *pi = (No*) malloc(sizeof(No));
                pi->dado = f;
                pi->prox = lista.inicio;
                lista.inicio = pi;
            }
    }
    return lista;
    fclose(file);
}
//funcao para salvar uma lista de funcionarios
void salvar_funcionarios(Lista_funcionarios *lista){
    FILE *file = fopen("./dados/funcionarios.b","wb");
    No *pi;
    for(pi=lista->inicio;pi!=NULL;pi=pi->prox){
        fwrite(&pi->dado,sizeof(Funcionario),1,file);
    }
    fclose(file);
}
