

Trust-based routing protocols framework
---------------------------------------

This module defines the trust-based routing protocols framework which can be used 
to transform an existing routing protocol into a trust based variation.

This module was written by Jude Niroshan from Sri Lanka Institute of Information 
Technology(SLIIT). It has been developed in Google Summer of Code 2018 under the 
mentorship of Tommaso Pecorella from Università di Firenze.

Model Description
*****************

The source code for the new module lives in the directory ``src/trust-routing``.

All the generic classes of trust framework is defined here.

Design
======

Class ``ns3::trust-routing::TrustManager`` serves as the base class for the trust 
framework. This acts as an abstract class which includes a virtual method called 
``CalculateTrust``. This method must be implemented by the extended child class. 
It allows the trust calculation algorithmn decoupled from the trust framework. 

Trust based protocols are operating with trust value. This can be sometimes 
considered as a routing parameter. Therefore, most of the trust based protocols 
are using a trust table which holds trust values for each node in the network. 
Therefore, trust framework has provided a table ``ns3::trust-routing::TrustTable``.
 This includes address, trust value and the timestamp of when the value has been 
 added to the trust table. 

Class ``ns3::trust-routing::TrustTable`` has a ``std::map`` of 
``ns3::trust-routing::TrustEntry`` objects against the ``ns3::Address``. 
There is only one trust entry instance per given address in the trust 
table. By default, trust table only consists of directly connected nodes.

Users of this framework must provide an implementation for 
``ns3::trust-routing::TrustManager``. As TrustManager has extended from 
``ns3::Application``, this can be instantiated and installed to each node of the 
network as an application.

Implementations for ``ns3::trust-routing::TrustManager`` have the flexibility over
what kind of packets should be considered and how the metrics can be manipulated when 
calculating the trust value. It is recommended to use a promiscuous callback function 
hooked into net-device interfaces of the nodes. This way collected and processed 
information merged into a single metric called trust value. It can be stored in the 
trust table for future decision making.

Scope and Limitations
=====================

The framework is for IPv4 only. Trust tables are resides for each node in the network.
It can defines a trust value based on directly connected node's communication. It can
print the trust table values to a given output stream and check for the trust entries.

The following features are not yet implemented:

#. Remove trust table entries when a route is removed or invalidated from the 
   trust table
#. Trust value range definition [0, 1]
#. Threshold value for trust value should be used to decide whether a node is 
   malicious or healthy

References
==========

Add academic citations here, such as if you published a paper on this
model, or if readers should read a particular specification or other work.

Usage
*****

This section is principally concerned with the usage of your model, using
the public API.  Focus first on most common usage patterns, then go
into more advanced topics.

Building New Module
===================

Include this subsection only if there are special build instructions or
platform limitations.

Helpers
=======

What helper API will users typically use?  Describe it here.

Attributes
==========

What classes hold attributes, and what are the key ones worth mentioning?

Output
======

What kind of data does the model generate?  What are the key trace
sources?   What kind of logging output can be enabled?

Advanced Usage
==============

Go into further details (such as using the API outside of the helpers)
in additional sections, as needed.

Examples
========

What examples using this new code are available?  Describe them here.

Troubleshooting
===============

Add any tips for avoiding pitfalls, etc.

Validation
**********

Describe how the model has been tested/validated.  What tests run in the
test suite?  How much API and code is covered by the tests?  Again, 
references to outside published work may help here.
