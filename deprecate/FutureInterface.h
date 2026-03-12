// this file shows the future api of the parsing system. It allows for different styles of ownership and memory usage
#include <string>
#include <span>
#include <memory>

struct Document {

};

// DOM, standard model, takes ownership of a string containing the contents of the file,
// tags store string_views into this string, zero copy, extremely fast, but has high memory usage

struct DOMStorage {
    std::string data;
};

inline Document ParseDOM(std::string&& data) {
    DOMStorage m_storage; // example
    m_storage.data = std::move(data);

    return {};
}


// Copying/owned DOM, does not take ownership of the file contents, instead the user must ensure that the
// data string lasts for as long as parsing. This model is slower for parsing, as it makes many copies.
// will spike memory usage during parse operation, but overall will have a much lower memory footprint
// once finished

inline Document ParseCopy(const std::string_view data) {
    std::string tag = std::string(data.data() + 0, 10); // creates copies from parts of the data

    return {};
}

// Streaming parser. Takes a special IReader which just defines functions. The implementation is up to the user,
// the parser will take the streamer and read on demand, this option also allows for lazy loading

struct IReader {
    std::span<const char> GetChunk() { return {}; }
};

inline Document ParseStream(std::shared_ptr<IReader> reader, bool lazyLoad = false) {
    auto chunk = reader->GetChunk();
    
    if(lazyLoad) {
        std::size_t index; // computed from line offset
        std::size_t size; // computed from line
    }
    else {
        std::string data = std::string(chunk.subspan(0, 10).data()); // copy
    }
    
    return {};
}