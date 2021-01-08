#pragma once

#include <json.hpp>

/**
 * @brief one of the many tiles in a level
 */
class tile {
public:
	/**
	 * @brief the type of this tile
	 */
	enum type {
		AIR,
		BLOCK,
		SPIKE,
		START,
		END,
	};

	/**
	 * @brief construct to an empty air tile
	 *
	 */
	tile();

	/**
	 * @brief construct to a specific tile type
	 *
	 * @param t 
	 */
	tile(type t);

	/**
	 * @brief get this tile's type
	 *
	 */
	type get_type() const;

	/**
	 * @brief set this tile's type
	 *
	 * @param t
	 */
	void set_type(type t);

	/**
	 * @brief convert a tile type into a string
	 *
	 * @param t
	 */
	static std::string type_to_str(type t);

	/**
	 * @brief convert a string into a tile type
	 *
	 * @param s the string representing the type
	 * @return AIR if not found, else the type
	 */
	static type str_to_type(const std::string& s);

	/**
	 * @brief serialize this tile into a simple json object
	 *
	 */
	nlohmann::json serialize() const;

	/**
	 * @brief overwrite this tile with the data found in the json obect
	 *
	 * @param j valid tile json generated from serialize()
	 */
	void deserialize(const nlohmann::json& j);

private:
	// the tile type
	type m_type;
};
