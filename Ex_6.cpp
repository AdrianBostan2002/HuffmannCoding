#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <queue>

class Node
{
public:
	int valoare;
	std::string caractere;
	Node* left;
	Node* right;
	Node* parent;
};

struct comparator
{
	bool operator()(Node* a, Node* b)
	{
		return a->valoare > b->valoare;
	}
};

void citire_propozitie(std::string& propozitie)
{
	std::ifstream fin;
	fin.open("input.in");
	std::getline(fin, propozitie);
	fin.close();
}

void determinare_frecventa_caractere(std::string propozitie, std::unordered_map<std::string, int>& fr_caractere)
{
	std::string temp;
	std::unordered_map<std::string, int>::iterator it;
	for (int i = 0; i < propozitie.size(); i++)
	{
		temp = propozitie[i];
		it = fr_caractere.find(temp);
		if (it != fr_caractere.end())
		{
			fr_caractere[temp]++;
		}
		else
		{
			fr_caractere[temp] = 1;
		}
	}
}

Node* combine_doua_noduri_intr_unul(Node* nod1, Node* nod2)
{
	Node* nod_nou = new Node;
	nod_nou->valoare = nod1->valoare + nod2->valoare;
	nod_nou->caractere = nod1->caractere + nod2->caractere;
	nod1->parent = nod_nou;
	nod2->parent = nod_nou;
	nod_nou->left = nod1;
	nod_nou->right = nod2;
	return nod_nou;

}

void construire_arbore_Huffman(std::unordered_map<std::string, int> fr_caractere, std::priority_queue<Node*, std::vector<Node*>, comparator>& coada_de_prioritati)
{
	std::string temp;
	std::unordered_map<std::string, int>::iterator it;
	for (it = fr_caractere.begin(); it != fr_caractere.end(); it++)
	{
		Node* nod_nou = new Node;
		nod_nou->valoare = it->second;
		nod_nou->caractere = it->first;
		nod_nou->left = nullptr;
		nod_nou->right = nullptr;
		coada_de_prioritati.push(nod_nou);
	}

	Node* nod1;
	Node* nod2;
	while (coada_de_prioritati.size() != 1)
	{
		nod1 = coada_de_prioritati.top();
		coada_de_prioritati.pop();
		nod2 = coada_de_prioritati.top();
		coada_de_prioritati.pop();
		coada_de_prioritati.push(combine_doua_noduri_intr_unul(nod1, nod2));
	}
}

void afisare_codificare_Huffman(std::priority_queue<Node*, std::vector<Node*>, comparator>coada_de_prioritati)
{
	std::queue<std::pair<Node*, std::string>>coada;
	std::string codificare;
	Node* parinte=coada_de_prioritati.top();
	coada_de_prioritati.pop();
	coada.push(std::make_pair(parinte, ""));
	while (coada.size()!=0)
	{
		parinte = coada.front().first;
		codificare = coada.front().second;
		coada.pop();
		//std::cout << "Caracterul " << parinte->caractere << " are codificarea " << codificare << std::endl;
		if (parinte->caractere.size() == 1)
		{
			std::cout << "Caracterul " << parinte->caractere << " are codificarea " << codificare << std::endl;
		}
		if (parinte->left != nullptr)
		{
			coada.push(std::make_pair(parinte->left, codificare + "0"));
		}
		if (parinte->right != nullptr)
		{
			coada.push(std::make_pair(parinte->right, codificare + "1"));
		}
	}
}

int main()
{
	std::string propozitie;
	std::unordered_map<std::string, int>fr_caractere;
	std::priority_queue<Node*, std::vector<Node*>, comparator>coada_de_prioritati;

	citire_propozitie(propozitie);
	determinare_frecventa_caractere(propozitie, fr_caractere);
	construire_arbore_Huffman(fr_caractere, coada_de_prioritati);
	afisare_codificare_Huffman(coada_de_prioritati);

	return 0;
}


