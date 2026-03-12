# OpenGedcom

## Document
The Document is the primary interaction point with OpenGedcom. It stores all the gedcom information and provides the api for interacting with the gedcom data.

## Parser-Document Relationship
The parser is detached from the Document through a GedcomStorage object. The parser sends the tags to the GedcomStorage object and eventually retuns it to the Document where it is stored and interacted with through the Document api.

## Parser-GedcomStorage Relationship
The parser has no knowledge about the internal representation of gedcom. It knows how gedcom tags are ordered, ```<level> <xref?> <tag> <value?>``` and it knows how to deal with missing elements. It builds out tags generically and passes it to the GedcomStorage. From here using the tag registry, proper tags are built out. 

## Parser-Reader Relationship
The reader provides a simple api to the Parser, that is for reading the file and consuming a line. As far as the Parser is concerned it tells the reader to start reading, then lines are consumed at the Parsers discretion. The internals of which are a lot more complicated, and are discussed in the Reader ReadMe.