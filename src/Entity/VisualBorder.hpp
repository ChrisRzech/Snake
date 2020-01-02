#pragma once
#include <array>
#include <SFML/Graphics.hpp>

namespace Entity
{
class VisualBorder
{
public:
    /* Constructors */
    VisualBorder(const sf::Vector2u& size, unsigned int borderWidth, const sf::Color&);
    
    /* Getters */
    sf::Vector2u getSize() const;
    unsigned int getBorderWidth() const;
    sf::Color getColor() const;
    
    /* Setters */
    void setSize(const sf::Vector2u&);
    void setBorderWidth(unsigned int);
    void setColor(const sf::Color&);
    
    /* Updates */
    void draw(sf::RenderWindow&) const;
    
private:
    unsigned int m_borderWidth;
    std::array<sf::RectangleShape,4> m_borders;
};
}
