# Debugging

## Exceptions and Asserts
Open Gedcom uses both exceptions and Asserts. 

### Exceptions
Exceptions are used in cases where Open Gedcom has encountered an issue that it cannot recover from, this can be situations such as an invalid or missing gedcom file. Functions with `noexcept` will not throw due to improper Open Gedcom usage, but does not guarantee that std library features won't throw.

### Asserts
Asserts are only used within debug builds and are used to note issues that may not be intended and that could cause issues, but do not immediately cause an unrecoverable state for Open Gedcom. Asserts can include situations such as adding an individual with an ID that already exists. Behaviour for these kinds of situations is defined, but may be unintended, so there will usually be a flag to denote that it was intended.