#include "pch.h"
#include "gedcom.h"

using namespace gedcom;

GedcomObject::GedcomObject() 
	: _Individuals(new std::vector<Individual>{})
{

}
GedcomObject::~GedcomObject() {
	delete _Individuals;
}
