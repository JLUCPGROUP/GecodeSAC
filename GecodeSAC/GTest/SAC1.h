/*
 * SAC1.h
 *
 *  Created on: 2016年11月17日
 *      Author: leezear
 */
#include "GecodeModel.h"
#include <time.h>
#ifndef SAC1_H_
#define SAC1_H_
using namespace Gecode;

namespace cp {
namespace algorithm {

class SAC_1 {
public:
	GecodeModel* model;
	SAC_1(GecodeModel* model);
	bool enforce();
	virtual ~SAC_1();
};

} /* namespace algorithm */
} /* namespace cudacsp */

#endif /* SAC1_H_ */
