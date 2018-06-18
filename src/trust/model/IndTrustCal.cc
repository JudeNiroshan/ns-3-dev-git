
#include "IndTrustCal.h"
#include "TrustTableEntry.h"
#include "DirTrustCal.h"
#include "NodeEntry.h"
#include "TestValueGenerator.h"
#include "TrustLevelClassifier.h"
#include "trust-routing-protocol.h"
#include "ns3/log.h"
#include <iostream>

namespace ns3 {
namespace trust {

/**
 * Method:    main
 * Returns:   0
 * Parameter:
 */
/*
 int main()
 {
 TrustTable* dirTrustTable = TestValueGenerator::getDummyDirTrustTable();
 dirTrustTable->printTable();

 //identifyTrustLevel();
 std::cout << "--After calculating direct trust--" << std::endl;

 std::cout << "-----------------------------------" << std::endl;

 TrustTable* trustTable = TestValueGenerator::getDummyTrustTable();
 trustTable->printTable();

 IndTrustCal indTrustCal;
 indTrustCal.setTrustTable(trustTable);
 std::vector<TrustTableEntry>& node_entry_vector = trustTable->getTrustTableEntries();

 for (std::vector<TrustTableEntry>::iterator it = node_entry_vector.begin(); it != node_entry_vector.end(); it++) {

 double ind_trust_value = indTrustCal.calculateIndirectTrust(*it);
 it->updateIndirectTrust(ind_trust_value);
 it->calculateGlobalTrust();
 //TODO: inside above calculateGlobalTrust() need to update backupTable.

 }
 std::cout << "After the calculation process..." << std::endl;
 trustTable->printTable();

 BackupTable* backupTable = TestValueGenerator::getDummyBackupTableByTrustTable(trustTable);
 backupTable->printTable();


 RecommendationTable* recomendationTable = TestValueGenerator::getDummyRecommendationTableByTrustTable(trustTable);

 std::cout << "Recommendation Table After adding values..." << std::endl;
 recomendationTable->printTable();

 TrustLevelClassifier classifier;
 classifier.identifyTrustLevel(trustTable);

 int pause;
 std::cin >> pause;

 return 0;
 }
 */

IndTrustCal::IndTrustCal() {
}

/**
 * Method:    sendTRR
 * Returns:   rec
 * Parameter: node, targetNode
 */
double*
IndTrustCal::sendTRR (TrustTableEntry node, TrustTableEntry targetNode) {
	static double rec[2];
	rec[0] = 0.5;
	rec[1] = 0.6;

    if (this->trrRecFlag == 2)
	  {
		  for (std::vector<TRRTableEntry>::iterator it = this->trrTable->getTrrTableEntries().begin(); it != this->trrTable->getTrrTableEntries().end(); it++)
		    {
			  if(it->GetDestinationNodeId() == node.getDestinationNode() && it->getTargetNodeId() == targetNode.getDestinationNode())
			    {
				  rec[0] = it->getDirectTrust();
				  rec[1] = it->getGlobalTrust();
			    }
		    }
	  }
	return rec;
}

/**
 * Method:    setTrustTable
 * Returns:
 * Parameter: trustTable
 */
void IndTrustCal::setTrustTable(TrustTable* trustTable) {
	this->trustTable = trustTable;
}

/**
 * Method:    calculateWeight
 * Returns:   weight
 * Parameter: node, targetNode
 */
double IndTrustCal::calculateWeight(TrustTableEntry node,
		TrustTableEntry targetNode) {
	double r_new_nei_node = calculateRNew(node, targetNode);
	double r_new_all = 0;
	std::vector<TrustTableEntry> node_entry_list =
			this->trustTable->getTrustTableEntries();
	for (std::vector<TrustTableEntry>::iterator it = node_entry_list.begin();
			it != node_entry_list.end(); it++) {
		if (it->getDestinationNode() != targetNode.getDestinationNode()) {
			double r_new_node = calculateRNew(*it, targetNode);
			r_new_all = r_new_all + r_new_node;
		}
	}
	return r_new_nei_node / r_new_all;
}

/**
 * Method:    calculateRNew
 * Returns:   new Recommendation
 * Parameter: node, targetNode
 */
double IndTrustCal::calculateRNew(TrustTableEntry node,
		TrustTableEntry targetNode) {
	double mlevel = calculateMaturityLevel(node);
	double* rec;
	rec = getDTGT(node, targetNode);

	return mlevel * rec[0];
}

/**
 * Method:    getDTGT
 * Returns:   rec
 * Parameter: node, targetNode
 */
double* IndTrustCal::getDTGT(TrustTableEntry node, TrustTableEntry targetNode) {
	double* rec;
	rec = sendTRR(node, targetNode);

	return rec;
}

/**
 * Method:    calculateMaturityLevel
 * Returns:   maturity level
 * Parameter: node
 */
double IndTrustCal::calculateMaturityLevel(TrustTableEntry node) {
	int i_p_node = node.getInteractionCount();
	std::vector<TrustTableEntry> node_entry_list =
			this->trustTable->getTrustTableEntries();
	double i_all = 0;
	for (std::vector<TrustTableEntry>::iterator it = node_entry_list.begin();
			it != node_entry_list.end(); it++) {
		i_all = i_all + it->getInteractionCount();
	}

	return i_p_node / i_all;
}

/**
 * Method:    calculateIndirectTrust
 * Returns:   w_sum
 * Parameter: targetNode
 */
double
IndTrustCal::calculateIndirectTrust (TrustTableEntry targetNode) {
	std::vector<TrustTableEntry> node_entry_list =
			this->trustTable->getTrustTableEntries();
	double w_sum = 0;
	for (std::vector<TrustTableEntry>::iterator it = node_entry_list.begin();
			it != node_entry_list.end(); it++) {
		if (it->getDestinationNode() != targetNode.getDestinationNode()) {
			double w = calculateWeight(*it, targetNode);
			double r_new_nei_node = calculateRNew(*it, targetNode);
			double *rec;
			rec = getDTGT(*it, targetNode);
			double cal_w_term = w * (r_new_nei_node * rec[1]);
			w_sum = w_sum + cal_w_term;
		}
	}
	double value = round ( w_sum * 100000.0 ) / 100000.0;
	return value;
}

void
IndTrustCal::SetTrrRecFlag (uint trrRecFlag)
{
	this->trrRecFlag = trrRecFlag;
}

void
IndTrustCal::SetTrrTable (TRRTable* trrTable)
{
	this->trrTable = trrTable;
}

IndTrustCal::~IndTrustCal() {
}

}
}

