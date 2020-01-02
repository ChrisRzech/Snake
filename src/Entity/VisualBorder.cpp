#include "VisualBorder.hpp"

namespace Entity
{
VisualBorder::VisualBorder(const sf::Vector2u& size, unsigned int borderWidth, const sf::Color& color)
    : m_borderWidth(borderWidth)
{
    setSize(size);
    setColor(color);
}

sf::Vector2u VisualBorder::getSize() const
{
    return sf::Vector2u(m_borders[0].getSize().x, m_borders[2].getSize().y);
}

unsigned int VisualBorder::getBorderWidth() const
{
    return m_borders[0].getSize().y;
}

sf::Color VisualBorder::getColor() const
{
    return m_borders[0].getFillColor();
}

void VisualBorder::setSize(const sf::Vector2u& size)
{
    m_borders[0].setSize(sf::Vector2f(size.x, m_borderWidth)); //Top
    m_borders[1].setSize(sf::Vector2f(size.x, m_borderWidth)); //Bottom
    m_borders[2].setSize(sf::Vector2f(m_borderWidth, size.y)); //Left
    m_borders[3].setSize(sf::Vector2f(m_borderWidth, size.y)); //Right
    
    /*
     * NOTE:
     * Top and left borders are initialized to (0,0)
     */
    m_borders[1].setPosition(0, size.y - m_borderWidth);
    m_borders[3].setPosition(size.x - m_borderWidth, 0);
}

void VisualBorder::setBorderWidth(unsigned int width)
{
    m_borderWidth = width;
    
    //Updating size will update border width
    setSize(getSize());
}

void VisualBorder::setColor(const sf::Color& a)
{
    for(sf::RectangleShape& border : m_borders)
        border.setFillColor(a);
}

void VisualBorder::draw(sf::RenderWindow& w) const
{
    for(const sf::RectangleShape& border : m_borders)
        w.draw(border);
}
}
