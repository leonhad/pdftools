#include "element.h"
#include <sstream>

using namespace std;

Element::Element(string element) noexcept : XmlTag{element}
{
}

Element::~Element() noexcept
{
}

std::string Element::to_XML() const noexcept
{
    stringstream buffer;
    for (char c : m_name) {
        switch(c) {
        case '&':
            buffer << "&amp;";
            break;
        case '<':
            buffer << "&lt;";
            break;
        case '>':
            buffer << "&gt;";
            break;
        default:
            buffer << c;
        }
    }
    return buffer.str();
}
