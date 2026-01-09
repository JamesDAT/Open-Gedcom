# Reader

## Encoding
Gedcom allows for many different encodings, the reader must detect the encoding and internally convert to utf-8. The reader contains an interface stream, which at runtime is decided depending on the encoding. The interface demands certain read functions, and will always return a utf-8 string, how the stream manages this is up to implementation.

## Multithreading
When the reader is commanded to start reading it will spawn a new thread. It will decide on the encoding and change its source reader. It then reads chunks as fast as it can and stores them in a line queue, this queue can be accessed through a function. Using the function to get the next line is thread safe.