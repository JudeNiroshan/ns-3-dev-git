#pragma once
#include "TrustTable.h"
#include "TrustTableEntry.h"

namespace ns3
{
namespace trust
{

class IndTrustCal
{
private:
	TrustTable* trustTable;
public:
	IndTrustCal();
	double* sendTRR(TrustTableEntry node, TrustTableEntry targetNode,  RecommendationTable recommendationTable);
	double calculateWeight(TrustTableEntry node, TrustTableEntry targetNode);
	double calculateRNew(TrustTableEntry node ,TrustTableEntry targetNode);
	double* getDTGT(TrustTableEntry node, TrustTableEntry targetNode, RecommendationTable recommendationTable);
	double calculateMaturityLevel(TrustTableEntry node);
	void setTrustTable(TrustTable* trustTable);
	double calculateIndirectTrust(TrustTableEntry targetNode, RecommendationTable recommendationTable);
	~IndTrustCal();
};

}
}

