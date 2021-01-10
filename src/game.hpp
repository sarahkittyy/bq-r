#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "level.hpp"
#include "resource.hpp"

/**
 * @brief uses level data to create a playable level, managing physics and graphics
 */
class game : public sf::Drawable, sf::Transformable {
public:
	/**
	 * @brief constructor
	 *
	 * @param r the app resource manager
	 * @param l the level to use. internally makes a copy.
	 */
	game(resource& r, const level& l);
	~game();

	/// the width of the tilemap, in tiles (not pixels!)
	static const int TILEMAP_WIDTH;
	/// the size of each tile of the tilemap, in pixels
	static const int TILEMAP_TILE_SIZE;

	/**
	 * @brief set the tile size that each tile should be rendered at
	 *
	 * @param nsz the new size of each rendered tile.
	 */
	void set_tile_size(int nsz);

	/**
	 * @brief returns a const reference to the level stored inside
	 *
	 */
	const level& get_level() const;

private:
	/**
	 * @brief sfml draw override
	 */
	virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
	resource& m_r;	 // app resource manager

	level m_lvl;	   // internally stored level
	b2World m_world;   // the physics world

	sf::Texture& m_tstex;	// tileset texture
	int m_render_size;		// what size the tiles should be rendered to

	sf::VertexArray m_static;	// static level rendering
	void gen_static();			// generating the static level to render
};
