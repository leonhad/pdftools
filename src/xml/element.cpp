#include "element.h"

using namespace std;

Element::Element(string element) noexcept : XmlTag{element}
{
}

Element::~Element() noexcept
{
}

std::string Element::to_XML() const noexcept
{
    return m_name;
}
