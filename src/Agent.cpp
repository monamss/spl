#include "../include/Agent.h"
using namespace std;

Agent * ContactTracer::clone() {
    return new ContactTracer(*this);
}

Agent * Virus::clone() {
    return new Virus(*this);
}