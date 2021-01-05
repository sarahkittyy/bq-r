#pragma once

#include <json.hpp>

/**
 * @brief level class
 * 
 * @remarks does not actually store level running / rendering information,
 *	simply just stores raw level data, for serialization and passing to a level runner of sorts
 */
class level {
public:
	level();
	~level();

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
};
