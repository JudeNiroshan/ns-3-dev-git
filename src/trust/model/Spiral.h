#pragma once
#include "TrustTable.h"

namespace ns3
{
namespace trust
{
class Spiral
{
public:
	Spiral();
	void addMaliciousCategory(double* past_global_trust_range, TrustTable* trustTable);
	double* getMinMaxTrust(TrustTable* trustTable);
	~Spiral();
};
}
}

