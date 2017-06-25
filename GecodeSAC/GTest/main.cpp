#include <iostream>
#include <string>
#include "XMLBuilder.h"
#include "BuildGecodeModel.h"
using namespace std;
using namespace cp;
using namespace cp::model;
using namespace cp::parse;

const string X_PATH = "BMPath.xml";

int main()
{
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
	branch(*gm, gm->vars_, INT_VAR_AFC_SIZE_MAX(0), INT_VAL_MIN());
	//branch(*gm, gm->vars_, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
	//branch(*gm, gm->vars_, INT_VAR_DEGREE_SIZE_MIN(), INT_VAL_MIN());

	DFS<GecodeModel> ee(gm);
	delete gm;
	int i = 0;
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
	//cout << "|solutions| = " << i << endl;
	cout << "---end---" << endl;
	return 0;
}
