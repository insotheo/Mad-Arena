#ifndef GAME_UI
#define GAME_UI

#include "engine/Pawn.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class FontHandler {
public:
	static sf::Font s_font;
	static bool s_loaded;

	inline static void load() {
		if (!s_loaded) {
			if (!s_font.openFromFile("./assets/font/PixelifySans.ttf")) { return; }
			s_loaded = true;
		}
	}
};

class UIText : public Pawn{
public:
	UIText(const std::string& text, unsigned int size, const sf::Vector2f& pos, const sf::Color& fill = sf::Color::Black, const sf::Color& outline = sf::Color::White, const unsigned int outlineSize = 0)
		: m_text(FontHandler::s_font, text), m_offset(pos)
	{ 
		m_text.setFillColor(fill);
		m_text.setOutlineColor(outline);
		m_text.setOutlineThickness(outlineSize);
		m_text.setCharacterSize(size);
		m_text.setOrigin(m_text.getLocalBounds().getCenter());
	}

	inline void draw(WND wnd, SCENE_REF scene) override {
		sf::Vector2f pos = wnd.mapPixelToCoords({ (int)m_offset.x, (int)m_offset.y }, wnd.getView());
		m_text.setPosition(pos);
		wnd.draw(m_text);
	};

	inline void setText(const std::string& text) {
		m_text.setString(text);
	}

	inline sf::Text& getText() { return m_text; }

private:
	sf::Vector2f m_offset;
	sf::Text m_text;
};

class UIImage : public Pawn {
public:
	UIImage(const std::string& path, const sf::FloatRect& rectangle, UIText& txt, const sf::Vector2f& offset)
		: m_sprite(m_txt), m_text(txt), m_textOffset(offset)
	{
		if (!m_txt.loadFromFile(path)) { return; }
		m_sprite = sf::Sprite(m_txt);
		m_sprite.setScale(rectangle.size);
		m_sprite.setOrigin(rectangle.getCenter());
	}

	inline void draw(WND wnd, SCENE_REF scene) override {
		sf::Vector2f pos = wnd.mapPixelToCoords({ (int)m_offset.x, (int)m_offset.y }, wnd.getView());
		m_sprite.setPosition(pos);
		wnd.draw(m_sprite);
		m_text.getText().setPosition({ pos.x + m_textOffset.x, pos.y + m_textOffset.y });
		wnd.draw(m_text.getText());
	};

private:
	UIText& m_text;
	sf::Vector2f m_textOffset;

	sf::Vector2f m_offset;

	sf::Texture m_txt;
	sf::Sprite m_sprite;
};

template<typename Func>
class Button : public Pawn {
public:
	Button(Func function,
		const sf::FloatRect& rectangle,
		const std::string& text,
		const sf::Color& background = sf::Color::Transparent, const sf::Color& accent = sf::Color::Green, const sf::Color& fontColor = sf::Color::White)
		: m_shape(rectangle.size), m_text(FontHandler::s_font, text), m_act{ std::forward<Func>(function) },
		m_backgroundColor(background), m_accentColor(accent), m_offset(rectangle.position), m_isOver(false)
	{
		m_shape.setFillColor(m_backgroundColor);
		m_text.setCharacterSize(24);
		m_text.setString(text);
		m_text.setFillColor(fontColor);
		m_text.setOrigin(m_text.getGlobalBounds().getCenter());
	}

	inline void tick(WND wnd, SCENE_REF scene, float dt) override {
		sf::Vector2f mousePos = wnd.mapPixelToCoords(sf::Mouse::getPosition(wnd), wnd.getView());
		if (m_shape.getGlobalBounds().contains(mousePos)) {
			m_isOver = true;
		}
		else { m_isOver = false; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isOver) {
			call();
		}
	};

	inline void draw(WND wnd, SCENE_REF scene) override {
		if (m_isOver) {
			m_shape.setFillColor(m_accentColor);
		}
		else {
			m_shape.setFillColor(m_backgroundColor);
		}

		sf::Vector2f shapePos = wnd.mapPixelToCoords({ (int)m_offset.x, (int)m_offset.y }, wnd.getView());
		m_shape.setPosition(shapePos);
		sf::Vector2f textPos = shapePos + (m_text.getGlobalBounds().size / 2.f);
		m_text.setPosition({textPos.x + 5.f, textPos.y + 5.f});

		wnd.draw(m_shape);
		wnd.draw(m_text);
	};

	inline void call() {
		m_act();
	}
private:
	Func m_act;

	sf::Color m_backgroundColor;
	sf::Color m_accentColor;

	sf::Vector2f m_offset;

	sf::RectangleShape m_shape;
	sf::Text m_text;

	bool m_isOver;
};

#endif // !GAME_UI