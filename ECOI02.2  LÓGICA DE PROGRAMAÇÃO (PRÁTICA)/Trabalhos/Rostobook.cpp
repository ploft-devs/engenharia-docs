#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <regex>

#define QTDMAXFUNC 20
#define QTDMAXPOST 100
#define QTDMAXCMT 500

using namespace std;

struct Comentario {
    int id;
	char cmt[141];
};

struct Post {
    int id;
    int qtdCmt;
	char pub[141];
	Comentario com[5];
};

struct Funcionarios{
    int id;
    int qtdPosts;
    Post post[5];
    char nome[100];
    string email;
};

void menu();
void cadFuncionario(Funcionarios f[], Funcionarios faz[], int &qtdFunc);
void cadPost(Post post[], Funcionarios f[],int &qtdPost, int qtdFunc);
void cadComentario(Funcionarios f[], Post post[], Comentario com[], int &qtdCmt ,int qtdPost, int  qtdFunc);
void listarPostsEComentarios (Funcionarios f[], Post post[], Comentario com[], int qtdFunc, int qtdPosts, int qtdCmt);
void listarQtdPostsFuncionario(Funcionarios f[], int qtdFunc);
void listarFuncionarios(Funcionarios f[], int qtdFunc);
void ordenarAZ(Funcionarios faz[], int qtdFunc);
void listarFuncionariosAZ(Funcionarios faz[], int qtdFunc);
void swap(int *xp, int *yp);
bool validarEmail(string email);
bool vefFuncionarioById(Funcionarios f[], int id, int qtdFunc);
bool vefPostById (Post post[], int id, int qtdPost);

/**
    Onde a mágica acontece
*/
int main(){
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}

/**
    Método ultilizado para inciar o menu e mostrar as opções disponiveis do sistema
*/
void menu(){
    int op = 0, qtdFunc = 0, qtdPosts = 0, qtdCmt = 0;
    Funcionarios f[QTDMAXFUNC], faz[QTDMAXFUNC];
    Post post[QTDMAXPOST];
    Comentario com[QTDMAXCMT];
    do{
        system("cls");
        cout << "SISTEMA  ROSTOBOOK" << endl << endl;
        cout << "(0) - Sair" << endl;
        cout << "(1) - Inserir dados de um funcionário" << endl;
        cout << "(2) - Emitir um post" << endl;
        cout << "(3) - Emitir um comentário" << endl;
        cout << "(4) - Listar posts de um funcionário e os comentários descritos" << endl;
        cout << "(5) - Listar funcionários com suas respectivas quantidades de posts enviados" << endl;
        cout << "(6) - Listar funcionários por ordem alfabética" << endl;
        cout << "(7) - Listar funcionários por ordem de inserção no sistema" << endl;
        cout << "\nOpção:";
        cin >> op;
        switch(op){
            case 0:
                break;
            case 1:
                cadFuncionario(f, faz, qtdFunc);
                break;
            case 2:
                cadPost(post, f, qtdPosts, qtdFunc);
                break;
            case 3:
                cadComentario(f, post, com, qtdCmt, qtdPosts, qtdFunc);
                break;
            case 4:
                listarPostsEComentarios (f, post, com, qtdFunc, qtdPosts, qtdCmt);
                break;
            case 5:
                listarQtdPostsFuncionario(f, qtdFunc);
                break;
            case 6:
                listarFuncionariosAZ(faz, qtdFunc);
                break;
            case 7:
                listarFuncionarios(f, qtdFunc);
                break;
            default:
                cout <<"\aOpção inválida!\n\n";
        }
    }while( op != 0);
}

/**
    Método ultilizado para cadastrar novos funcionarios no sistema
    Parametros - vetor de funcionarios, vetor auxiliar de funcionarios e quantidade total de funcionarios cadastrados no sistema
*/
void cadFuncionario(Funcionarios f[], Funcionarios faz[], int &qtdFunc){
    system("cls");
    cout << "CADASTRO DE FUNCIONÁRIO" << endl;

    f[qtdFunc].id = qtdFunc;
    f[qtdFunc].qtdPosts = 0;
    cout << endl << "Nome: ";
    fflush(stdin);
    gets(f[qtdFunc].nome);
    cout <<"E-mail: ";
    getline(cin, f[qtdFunc].email);

    while(!(validarEmail(f[qtdFunc].email))){
        cout << endl << "E-mail inválido!";
        cout << endl << "Digite novamente...";
        cout << endl << "E-mail: ";
        getline(cin, f[qtdFunc].email);
    }

    faz[qtdFunc] = f[qtdFunc];
    qtdFunc++;
    cout << endl << "Funcionário cadastrado com Sucesso!" << endl;
    system("pause");
}

/**
    Método ultilizado para cadastrar novos Posts no sistema
    Parametros - vetor de Posts, quantidade total de posts cadastrados no sistema e quantidade total de funcionarios cadastrados no sistema
*/
void cadPost(Post post[], Funcionarios f[], int &qtdPost, int qtdFunc){
    system("cls");
    if(qtdFunc > 0){
        cout << "CADASTRO DE POST" << endl << endl;

        int id;
        cout << "Digite o id do funcionário: ";
        cin >> id;

        while(!(vefFuncionarioById(f, id, qtdFunc))){
            cout << "Funcionário não encontrado!" << endl;
            cout << "Digite novamente: ";
            cin >> id;
            cout << endl;
        }
        cout << endl << "Funcionário encontrado com sucesso!";
        cout << endl << "Nome: " << f[id].nome << endl;
        cout << endl << "Insira seu Post (Maximo 140 caracteres): ";
        fflush(stdin);
        gets(post[qtdPost].pub);

        post[qtdPost].id = qtdPost;

        f[id].post[f[id].qtdPosts] = post[qtdPost];
        f[id].qtdPosts +=1;

        qtdPost++;
        cout << endl << "Post cadastrado com Sucesso!" << endl;
    }else cout << "NENHUM FUNCIONÁRIO CADASTRADO NO SISTEMA..." << endl << endl;

    system("pause");
}


void cadComentario (Funcionarios f[], Post post[], Comentario com[], int &qtdCmt ,int qtdPost, int  qtdFunc){
    system("cls");
    if (qtdPost > 0) {
        cout << "CADASTRO DE COMENTÁRIO" << endl;

        int idF;
        cout << "Digite o id do funcionario: ";
        cin >> idF;

         while(!(vefFuncionarioById(f, idF, qtdFunc))){
            cout << "Funcionário não encontrado!" << endl;
            cout << "Digite novamente: ";
            cin >> idF;
            cout << endl;
        }
        system("cls");
        cout << endl << "Funcionario encontrado com sucesso!\nLista de posts do funcionario: " << endl;
        for (int i = 0; i < f[idF].qtdPosts; i++) {
            cout << "ID: " << i << endl;
            cout << f[idF].post[i].pub;
            cout << "\n-----------------\n";
        }

        int idP;
        cout << "\nDigite o id do post: ";
        cin >> idP;

        while(idP < 0 || idP > f[idF].qtdPosts){
            cout << "Post não encontrado!" << endl;
            cout << "Digite novamente: ";
            cin >> idP;
            cout << endl;
        }

        system("cls");

        cout << endl << "Post encontrado com sucesso!";
        cout << endl << "Post: " << f[idF].post[idP].pub << endl;
        cout << endl << "Insira seu Comentário (Maximo 140 caracteres): ";
        fflush(stdin);
        gets(com[qtdCmt].cmt);
        com[qtdCmt].id = qtdCmt;

        int aux = f[idF].post[idP].qtdCmt;
        f[idF].post[idP].com[aux] = com[qtdCmt];

        qtdCmt++;
        f[idF].post[idP].qtdCmt++;
        cout << endl << "Comentario cadastrado com Sucesso!" << endl;
    } else {
        cout << "NENHUM POST CADASTRADO..." << endl << endl;
    }
    system("pause");
}

void listarPostsEComentarios (Funcionarios f[], Post post[], Comentario com[], int qtdFunc, int qtdPosts, int qtdCmt){
    system("cls");

    if (qtdFunc > 0) {
        int id;
        cout << "Insira o ID do Funcionário: ";
        cin >> id;

        while(!(vefFuncionarioById(f, id, qtdFunc))){
            cout << "Funcionário não encontrado!" << endl;
            cout << "Digite novamente: ";
            cin >> id;
            cout << endl;
        }
        for (int i = 0; i < f[id].qtdPosts; i++) {
            cout << "ID do Post: " << f[id].post[i].id << endl;
            cout << f[id].post[i].pub;

            if (f[id].post[i].qtdCmt > 0) {
                cout << "\n-----------------\n" << endl << "COMENTARIOS: ";
                for (int j = 0; j < f[id].post[i].qtdCmt; j++) {
                    cout << endl << f[id].post[i].com[j].id << " | " <<  f[id].post[i].com[j].cmt;
                }
            }
            cout << "\n-----------------\n" << endl;
        }


    } else cout << "NENHUM FUNCIONÁRIO CADASTRADO NO SISTEMA..." << endl << endl;

    cout << endl;
    system("pause");
}

/**
    Método ultilizado para listar os funcionarios em ordem alfabetica
    Receber por parametro um vetor auxiliar de funcionarios e a quantidade total de funcionario cadastrados no sistema
*/
void listarQtdPostsFuncionario(Funcionarios f[], int qtdFunc){
    system("cls");
    if(qtdFunc > 0){
        cout << "FUNCIONÁRIO E SUA RESPECTIVA QUANTIDADE DE POSTS ENVIADOS" << endl << endl;
        int id;
        cout << "Digite o id do funcionário: ";
        cin >> id;

        while(!(vefFuncionarioById(f, id, qtdFunc))){
            cout << "Funcionário não encontrado!" << endl;
            cout << "Digite novamente: ";
            cin >> id;
            cout << endl;
        }

        if(f[id].qtdPosts == 0){
            cout << endl << "O Funcionário " << f[id].nome << " não possui posts cadastrados no sistema..." << endl << endl;
        }else{
            cout << "Id: " << f[id].id;
            cout << "Nome: " << f[id].nome;
            cout << endl << "E-mail: " << f[id].email;
            cout << endl << "Quantidade de Posts: " << f[id].qtdPosts;
            cout << endl << endl;

            cout << "Posts:" << endl;
            for(int i=0; i<f[id].qtdPosts; i++){
                cout << endl << "Post id[" << i <<"]: "<< f[id].post[i].pub << endl;
            }
        }
    }else cout << "NÃO HÁ FUNCIONÁRIOS CASTRADOS PARA ESTÁ LISTAGEM" << endl << endl;


    cout << endl;
    system("pause");
}

/**
    Método ultilizado para listar os funcionarios cadastrados no sistema
    Receber por parametro um vetor de funcionarios e a quantidade total de funcionario cadastrados no sistema
*/
void listarFuncionarios(Funcionarios f[], int qtdFunc){
    system("cls");

    if(qtdFunc > 0){
        cout << "LISTA DE FUNCIONÁRIO EM ORDEM DE INSERÇÃO NO SISTEMA" << endl << endl;
        for(int i=0; i<qtdFunc; i++){
            cout << "Id: " << f[i].id;
            cout << endl << "Nome: " << f[i].nome;
            cout << endl << "E-mail: " << f[i].email;
            cout << endl << endl;
        }
        cout << endl;
    }else cout << "NENHUM FUNCIONÁRIO CADASTRADO NO SISTEMA..." << endl << endl;
    system("pause");
}

/**
    Método ultilizado para listar os funcionarios em ordem alfabetica
    Receber por parametro um vetor auxiliar de funcionarios e a quantidade total de funcionario cadastrados no sistema
*/
void listarFuncionariosAZ(Funcionarios faz[], int qtdFunc){
    system("cls");
    if(qtdFunc > 0){
        cout << "LISTA DE FUNCIONÁRIO EM ORDEM ALFABÉTICA" << endl << endl;

        if(qtdFunc > 1) ordenarAZ(faz, qtdFunc);
        for(int i=0; i<qtdFunc; i++){
            cout << endl << "Nome: " << faz[i].nome;
            cout << endl << "E-mail: " << faz[i].email;
            cout << endl << endl;
        }
        cout << endl;
    }else cout << "NENHUM FUNCIONÁRIO CADASTRADO NO SISTEMA..." << endl << endl;
    system("pause");
}

/**
    Método  ultilizada para colocar o vetor faz em ordem alfabetica
    Parametros - um vetor auxiliar de Funcionarios faz[] e a quantidade de funcionarios cadastrados no sistema
*/
void ordenarAZ(Funcionarios faz[], int n){
    int i, j, min_idx;
    for (i = 0; i < n-1; i++){
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (strcmp(faz[j].nome, faz[min_idx].nome) < 0 )
            min_idx = j;
        swap(faz[min_idx], faz[i]);
    }
}

/**
    Método  ultilizada para realizar a troca entre as posições do vetor
*/
void swap(Funcionarios xp, Funcionarios yp){
    Funcionarios temp = xp;
    xp = yp;
    yp = temp;
}

/**
    Método  ultilizada para validar o email;
    Parametro - recebe uma string
*/
bool validarEmail(string email){
   const regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

   return regex_match(email, pattern);
}

/**
     Recebe um vetor de Funcionario, id do funcionario e a quantidade de funcionarios cadastrados no sistema
     Retorna true - se o id do funcionario recebido existir no sistema
     Retorna false - caso contrario.[
 */
bool vefFuncionarioById(Funcionarios f[], int id, int qtdFunc){
    for(int i=0; i<qtdFunc; i++) if(f[i].id == id) return true;
    return false;
}

/**
    Recebe um vetor de Posts, id do post e a quantidade de posts cadastrados no sistema
    Retorna true - se o id recebido existir no sistema
    Retorna false - caso contrario
*/
bool vefPostById (Post post[], int id, int qtdPost){
    for(int i=0; i<qtdPost; i++) if(post[i].id == id) return true;
    return false;
}










