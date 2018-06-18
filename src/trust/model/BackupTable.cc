#include "BackupTable.h"
#include <iostream>

namespace ns3
{
namespace trust
{


BackupTable::BackupTable()
{
	columnSeperator = " | ";
}


void BackupTable::addBackupTableEntry(BackupTableEntry entry)
{
	backupTableRecords.push_back(entry);
}

std::vector<BackupTableEntry>& BackupTable::getBackupTableEntries()
{
	return backupTableRecords;
}

void
BackupTable::printTable()
{
	std::cout << ">>>>>>>>>>>>>> Backup Table <<<<<<<<<<<<<<<" << std::endl;
	std::cout << "| " << "Node" << columnSeperator << "Trust Value" << columnSeperator << "Time Duration" << columnSeperator << "Analyzed Result" << std::endl;
//	int index = backupTableRecords.size()-1;
	for (std::vector<BackupTableEntry>::iterator it = backupTableRecords.begin(); it != backupTableRecords.end(); it++)
	{
		/*if (index)
		  {
			std::cout << "| " << backupTableRecords.at(index).getNeiNode() << columnSeperator << backupTableRecords.at(index).getTrustValue() << "\t" << columnSeperator << backupTableRecords.at(index).GetTimeDuration() << "\t\t" << columnSeperator << backupTableRecords.at(index).GetResult() << std::endl;

			index--;
		  }*/
		std::cout << "| " << it->getNeiNode() << columnSeperator << it->getTrustValue() << "\t" << columnSeperator << it->GetTimeDuration () << "\t\t" << columnSeperator << it->GetResult () << std::endl;
	}
}

void BackupTable::addToTrustList(double trustValue)
{
	this->trustList.push_back(trustValue);
}

std::vector<double>& BackupTable::getTrustList()
{
	return this->trustList;
}


BackupTable::~BackupTable()
{
}

}
}
