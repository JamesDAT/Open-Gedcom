# Open-Gedcom
A library for managing gedcom files.

## Future Directions
As the core architecture of experimental is coming to an end, planning and revisions for a first version are beginning.

### Core Changes
**Lazy Loading**, although some lazy loading infrastructure was added, it was not part of the initial reader and parser implementation, meaning they did not have the capabilities to record data locations, and there is no backwards call to the reader to then retrieve that data when requested. A simple static pointer back to the reader implementation would fix this, but a proper modular reader system which has data indexing is required.

**Smarter Views**, The current view model is a very functional model, where all use cases have to be assumed and each view function his tailored to parse the data. This is extremely time consuming to implement, leads to greater chance of bugs, repeated code and becomes limiting on the user. Moving to an object oriented model would greatly improve the view api. For instance building out a list of events which the user can make use of is better than the current model which needs custom views and functions for every event type.

**Performance**, performance is difficult to gauge without the proper lazy loading, but now that the core registry system is in place, greater emphasis can be placed in optimizing the parser and reader. Although multithreading was briefly tried and dropped, simd optimization can be used heavily in the delimeter checking.

**Storage**, the storage went through an overhaul, removing polymorphism and flattening out records. The next step is to create separate storage for different record types, as storing them contiguously is not necessary and causes more issues (fragmentation etc.), separate storage also removes the record type checking step when iterating. It also allows for id based lookup, but this would need to be done with caution, it is unknown how well the ids were created in a gedcom file by other software, there could be collisions, or gaps. Also the implementation would have to protect against out of bounds lookups, but the main concern is reserving to the highest id number could use a lot more memory than needed if there are id gaps. Storage should also favour speed over memory in a few cases. Names are very commonly a way to search gedcom documents, so storing individuals names in memory in such a way they can be specifically searched and fuzzy searched is very important. Reducing memory usage is also important, so using a system that reduces name duplications is important.
