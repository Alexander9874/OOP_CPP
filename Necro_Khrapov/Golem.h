/**
 * @file Golem.h
 * @author ALEXANDER (me@domain.com)
 * @brief заголовочный файл для класса голем
 * @version 0.1
 * @date 2021-12-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GOLEM_HEADDER
#define GOLEM_HEAEDER

#include "Dungeon_and_Creature.h"

/**
 * @brief Класс голем
 * голем - существо, отличающееся возможность отражать урон
 * и оставлять после смерти либо лаву либо стену либо эссецию
 */
class Golem : public Creature
{
	private:
		int receive_damage_probability;	///< веротность получени урона, измеряется в целых процентах
		golem_states golem_state;		///< вид голема, големы бывают огненные FIRE, эфирные ETHER, каменные STONE
	public:
/**
 * @brief Construct a new Golem object
 * 
 * @param mh максимальное здоровье
 * @param d урон наносимы существом
 * @param dp вероятность нанести урон
 * @param gs вид голема
 * @param rdp вероятность получить урон
 */
		explicit Golem(int mh, int d, int dp, golem_states gs, int rdp) :
		Creature(GOLEM, mh, ENEMY, d, dp, NONE), receive_damage_probability(rdp), golem_state(gs)  {};

/**
 * @brief Construct a new Golem object
 * конструктор создает копию голема хранящегося в конфиурации 
 * @param state вид голема (огненный ... )
 */
		explicit Golem(golem_states state) : 
		Golem(*(dynamic_cast<Golem *>(dungeon->get_configuration(GOLEM))))
		{
			golem_state = state;
		}
/**
 * @brief Get the recieve damage probability object
 * 
 * @return receive_damage_probability 
 */
    	inline int get_recieve_damage_probability() const
		{
			return receive_damage_probability;
		};

/**
 * @brief Get the golem state object
 * 
 * @return golem_states 
 */
    	inline golem_states get_golem_state() const
		{
			return golem_state;
		};
/**
 * @brief Set the recieve damage probability object
 * 
 * @param state 
 * @throw Exception("unavailable_value") попытка установить неправильное значение
 */
		void set_recieve_damage_probability(const int state);
/**
 * @brief Set the golem state object
 * 
 * @param state 
 * @throw Exсeption("unavailable_value") попытка установить неправильное значение
 */
		void set_golem_state(const golem_states state);
/**
 * @brief Получение урона со стороны другого существа или лавы
 * 
 * @param magnitude количество единиц здоровь, которые существо может потерять
 * @param probability вероятность получения урона
 * @return true существо получило фатальный урон, существо погибло
 * @return false существо получило или совсем не получило урон и осталось живо
 * @throw Exсeption("unavailable_value") попытка установить неправильное значение
 */
		bool receive_damage(const int magnitude, const int probability);
/**
 * @brief нанести урон другому существу
 * в случае нанесения фатального урона, target будет удален
 * 
 * @param target указатель на существо которое получит урон 
 * @throw Exception("self_harm") попытка нанести урон самому себе
 * @throw Exception(friendly_fire) попытка нанести урон дружественому существу
 */
        void to_damage(Creature * target) const;
/**
 * @brief Destroy the Golem object
 * оставляет после себя Стену, эссенцию или лаву,
 * в зависимости от состояния голема
 * 
 */
        ~Golem()
		{
			cell_states cell;
			if(golem_state == ETHER) cell = ESSENCE;
			else if(golem_state == FIRE) cell = LAVA;
			else cell = WALL;
			dungeon->try_emplace_cell(get_position(), cell);
		};
};

#endif