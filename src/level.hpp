#pragma once

#include <json.hpp>

#include "tile.hpp"

/**
 * @brief level class
 * 
 * @remarks does not actually store level running / rendering information,
 *	simply just stores raw level data, for serialization and passing to a level runner of sorts
 */
class level {
public:
	level(int width, int height);
	level(const level& other);
	level(const nlohmann::json& data);
	~level();

	/**
	 * @brief update a tile in the map
	 *
	 * @param x the x position
	 * @param y the y position
	 * @param t the tile
	 */
	void set_tile(int x, int y, tile t);

	/**
	 * @brief retrieve a tile in the map
	 *
	 * @param x
	 * @param y
	 * @return the tile
	 */
	const tile& get_tile(int x, int y) const;

	/**
	 * @brief the non-const version of get_tile
	 *
	 * @param x 
	 * @param y
	 */
	tile& get_tile(int x, int y);

	/**
	 * @brief convert this level's into a portable json format
	 *
	 */
	nlohmann::json serialize() const;

	/**
	 * @brief update this level to reflect the data in the level json
	 *
	 * @param j the level json (obtained from serialize()
	 */
	void deserialize(const nlohmann::json& j);

private:
	// size of the level
	int m_width;
	int m_height;

	/**
	 * @brief convert a xy coord into a tile index
	 *
	 * @param x the coordinate x position
	 * @param y the coordinate y position
	 * @return the index into m_tiles to seek
	 */
	int c2i(int x, int y) const;

	// 2d array of tiles
	// stored in [x + y * width] where [0] is the top-left
	tile* m_tiles;
};
