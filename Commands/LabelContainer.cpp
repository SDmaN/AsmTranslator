#include "LabelContainer.h"

bool LabelContainer::contains(const std::string &label) const
{
    auto it = m_container.find(label);
    return it != std::end(m_container);
}

void LabelContainer::add(const std::pair<std::string, Address> &element)
{
    m_container.insert(element);
}

Address LabelContainer::address(const std::string &label) const
{
    return m_container[label];
}

void LabelContainer::clear()
{
    m_container.clear();
}