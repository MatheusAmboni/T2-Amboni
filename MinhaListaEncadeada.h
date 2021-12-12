#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{

public:

    MinhaListaEncadeada(){
        ListaEncadeadaAbstrata<T>::_primeiro = NULL;
        ListaEncadeadaAbstrata<T>::_tamanho = 0;
    }

    ~MinhaListaEncadeada()
    {
      Elemento<T> *ProximoElemento = NULL;
      Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro;

      while(ElementoAuxiliar != NULL)
      {
        ProximoElemento = ElementoAuxiliar->proximo;
        delete ElementoAuxiliar;
        ElementoAuxiliar = ProximoElemento;
      }
    };

    std::size_t tamanho() const{
        int count = 0;
        Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;

        if (atual == NULL){
            return 0;
        }
        else{
            while (atual != NULL){
                atual = atual->proximo;
                count++;
            }
        }
        return count;
    };

    bool vazia() const{
        if (ListaEncadeadaAbstrata<T>::_primeiro == NULL){
            return true;
        }
        else{
            return false;
        }
    };

    std::size_t posicao(T dado) const{
        if(ListaEncadeadaAbstrata<T>::_tamanho == 0)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
    else
    {
	bool check = false;
        Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro;
        size_t indice = 0;
        while (ElementoAuxiliar != NULL)
        {
          if(dado == ElementoAuxiliar->dado)
          {
		check = true;
            return indice;
          }
          indice++;
          ElementoAuxiliar = ElementoAuxiliar->proximo;
        }
	if(check == false)
	{
		throw ExcecaoDadoInexistente();
	} 
      return 0;
    }
    };

    bool contem(T dado) const{
        Elemento<T> *ElemAtual = (ListaEncadeadaAbstrata<T>::_primeiro);
            while(ElemAtual != NULL){
                if (ElemAtual->dado == dado){
                    return true;
                }
                ElemAtual = ElemAtual->proximo;
            }
            return false;
    };

void inserirNoInicio(T dado)
  {
    Elemento<T> *novoElemento = new Elemento<T>(dado, nullptr);
    novoElemento->proximo = ListaEncadeadaAbstrata<T>::_primeiro;
    ListaEncadeadaAbstrata<T>::_primeiro = novoElemento;
    ListaEncadeadaAbstrata<T>::_tamanho++;
  };

  void inserir(size_t posicao, T dado)
  {
    int tamanhoLista = static_cast<int>(tamanho());
    int posicaoInt = static_cast<int>(posicao);
    if(posicaoInt == 0 && tamanhoLista >= 0)
    {
      inserirNoInicio(dado);
    }
    else if (posicaoInt < 0)
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if (posicaoInt > tamanhoLista)
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if(posicaoInt == tamanhoLista)
    {
      inserirNoFim(dado);
    }
    else
    {
      int aux = 0;
      Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro ;
      while(aux < posicaoInt - 1 && ElementoAuxiliar->proximo != NULL && ElementoAuxiliar != NULL)
      {
        ElementoAuxiliar = ElementoAuxiliar->proximo;
        aux++;
      }
      Elemento<T> *NovoElemento = new Elemento<T>(dado, nullptr);
      NovoElemento->proximo = ElementoAuxiliar->proximo;
      ElementoAuxiliar->proximo = NovoElemento;
      ListaEncadeadaAbstrata<T>::_tamanho++;
    }
    return;
  };

void inserirNoFim(T dado)
  {
    if(ListaEncadeadaAbstrata<T>::_primeiro == NULL)
    {
      inserirNoInicio(dado);
      return;
    }
    else
    {
      Elemento<T> *NovoElemento = new Elemento<T>(dado, nullptr);
      Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro;
      NovoElemento->proximo = NULL;
      while (ElementoAuxiliar->proximo != NULL)
      {
        ElementoAuxiliar = ElementoAuxiliar->proximo;
      }
      ElementoAuxiliar->proximo = NovoElemento;
      ListaEncadeadaAbstrata<T>::_tamanho++;
      return;
    }
  };

    T removerDoInicio()
    {
    if(ListaEncadeadaAbstrata<T>::_tamanho == 0)
    {
      throw ExcecaoListaEncadeadaVazia();
    }
    else
    {
      Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro;
      T dadoAux = ElementoAuxiliar->dado;
      ListaEncadeadaAbstrata<T>::_primeiro = ListaEncadeadaAbstrata<T>::_primeiro->proximo;
      delete ElementoAuxiliar;
      ListaEncadeadaAbstrata<T>::_tamanho--;
      return dadoAux;
    }
  };

    T removerDe(size_t posicao)
  {
    int tamanhoLista = tamanho();
    int posicaoInt = static_cast<int>(posicao);
    if (vazia())
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if(posicaoInt < 0 || posicaoInt >= tamanhoLista)
    {
      throw ExcecaoPosicaoInvalida();
    }
    else if (posicaoInt == 0)
    {
        T a = removerDoInicio();
        return a;
    }
    else
    {
      Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro;
      for (int i = 0; ElementoAuxiliar != NULL && i < posicaoInt-1; i++)
      {
        ElementoAuxiliar = ElementoAuxiliar->proximo;
      }
      if (ElementoAuxiliar->proximo->proximo == NULL)
      {
        T a = removerDoFim();
        return a;
      }
      else if (ElementoAuxiliar != NULL || ElementoAuxiliar->proximo != NULL)
      {
        Elemento<T> *ElementoDeletado = ElementoAuxiliar->proximo;
        ElementoAuxiliar->proximo = ElementoAuxiliar->proximo->proximo;
        T aux = ElementoDeletado->dado;
        delete ElementoDeletado;
        ListaEncadeadaAbstrata<T>::_tamanho--;
        return aux;
      }
    }
    return 0;
  };

    T removerDoFim()
      {
        Elemento<T> *ElementoAuxiliar = ListaEncadeadaAbstrata<T>::_primeiro;
        if (ListaEncadeadaAbstrata<T>::_primeiro == NULL)
        {
          throw ExcecaoListaEncadeadaVazia();
        }
        else if (ElementoAuxiliar->proximo == NULL)
        {
          return removerDoInicio();
        }
        else
        {
          while (ElementoAuxiliar->proximo->proximo != NULL)
          {
            ElementoAuxiliar = ElementoAuxiliar->proximo;
          }
          Elemento<T> *ultimoElemento = ElementoAuxiliar->proximo;
          ElementoAuxiliar->proximo = NULL;
          T DadoRemovido = ultimoElemento->dado;
          delete ultimoElemento;
          ListaEncadeadaAbstrata<T>::_tamanho--;
          return DadoRemovido;
        }
        return 0;
      };

    void remover(T dado)
    {
      if(ListaEncadeadaAbstrata<T>::_primeiro == NULL)
      {
        throw ExcecaoListaEncadeadaVazia();
      }
      else if(!contem(dado))
      {
        throw ExcecaoDadoInexistente();
      }
      else
      {
        size_t indice = posicao(dado);
        removerDe(indice);
      } 
    };
};

#endif