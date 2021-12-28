/**
 * @file User.h
 * @author ALEXANDER (you@domain.com)
 * @brief файл класс пользователя 
 * @version 0.1
 * @date 2021-12-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef USER_HEADER
#define USER_HEADER

#include "Dungeon_and_Creature.h"
#include "Alive_Creature.h"
#include "Dead_Creature.h"
/**
 * @brief Класс пользователь
 * 
 */
class User : public Creature
{
	private:
		int max_mana;
		int mana;
		int next_level_experience; // 0th -> 1st level 100 exp
		int experience;
		int level;
		int skill_point;
		std::map<skills, int> skill_table;

		void correct();
		
	public:
	/**
	 * @brief Construct a new User object
	 * 
	 * @param mh максимальное здоровье
	 * @param d урон
	 * @param dp вероятность нанести урон
	 * @param mm максимальная мана
	 */
		explicit User(int mh, int d, int dp, int mm) :
		Creature(USER, mh, FRIEND, d, dp, NONE), max_mana(mm), mana(max_mana), next_level_experience(100), experience(0), level(0), skill_point(0)
		{
			for(int i = 0; i < 4; ++i) skill_table.insert(std::pair<skills, int>(static_cast<skills>(i), 0));
		};
		/**
		 * @brief Construct a new User object
		 * 
		 */
		User() :
		Creature(USER, 10, FRIEND, 2, 65, NONE), max_mana(0), mana(0), next_level_experience(100), experience(0), level(0), skill_point(0)
		{
			for(int i = 0; i < 4; ++i) skill_table.insert(std::pair<skills, int>(static_cast<skills>(i), 0));
		};
/**
 * @brief Destroy the User object
 * 
 */
		~User() = default;
/**
 * @brief Get the max mana object
 * 
 * @return max_mana 
 */
		inline int get_max_mana() const noexcept
		{
			return max_mana;
		};
		/**
		 * @brief Get the mana object
		 * 
		 * @return mana 
		 */
		inline int get_mana() const noexcept
		{
			return mana;
		};
/**
 * @brief Get the next level experience object
 * 
 * @return next_level_experience 
 */
		inline int get_next_level_experience() const noexcept
		{
			return next_level_experience;
		};
/**
 * @brief Get the level object
 * 
 * @return level 
 */
		inline int get_level() const noexcept
		{
			return level;
		};
/**
 * @brief Get the experience object
 * 
 * @return experience 
 */
		inline int get_experience() const noexcept
		{
			return experience;
		};
/**
 * @brief Get the skill point object
 * 
 * @return skill_point 
 */
		inline int get_skill_point() const noexcept
		{
			return skill_point;
		};
/**
 * @brief Get the skill power object
 * 
 * @param skill скилл который мы хотим проверить
 * @return int 
 */
		inline int get_skill_power(const skills skill) const
		{
			return skill_table.at(skill);
		};
/**
 * @brief Get the skill table object
 * 
 * @return std::map<skills, int> копия таблицы умений
 */
		inline std::map<skills, int> get_skill_table() const
		{
			return skill_table;
		};
/**
 * @brief Set the mana object
 * 
 * @param state 
 * @throw Exception("unavailable_value") попытка установить неправильное значение
 */
		void set_mana(const int state);
		/**
		 * @brief Set the experience object
		 * 
		 * @param state 
		 * @throw Exception("unavailable_value") попытка установить неправильное значение
		 */
		void set_experience(const int state);
		/**
		 * @brief Set the skill point object
		 * 
		 * @param state 
		 * @throw Exception("unavailable_value") попытка установить неправильное значение
		 */
		void set_skill_point(const int state);
		/**
		 * @brief Set the skill power object
		 * 
		 * @param skill 
		 * @param state 
		 * @throw Exception("unavailable_value") попытка установить неправильное значение
		 */
		void set_skill_power(const skills skill, const int state);
/**
 * @brief собрать эссенцию
 * удалит элемент эссенция с поля		 
 * @throw Exception("wrong_type") собирать нечего
 */
		void collect_essence();
		/**
		 * @brief прибавить онять определенное количество маны
		 * @throw Exception("not_enouth_mana") недостаточно маны
		 * @param state 
		 */
		void mana_exchange(const int state);
		/**
		 * @brief получить определенное количество опыта
		 * 
		 * @throw Exception("unavailable_value") попытка установить неправильное значение
		 * @param state 
		 */
		void receive_experience(const int state);
		/**
		 * @brief получить определенное количество здоровья
		 * @throw Exception("unavailable_value") попытка установить неправильное значение
		 * @param state 
		 */
		void receive_health(const int state);
		/**
		 * @brief улучшить определенное умение
		 * @throw Exception("not_enouth_skill_point") неостаточно очков умения
		 * @throw Exception("already_max_state") уже максимальное значение 
		 * @param skill_name 
		 */
		void skill_increase(const skills skill_name);
/**
 * @brief иссушить труп существа
 * получить опредлынные очки (опыт здоровье ману) 
 * 
 * @throw Exception("skill_not_available") умение недоступно
 * @throw Exception("target_not_found") цель не найдена
 * @throw Exception("target_is_not_alive_at_all_or_still_alive") цель не подходит
 * @throw Exception("nullptr_object") nullptr object received
 */
		void wither();
		/**
		 * @brief прокляти
		 * накладывает на враждебное чущество определенный эффект
		 * @throw Exception("skill_not_available") умение недоступно
		 * @throw Exception("target_not_found") цель не найдена
		 * @throw Exception("target_is_not_alive_or_already_dead") цель не подходит
		 * @throw Exception("nullptr_object") nullptr object received
		 */
		void curse();
		/**
		 * @brief некромантия
		 * превратить враждебный труп в живого мертвого дружественного существа
		 * @throw Exception("skill_not_available") умение недоступно
		 * @throw Exception("target_not_found") цель не найдена
		 * @throw Exception("target_is_still_alive") цель не подходит
		 * @throw Exception("nullptr_object") nullptr object received
		 */
		void necromancy();
		/**
		 * @brief морфиз
		 * улучшить характеристики дружественного мертвого существа
		 * ухудшить характеристики враждебного
		 * 
		 * @throw Exception("skill_not_available") умение недоступно
		 * @throw Exception("target_not_found") цель не найдена
		 * @throw Exception("target_is_alive") цель не подходит
		 * @throw Exception("nullptr_object") nullptr object received
		 * @throw Exception("already_max_state") already_max_state
		 * @throw Exception("already_min_state") already_min_state
		 */
		void morphism();
/**
 * @brief получить урон от другого существа
 * 
 * @param magnitude колличество единиц здоровья которые может потерять пользлватель
 * @param probability вероятность получения урона
 * @return true умер
 * @return false не умер
 * @throw Exception("unavailale_value") неверные значения
 */
		bool receive_damage(const int magnitude, const int probability);
		/**
		 * @brief нанести урон
		 * 
		 * @param target сужество которое получает урон
		 * @throw Exception("self_harm") попытка нанести урон самому себе
 		 * @throw Exception(friendly_fire) попытка нанести урон дружественому существу
		 */
		void to_damage(Creature * target) const;
/**
 * @brief выполнить ход имеет смысл для друх сущест
 * остался здесь чтобы не ломать логику программы 
 * 
 * @return true мертв
 * @return false жив
 */
		bool turn();
};

#endif
