# Reader

## Encoding
Gedcom allows for many different encodings, the reader must detect the encoding and internally convert to utf-8. The reader contains an interface stream, which at runtime is decided depending on the encoding. The interface demands certain read functions, and will always return a utf-8 string, how the stream manages this is up to implementation.