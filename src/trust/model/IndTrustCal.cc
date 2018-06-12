
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
double* IndTrustCal::sendTRR(TrustTableEntry node, TrustTableEntry targetNode, RecommendationTable recommendationTable) {
	//TODO : Need to send a packet to targetNode to get the DT and GT
	static double rec[2];
	rec[0] = 0.5;
	rec[1] = 0.6;

	std::vector<RecommendationTableEntry> node_entry_list = recommendationTable.getRecommendedNodeEntries(node.getDestinationNode());

	for (std::vector<TrustTableEntry>::iterator it = node_entry_list.begin();it != node_entry_list.end(); it++) {
		if (it->getDestinationNode() != targetNode.getDestinationNode()) {
			//to be completed

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
double IndTrustCal::calculateWeight(TrustTableEntry node, TrustTableEntry targetNode) {

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
double IndTrustCal::calculateRNew(TrustTableEntry node, TrustTableEntry targetNode) {

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
double* IndTrustCal::getDTGT(TrustTableEntry node, TrustTableEntry targetNode, RecommendationTable recommendationTable)) {

	double* rec;
	rec = sendTRR(node, targetNode, recommendationTable);

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
double IndTrustCal::calculateIndirectTrust(TrustTableEntry targetNode, RecommendationTable recommendationTable) {

	std::vector<TrustTableEntry> node_entry_list = this->trustTable->getTrustTableEntries();
	double w_sum = 0;

	for (std::vector<TrustTableEntry>::iterator it = node_entry_list.begin();it != node_entry_list.end(); it++) {
		if (it->getDestinationNode() != targetNode.getDestinationNode()) {
			double w = calculateWeight(*it, targetNode);
			double r_new_nei_node = calculateRNew(*it, targetNode);
			double *rec;
			rec = getDTGT(*it, targetNode, recommendationTable);
			double cal_w_term = w * (r_new_nei_node * rec[1]);
			w_sum = w_sum + cal_w_term;
		}
	}
	return w_sum;
}

IndTrustCal::~IndTrustCal() {
}

}
}

