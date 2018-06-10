//#include "stdafx.h"
#include "TRRTableEntry.h"
#include <string>

namespace ns3
{
namespace trust
{

TRRTableEntry::TRRTableEntry()
{
}

Ipv4Address TRRTableEntry::getTargetNodeId()
{
	return this->targetNodeId;
}

void TRRTableEntry::setTargetNodeId(Ipv4Address targetNodeId)
{
	this->targetNodeId = targetNodeId;
}

Ipv4Address TRRTableEntry::getSenderNodeId()
{
	return this->senderNodeId;
}

void TRRTableEntry::setSenderNodeId(Ipv4Address senderNodeId)
{
	this->senderNodeId = senderNodeId;
}

double TRRTableEntry::getDirectTrust()
{
	return directTrust;
}
void TRRTableEntry::setDirectTrust(double directTrust)
{
	this->directTrust = directTrust;
}

double TRRTableEntry::getGlobalTrust()
{
	return globalTrust;
}
void TRRTableEntry::setGlobalTrust(double globalTrust)
{
	this->globalTrust = globalTrust;
}

Time TRRTableEntry::getSentTime()
{
	return sentTime;
}

void TRRTableEntry::setSentTime(Time sentTime)
{
	this->sentTime = sentTime;
}

Time TRRTableEntry::getReceivedTime()
{
	return receivedTime;
}

void TRRTableEntry::setReceivedTime(Time receivedTime)
{
	this->receivedTime = receivedTime;
}

TRRTableEntry::~TRRTableEntry()
{
}

}
}
