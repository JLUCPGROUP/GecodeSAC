#include <iostream>
#include <string>
#include "XMLBuilder.h"
#include "BuildGecodeModel.h"
#include <time.h>
#include "SAC1.h"
using namespace std;
using namespace cp;
using namespace cp::model;
using namespace cp::parse;
using namespace cp::algorithm;

const string X_PATH = "BMPath.xml";

int main()
{
	clock_t  begin, end;
	XMLBuilder path_builder(X_PATH, XRT_BM_PATH);
	string bm_path = path_builder.GetBMFile();
	cout << bm_path << endl;
	XMLBuilder builder(bm_path, XRT_BM);
	XMLModel* xml_model = new XMLModel();
	builder.GenerateModelFromXml(xml_model);
	GecodeModel* gm = new GecodeModel;
	BuildGecodeModel(xml_model, gm);
	DestroyEXTModel(xml_model);

	//IntAFC afc(*gm, gm->vars_);
	//branch(*gm, gm->vars_, INT_VAR_AFC_SIZE_MAX(0), INT_VAL_MIN());
	branch(*gm, gm->vars_, INT_VAR_SIZE_MIN(), INT_VALUES_MIN());
	//branch(*gm, gm->vars_, INT_VAR_DEGREE_SIZE_MIN(), INT_VAL_MIN());

	//DFS<GecodeModel> ee(gm);
	//delete gm;
	//int i = 0;
	//begin = clock();
	//while (GecodeModel* ss = ee.next()) {
	//	//ss->print();
	//	++i;
	//	delete ss;
	//}
	//end = clock();
	//if (GecodeModel* ss = ee.next()) {
	//	ss->print();
	//	cout << "nodes = " << ee.statistics().node << endl;
	//	delete ss;
	//}
	//cout << "|solutions| = " << i << endl;

	//--------------------------------------------------------
	SAC_1 sac1(gm);
	begin = clock();
	//gm->status();
	//const Choice* ch = gm->choice();
	//unsigned int n = ch->alternatives();
	//ch->
	//std::cout << "n = " << n << std::endl;
	sac1.enforce();
	end = clock();
	delete gm;

	cout << "execute time = " << end - begin << endl;
	cout << "---end---" << endl;
	return 0;
}
