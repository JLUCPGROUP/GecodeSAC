#include <iostream>
#include <string>
#include "XMLBuilder.h"

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

	return 0;
}
