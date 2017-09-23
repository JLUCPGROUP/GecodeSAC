/*
 * BuildGecodeModel.h
 *
 *  Created on: 2016年9月17日
 *      Author: leezear
 */

#ifndef BUILDGECODEMODEL_H_
#define BUILDGECODEMODEL_H_

#include "model/HModel.h"
#include "GecodeModel.h"
using namespace cudacp;
using namespace Gecode;
//
////************************************
//// Method:    IsEqual
//// FullName:  IsEqual
//// Access:    public 
//// Returns:   bool
//// Qualifier: 判断元组是否相等
//// Parameter: const int * lh
//// Parameter: const int * rh
//// Parameter: const int & len	元组长度
////************************************
//inline bool IsEqual(const int* lh, const int* rh, const int& len) {
//	for (int i = 0; i < len; ++i)
//		if (lh[i] != rh[i])
//			return false;
//
//	return true;
//}
//
////************************************
//// Method:    GetIntTuple
//// FullName:  GetIntTuple
//// Access:    public 
//// Returns:   void
//// Qualifier: 从序号获得约束元组
//// Parameter: int idx	序号
//// Parameter: int * t	元组	
//// Parameter: const XMLDomain * * ds	scope(c)
////************************************
//inline void GetIntTuple(int idx, int *t, const int& len, XDom **ds) {
//	for (int i = (len - 1); i >= 0; --i) {
//		t[i] = ds[i]->values[(idx % (ds[i]->size))];
//		idx /= (ds[i]->size);
//	}
//}

void BuildGecodeModel(const  HModel* h_model, GecodeModel* g_model) {
	//if (h_model->property.vs_size == 1) {
	//	*d = &xmodel->doms[0];
	//	//		g_model->vars_ = IntVarArray(*g_model, xmodel->vs_size, d.values[0], d.values[d.size - 1]);
	//	g_model->vars_ = IntVarArray(*g_model, xmodel->vs_size, d->values[0], d->values[d->size - 1]);
	//}
	//else if (xmodel->ds_size != 1 && xmodel->vs_size != 1) {
	//	g_model->vars_ = IntVarArray(*g_model, xmodel->vs_size);

	//	for (int i = 0; i < xmodel->vs_size; ++i) {
	//		XMLVariable* v = &xmodel->variables[i];
	//		g_model->vars_[i] = IntVar(*g_model, IntSet(xmodel->domains[v->dm_id].values, xmodel->domains[v->dm_id].size));
	//		cout << i << ":" << g_model->vars_[i].size() << endl;
	//	}
	//}

	g_model->vars_ = IntVarArray(*g_model, h_model->property.vs_size);

	for (size_t i = 0; i < h_model->property.vs_size; ++i) {
		HVar* v = h_model->vars[i];
		g_model->vars_[i] = IntVar(*g_model, IntSet(h_model->vars[i]->vals, h_model->vars[i]->size));
	}

	for (size_t i = 0; i < h_model->property.ts_size; ++i) {
		HTab* tab = h_model->tabs[i];
		TupleSet ts;

		for (size_t j = 0; j < tab->size; ++j)
			ts.add(IntArgs(tab->arity, tab->tuples[j]));
		ts.finalize();

		IntVarArgs scope;
		for (int j = 0; j < tab->arity; ++j) 
			scope << g_model->vars_[tab->scope[j]];

		extensional(*g_model, scope, ts);
	}

	//if (xmodel->features.rel_type == REL_TABULAR) {
	//	int* tpl = new int[xmodel->features.arity];
	//	XMLDomain** ds = new XMLDomain*[xmodel->features.arity];
	//	int num_tuples;

	//	for (int i = 0; i < xmodel->cs_size; ++i) {
	//		int k = 0;
	//		XMLConstraint *c = &xmodel->constraints[i];
	//		TupleSet ts;
	//		XMLRelation* r = &xmodel->relations[c->re_id];
	//		XMLVariable* v;
	//		XMLDomain* d;

	//		if (r->semantices == SEM_SUPPORT) {
	//			for (int j = 0; j < r->size; ++j)
	//				ts.add(IntArgs(c->arity, r->tuples[j]));

	//			ts.finalize();
	//		}
	//		else {
	//			num_tuples = 1;

	//			for (int j = 0; j < r->arity; ++j) {
	//				v = &xmodel->variables[j];
	//				d = &xmodel->domains[v->dm_id];
	//				ds[j] = d;
	//				num_tuples *= d->size;
	//			}

	//			for (int j = 0; j < num_tuples; ++j) {
	//				GetIntTuple(j, tpl, r->arity, ds);

	//				//支持
	//				if (k < r->size) {
	//					if (!IsEqual(r->tuples[k], tpl, r->arity)) {
	//						ts.add(IntArgs(c->arity, tpl));
	//					}
	//					else
	//						++k;
	//				}
	//				else
	//					ts.add(IntArgs(c->arity, tpl));
	//			}

	//			ts.finalize();
	//		}

	//		IntVarArgs scope;

	//		for (int j = 0; j < c->arity; ++j) {
	//			scope << g_model->vars_[c->scope[j]];
	//		}
	//		//IntVarArray s;
	//		extensional(*g_model, scope, ts);
	//	}

	//	delete[] tpl;
	//	delete[] ds;

	//	tpl = NULL;
	//	ds = NULL;
	//}
	//else {
	//}
}

#endif /* BUILDGECODEMODEL_H_ */
