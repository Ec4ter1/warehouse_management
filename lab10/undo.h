#pragma once
#include "produs.h"
#include "repo.h"

class Undo {
public:
	virtual void doUndo() = 0;
	virtual ~Undo() = default;
};

class UndoAdd : public Undo {
	Prod p;
	repo_abs& rep;
public:
	UndoAdd(repo_abs& rep, const Prod& p) :rep{ rep }, p{ p } {}

	void doUndo() override{
		rep.del(p);
	}

};

class UndoDel : public Undo {
	Prod p;
	repo_abs& rep;
public:
	UndoDel(repo_abs& rep, const Prod& p) :rep{ rep }, p{ p } {}

	void doUndo() override{
		rep.store(p);
	}

};

class UndoModif : public Undo {
	Prod p;
	Prod p2;
	repo_abs& rep;
public:
	UndoModif(repo_abs& rep, const Prod& p) :rep{ rep }, p{ p } {}

	void doUndo() override {
		rep.modif(p.get_nume(), p.get_tip(), p.get_produc(), p.get_pret());
	}

};