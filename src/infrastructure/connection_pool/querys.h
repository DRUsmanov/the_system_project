#include <unordered_map>
#include <string>

namespace infrastructure {

const std::string save_player_result{"save_score"};
const std::string load_players_result{"load_score"};

inline const std::unordered_map<std::string, std::string> querys{
    {save_player_result, R"(INSERT INTO retired_players (id, name, score, play_time_ms) VALUES ($1, $2, $3, $4);)"},
    {load_players_result, R"(SELECT * FROM retired_players ORDER BY score DESC, play_time_ms, name LIMIT $2 OFFSET $1;)"}
};

} // namespace infrastructure
