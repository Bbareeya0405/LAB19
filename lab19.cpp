// Please include header (lab21.h) here.
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Unit {
public:
    string name;
    int hp, hpmax, atk, def;
    bool guard_on;
    
    void create(string t_name) {
        name = t_name;
        if (t_name == "Hero") {
            hpmax = 100;
            atk = 20;
            def = 10;
        } else {
            hpmax = 80;
            atk = 25;
            def = 5;
        }
        hp = hpmax;
        guard_on = false;
    }

    void newTurn() {
        guard_on = false;
    }

    void showStatus() {
        cout << "---------------------------------------\n";
        cout << name << "\n";
        cout << "HP: " << hp << "/" << hpmax << "   ATK: " << atk << "   DEF: " << def << "\n";
        cout << "---------------------------------------\n";
    }

    bool isDead() {
        return hp <= 0;
    }

    void guard() {
        guard_on = true;
    }

    int heal() {
        int h = rand() % 21 + 10; // ฟื้นฟูเลือดระหว่าง 10 ถึง 30
        if (hp + h > hpmax) h = hpmax - hp;
        hp += h;
        return h;
    }

    int beAttacked(int opp_atk) {
        int dmg;
        if (guard_on) dmg = (opp_atk - def) / 3; // ลดความเสียหายถ้าป้องกัน
        else dmg = opp_atk - def;

        if (dmg < 0) dmg = 0;
        hp -= dmg;
        return dmg;
    }

    int attack(Unit &target) {
        return target.beAttacked(atk);
    }
};

void drawScene(char p_action, int p_val, char m_action, int m_val) {
    cout << "\n";
    cout << "Player Action: " << p_action << " (" << p_val << ")" << " | Monster Action: " << m_action << " (" << m_val << ")\n";
    cout << "\n";
}

void playerWin() {
    cout << "\nYou have defeated the monster!\n";
}

void playerLose() {
    cout << "\nYou have been defeated! Game Over.\n";
}


int main(){
	srand(time(0));
	Unit hero,mons;
	hero.create("Hero");
	mons.create("Monster");	
	int turn_count = 1;
	char player_action = '\0',monster_action = '\0';
	int p = 0, m = 0;
	while(true){
		mons.newTurn();	
		hero.newTurn();			
		mons.showStatus();
		drawScene(player_action,p,monster_action,m);
		hero.showStatus();		
		cout << "[A] Attack [H] Heal [G] Guard [E] Exit";
		cout << "\n[Turn " << turn_count << "] Enter your action: ";
		cin >> player_action;
		player_action = toupper(player_action);
		if(player_action == 'E') break; 
		
		int temp = rand()%3;
		if(temp <= 1) monster_action = 'A';
		else if(temp == 2) monster_action = 'G';
		
		if(player_action == 'G') hero.guard();
		if(monster_action == 'G') mons.guard();
		
		if(player_action == 'H') p = hero.heal();
		
		if(player_action == 'A') p = hero.attack(mons); 
		if(monster_action == 'A') m = mons.attack(hero); 
		
		if(hero.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerLose();
			break; 
		}
		
		if(mons.isDead()){
			drawScene(player_action,p,monster_action,m);
			playerWin();
			break; 
		}
		
		turn_count++;
	}
	return 0;
}
