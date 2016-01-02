#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <stdexcept>

class Document;
class RootNode;

class Converter {
private:
    const std::string m_filein;
    const std::string m_format;
    std::string m_fileout;
    Document *m_document = nullptr;
    
public:
    Converter(const std::string& filein, const std::string& fileout, const std::string& format) noexcept;
    ~Converter() noexcept;
    
    void convert() throw(std::exception);
};

#endif
