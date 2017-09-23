#include <iostream>
#include <string>
#include <time.h>
#include "BuildGecodeModel.h"
#include "model/XBuilder.h"
#include "model/HBuilder.h"
#include "SAC1.h"
using namespace std;
using namespace cudacp;

const string X_PATH = "BMPath.xml";

int main() {
	clock_t  begin, end;
	XBuilder path_builder(X_PATH, XRT_BM_PATH);
	string bm_path = path_builder.GetBMFile();
	cout << bm_path << endl;
	XBuilder builder(bm_path, XRT_BM);
	XModel* xmodel = new XModel();
	builder.GenerateModelFromXml(xmodel);
	HModel* hmodel = new HModel();
	HBuilder hbuilder(xmodel, hmodel);
	GecodeModel* gm = new GecodeModel;
	BuildGecodeModel(hmodel, gm);

	//IntAFC afc(*gm, gm->vars_);
	branch(*gm, gm->vars_, INT_VAR_AFC_SIZE_MAX(0), INT_VAL_MIN());
	//branch(*gm, gm->vars_, INT_VAR_SIZE_MIN(), INT_VALUES_MIN());
	//branch(*gm, gm->vars_, INT_VAR_DEGREE_SIZE_MIN(), INT_VAL_MIN());

	DFS<GecodeModel> ee(gm);
	delete gm;
	//int i = 0;
	begin = clock();
	//while (GecodeModel* ss = ee.next()) {
	//	//ss->print();
	//	++i;
	//	delete ss;
	//}
	if (GecodeModel* ss = ee.next()) {
		ss->print();
		cout << "nodes = " << ee.statistics().node << endl;
		delete ss;
	}
	end = clock();
	//cout << "|solutions| = " << i << endl;

	//--------------------------------------------------------
	//SAC_1 sac1(gm);
	//begin = clock();
	//gm->status();
	//const Choice* ch = gm->choice();
	//unsigned int n = ch->alternatives();
	//ch->
	//std::cout << "n = " << n << std::endl;
	//sac1.enforce();
	//end = clock();
	//delete gm;

	delete hmodel;
	delete xmodel;
	cout << "execute time = " << end - begin << endl;
	cout << "---end---" << endl;
	return 0;
}
