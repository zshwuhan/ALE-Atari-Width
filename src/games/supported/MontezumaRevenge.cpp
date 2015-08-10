/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and 
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 */
#include "MontezumaRevenge.hpp"

#include "../RomUtils.hpp"


MontezumaRevengeSettings::MontezumaRevengeSettings() {

    reset();
}


/* create a new instance of the rom */
RomSettings* MontezumaRevengeSettings::clone() const { 
    
    RomSettings* rval = new MontezumaRevengeSettings();
    *rval = *this;
    return rval;
}


/* process the latest information from ALE */
void MontezumaRevengeSettings::step(const System& system) {

    // update the reward
    int score = getDecimalScore(0x95, 0x94, 0x93, &system); 
    int reward = score - m_score;
    m_reward = reward;
    m_score = score;

    // update terminal status
    int new_lives = readRam(&system, 0xBA);
    int m_lives = new_lives;
    // if( new_lives < 5){
    // 	//std::cout << "new lives" << new_lives << std::endl;
    // 	m_reward = -10;
    // }
    int some_byte = readRam(&system, 0xFE);
    m_terminal = new_lives == 0 && some_byte == 0x60;
}


/* is end of game */
bool MontezumaRevengeSettings::isTerminal() const {

    return m_terminal;
};


/* get the most recently observed reward */
reward_t MontezumaRevengeSettings::getReward() const { 

    return m_reward; 
}


/* is an action part of the minimal set? */
bool MontezumaRevengeSettings::isMinimal(const Action &a) const {

    switch (a) {
        case PLAYER_A_NOOP:
        case PLAYER_A_FIRE:
        case PLAYER_A_UP:
        case PLAYER_A_RIGHT:
        case PLAYER_A_LEFT:
        case PLAYER_A_DOWN:
        case PLAYER_A_UPRIGHT:
        case PLAYER_A_UPLEFT:
        case PLAYER_A_DOWNRIGHT:
        case PLAYER_A_DOWNLEFT:
        case PLAYER_A_UPFIRE:
        case PLAYER_A_RIGHTFIRE:
        case PLAYER_A_LEFTFIRE:
        case PLAYER_A_DOWNFIRE:
        case PLAYER_A_UPRIGHTFIRE:
        case PLAYER_A_UPLEFTFIRE:
        case PLAYER_A_DOWNRIGHTFIRE:
        case PLAYER_A_DOWNLEFTFIRE:
            return true;
        default:
            return false;
    }   
}


/* reset the state of the game */
void MontezumaRevengeSettings::reset() {
    
    m_reward   = 0;
    m_score    = 0;
    m_terminal = false;
}


        
/* saves the state of the rom settings */
void MontezumaRevengeSettings::saveState(Serializer & ser) {
  ser.putInt(m_reward);
  ser.putInt(m_score);
  ser.putBool(m_terminal);
}

// loads the state of the rom settings
void MontezumaRevengeSettings::loadState(Deserializer & ser) {
  m_reward = ser.getInt();
  m_score = ser.getInt();
  m_terminal = ser.getBool();
}

