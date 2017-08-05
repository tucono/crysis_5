#include "Button.h"

Button::Button(sf::RenderWindow *nWindow, sf::Texture *nNonSelect, sf::Texture *nHover, sf::Texture *nSelect, sf::Font *nButtonFont, unsigned int nCharSize, std::string nButtonStr, float size[2], sf::Vector2f position) {
	window = nWindow;
	nonSelect = nNonSelect;
	hover = nHover;
	select = nSelect;
	buttonFont = nButtonFont;
	charSize = nCharSize;
	buttonStr = nButtonStr;
	setNonSelect();
	setButtonFont(buttonFont);
	setButtonText(buttonStr);
	setCharSize(charSize);
	buttonText.setFillColor(sf::Color::Yellow);
	buttonText.setOrigin(sf::Vector2f(buttonText.getGlobalBounds().width / 2, buttonText.getGlobalBounds().height / 2));//set origin in middle of text
	Sprite.setPosition(position);
	Sprite.setTexture(*nonSelect);
	Sprite.setScale(sf::Vector2f(size[0] / Sprite.getGlobalBounds().width, size[1] / Sprite.getGlobalBounds().height));//set the sprite to desired size
	buttonText.setPosition(sf::Vector2f(Sprite.getPosition().x+Sprite.getGlobalBounds().width / 2, Sprite.getPosition().y + Sprite.getGlobalBounds().height / 2));//set Text to appear at the position.
	xBound[0] = Sprite.getPosition().x;//left bound
	xBound[1] = Sprite.getPosition().x + Sprite.getGlobalBounds().width;//right bound
	yBound[0] = Sprite.getPosition().y;//set bottom bound
	yBound[1] = Sprite.getPosition().y + Sprite.getGlobalBounds().height;//set top bound
}
void Button::setButtonText(std::string nButtonStr) {
	buttonStr = nButtonStr;
	buttonText.setString(buttonStr);
}
void Button::setButtonFont(sf::Font *nButtonFont) {
	buttonFont = nButtonFont;
	buttonText.setFont(*buttonFont);
}
void Button::setCharSize(int nCharSize) {
	charSize = nCharSize;
	buttonText.setCharacterSize(charSize);
}
void Button::setNonSelect() {
	buttonText.setFillColor(sf::Color::Yellow);
	Sprite.setTexture(*nonSelect);
}
void Button::setHover() {
	buttonText.setFillColor(sf::Color::Green);
	Sprite.setTexture(*hover);
}
void Button::setSelect() {
	Sprite.setTexture(*select);
}
sf::Text Button::getText() {
	return buttonText;
}
bool Button::getClick() {
	if (sf::Mouse::getPosition(*window).x >= xBound[0] && sf::Mouse::getPosition(*window).x <= xBound[1]) {//mouse is within x limits
		if (sf::Mouse::getPosition(*window).y >= yBound[0] && sf::Mouse::getPosition(*window).y <= yBound[1]) { //mouse is within y limits
			setHover();//mouse is hovering over button
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				setSelect();//mouse selected button
				return true;
			}
			return false;
		}
	}
	setNonSelect();//mouse is not over button
	return false;
}
bool Button::butMain()
{
	window->draw(Sprite);
	window->draw(buttonText);
	return getClick();
}