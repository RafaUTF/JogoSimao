#pragma once
#include <iostream>

template<class TE>
class Elemento
{
private:
	Elemento<TE>* pProx;
	TE Info;
public:
	Elemento(TE i = NULL);
	~Elemento();
	void setProx(Elemento<TE>* pp);
	Elemento<TE>* getProx();
	void setInfo(TE i);
	TE& getInfo();
};

template<class TE>
Elemento<TE>::Elemento(TE i) : pProx(NULL), Info(i) {}
template<class TE>
Elemento<TE>::~Elemento() { pProx = NULL; Info = NULL; }

template<class TE>
void Elemento<TE>::setProx(Elemento<TE>* pp) { pProx = pp; }
template<class TE>
Elemento<TE>* Elemento<TE>::getProx() { return pProx; }

template<class TE>
void Elemento<TE>::setInfo(TE i) { Info = i; }
template<class TE>
TE& Elemento<TE>::getInfo() { return Info; }
