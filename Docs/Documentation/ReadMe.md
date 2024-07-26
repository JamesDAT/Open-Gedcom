# Documentation
## Compatibility
Open Gedcom uses c++23 and is originally built in Visual Studio using MSVC. Open Gedcom should be kept crossplatform, and should allow for easy migration to other compilers and build systems.

## Modules
Open Gedcom exclusively uses modules and should only ever `#include` if strictly necessary macros need to be imported. 

## API Interface
All of Open Gedcom is exposed through the OpenGedcom module. Every interaction between user code and Open Gedcom should be achieved through Open Gedcom. The Open Gedcom module partitions are technically available if someone would need to access the internal systems.