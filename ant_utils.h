#pragma once

// -getantepochcontext : print the public epoch context.
void printAntEpochContext(const char* nodeIp, int nodePort);

// -getanttree <identity> : page and print one identity's tree. Operator-signed with 'seed'.
void printAntIdentityTree(const char* nodeIp, int nodePort, const char* identity, const char* seed);
