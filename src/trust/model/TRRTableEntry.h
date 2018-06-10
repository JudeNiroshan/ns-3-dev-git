#pragma once
#include <string>
#include <vector>
#include <list>
#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"


namespace ns3
{
namespace trust
{


class TRRTableEntry
{

private:

	Ipv4Address targetNodeId;
	Ipv4Address senderNodeId;
	double directTrust;
	double globalTrust;
	Time sentTime;
	Time receivedTime;

public:
	Ipv4Address getTargetNodeId();
	void setTargetNodeId(Ipv4Address neighborNodeId);
	Ipv4Address getSenderNodeId();
	void setSenderNodeId(Ipv4Address neighborNodeId);
	double getDirectTrust();
	void setDirectTrust(double DT);
	double getGlobalTrust();
	void setGlobalTrust(double DT);
	Time getSentTime();
	void setSentTime(Time sentTime);
	Time getReceivedTime();
	void setReceivedTime(Time receivedTime);
	TRRTableEntry();
	~TRRTableEntry();
};

}
}
