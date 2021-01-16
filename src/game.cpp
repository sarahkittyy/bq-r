#include "game.hpp"

game::game(resource& r, const level& l, int tswidth)
	: m_r(r),
	  m_lvl(l),
	  m_world(b2Vec2(0, -9.8f)),
	  m_tstex(m_r.texture("assets/tileset.png")),
	  m_render_size(tswidth),
	  m_ts_width(tswidth) {
	m_static.setPrimitiveType(sf::Quads);
	gen_static();
	m_ts_tsize = m_tstex.getSize().x / tswidth;
}

game::~game() {
}

void game::gen_static() {
	m_static.clear();
	for (int x = 0; x < m_lvl.width(); ++x) {
		for (int y = 0; y < m_lvl.height(); ++y) {
			tile& t = m_lvl.get_tile(x, y);
			if (t.get_type() == tile::Air) {
				continue;
			}

			// TODO: flipping based on direction

			// defining all four vertices of the quad
			sf::Vertex a, b, c, d;

			// clockwise orientation from top-left
			a.position = sf::Vector2f(
				x * m_render_size,
				y * m_render_size);
			b.position = sf::Vector2f(
				(x + 1) * m_render_size,
				y * m_render_size);
			c.position = sf::Vector2f(
				(x + 1) * m_render_size,
				(y + 1) * m_render_size);
			d.position = sf::Vector2f(
				x * m_render_size,
				(y + 1) * m_render_size);

			sf::Vector2f tl = (sf::Vector2f)(t.tex_loc(m_ts_width));
			a.texCoords		= sf::Vector2f(
				tl.x * m_ts_tsize,
				tl.y * m_ts_tsize);
			b.texCoords = sf::Vector2f(
				(tl.x + 1) * m_ts_tsize,
				tl.y * m_ts_tsize);
			c.texCoords = sf::Vector2f(
				(tl.x + 1) * m_ts_tsize,
				(tl.y + 1) * m_ts_tsize);
			d.texCoords = sf::Vector2f(
				tl.x * m_ts_tsize,
				(tl.y + 1) * m_ts_tsize);

			m_static.append(a);
			m_static.append(b);
			m_static.append(c);
			m_static.append(d);
		}
	}
}

void game::set_tile_size(int nsz) {
	m_render_size = nsz;
	gen_static();
}

const level& game::get_level() const {
	return m_lvl;
}

void game::draw(sf::RenderTarget& t, sf::RenderStates s) const {
	s.transform *= getTransform();
	s.texture = &m_tstex;

	t.draw(m_static, s);
}
