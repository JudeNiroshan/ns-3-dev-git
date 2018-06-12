#include "TrustLevelClassifier.h"
#include "RecommendationTableEntry.h"
#include "IndTrustCal.h"
#include "TrustTableEntry.h"
#include "DirTrustCal.h"
#include "Spiral.h"
#include <vector>
#include <iostream>

namespace ns3
{
namespace trust
{

TrustLevelClassifier::TrustLevelClassifier()
{
}


void TrustLevelClassifier::identifyTrustLevel(TrustTable* trustTable)
{
	double Threshold_trust = 0.5;
	double Threshold_trustWorthy = 0.8;
	double Threshold_selfish = 0.3;

	std::vector<TrustTableEntry>& node_entry_vector = trustTable->getTrustTableEntries();
	double node_GT;

	for (std::vector<TrustTableEntry>::iterator it = node_entry_vector.begin(); it != node_entry_vector.end(); it++) {
		node_GT = it->getGlobalTrust();

		if (node_GT > Threshold_trust)
		{
			if (node_GT > Threshold_trustWorthy)
			{
				it->setTrustLevel(1);
			}
			else
			{
				it->setTrustLevel(2);
			}
		}
		else
		{
			if (node_GT > Threshold_selfish)
			{
				it->setTrustLevel(3);

				//reduce trust here
			}
			else
			{
				//call spiral model method
				it->setTrustLevel(-1);
				Spiral model;
//				double *past_global_trust_range;
//				past_global_trust_range = model.getMinMaxTrust(trustTable);
//				std::cout << "Max GT:- " << past_global_trust_range[1] << std::endl;
//				model.addMaliciousCategory(past_global_trust_range, trustTable);
			}
		}


	}
}


double TrustLevelClassifier::calculateReductionFactor(int interactions, double globalTrust)
{
	double reductionFactor;
	reductionFactor = globalTrust / interactions;

	return reductionFactor;
}


double TrustLevelClassifier::recalculateIndirectTrust(double indirectTrust, double reductionFactor)
{
	indirectTrust = indirectTrust - reductionFactor;
	//update global trust
	return indirectTrust;
}

TrustLevelClassifier::~TrustLevelClassifier()
{
}

}
}
