#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;

const std::vector<int> DENOMINATIONS = { 5000, 2000, 1000, 500, 200, 100 };
const int CASSETTE_CAPACITY = 2000;          
const int INITIAL_LOAD_PERCENT = 80;         
const int MAX_NOTES_PER_OPERATION = 40;

bool is_number(const string& s);

class client {
	private:
		string name;
		string num_card;
		string Pin;
		unsigned int money;
		bool stat;
	public:
		client(string s = "-", string a = "0001", string b = "0000", int m = 0) {
			name = s;
			num_card=a;
			Pin = b;
			money = m;
			stat = false;
		}
		string& get_pin() {
			return Pin;
		}
		void block() {
			stat = true;
		}
		unsigned int balance() {
			return money;
		}
		void setBalance(unsigned int t) {
			money = t;
		}
		bool is_blocked() {
			return stat;
		}
};

class ProcessingCenter {
	private:
		map<string,client> data;
		client err;
	public:
		bool addClient(const string& cardNumber, const string& fullName, int balance, const string& pin) {
			if (data.find(cardNumber) != data.end()) {
				return false;
			}
			if (cardNumber.length() != 4 || !(is_number(cardNumber))) {
				return false;
			}
			if (pin.length() != 4 || !(is_number(pin))) {
				return false;
			}
			data.emplace(cardNumber,(cardNumber, fullName, balance, pin));
			return true;
		}
		client& find_client(const string& card)  {
			auto it = data.find(card);
			return (it != data.end()) ? it->second : err;
		}
		bool check_pin(const string& card, const string& pin) {
			client t = find_client(card);
			if (t.get_pin() == pin) {
				return true;
			}
			return false;
		}
		void block(const string& card) {
			client t = find_client(card);
			t.block();
		}
		unsigned int balance(const string& card) {
			client temp = find_client(card);
			return temp.balance();
		}
		void set_balance(const string& card, int del) {
			client temp = find_client(card);
			temp.setBalance(temp.balance() + del);
		}
		bool is_blocked(const string& card){
			client temp = find_client(card);
			return temp.is_blocked();
		}
};

class ATM {
	private:
		ProcessingCenter& pc;
		map <int, int> cass;
		string card;
		bool authentication;
		int err;

		int getTotalNotes() const {
			int total = 0;
			for (const auto& [a,b] : cass) {
				total += b;
			}
			return total;
		}

		
		std::pair<bool, std::map<int, int>> canDispense(int amount) const {
			std::map<int, int> plan;
			if (amount <= 0 || amount % 100 != 0)
				return { false, plan };

			int remaining = amount;
			int totalNotes = 0;

			for (int denom : DENOMINATIONS) {
				if (remaining == 0) break;
				int maxPossible = std::min({ cass.at(denom), remaining / denom,
											MAX_NOTES_PER_OPERATION - totalNotes });
				if (maxPossible > 0) {
					plan[denom] = maxPossible;
					totalNotes += maxPossible;
					remaining -= maxPossible * denom;
				}
			}

			if (remaining == 0 && totalNotes <= MAX_NOTES_PER_OPERATION)
				return { true, plan };
			else
				return { false, {} };
		}

		void dispense(const std::map<int, int>& plan) {
			for (const auto& [denom, count] : plan)
				cass[denom] -= count;
		}


		std::tuple<bool, int, std::map<int, int>> canAccept(const std::vector<int>& banknotes) const {
			if (banknotes.size() > MAX_NOTES_PER_OPERATION)
				return { false, 0, {} };

			std::map<int, int> required;
			int totalSum = 0;
			for (int note : banknotes) {
				if (std::find(DENOMINATIONS.begin(), DENOMINATIONS.end(), note) == DENOMINATIONS.end())
					return { false, 0, {} };
				required[note]++;
				totalSum += note;
			}

			
			for (const auto& [denom, count] : required) {
				auto it = cass.find(denom);
				if (it == cass.end()) return { false, 0, {} };
				if (it->second + count > CASSETTE_CAPACITY)
					return { false, 0, {} };
			}
			return { true, totalSum, required };
		}

		void accept(const std::map<int, int>& required) {
			for (const auto& [denom, count] : required)
				cass[denom] += count;
		}

	public:
		ATM(ProcessingCenter& center) :pc(center), authentication(false), err(0) {
			int initialCount = CASSETTE_CAPACITY * INITIAL_LOAD_PERCENT / 100;
			for (int denom : DENOMINATIONS)
				cass[denom] = initialCount;
		}
		void Getcard(const string& Card) {
			if (is_number(Card) && Card.length() == 4) {
				card = Card;
			}
		}
		bool PIN(const string& pin) {
			if (err == 3) {
				pc.block(card);
				return false;
			}
			if (pc.check_pin(card, pin)&&(!pc.is_blocked(card))) {
				authentication = true;
				return true;
			}
			err++;
			return false;
		}
		string print_cond() {
			if (pc.is_blocked(card)) {
				return "Карта заблокирована";
			}
			if (!authentication) {
				return "Не введён пин код";
			}
			return "Карта доступна\nБаланс: "+ std::to_string(pc.balance(card));
		}
		string get_money(int& m) {
			if (pc.is_blocked(card)) {
				return "Карта заблокирована";
			}
			if (!authentication) {
				return "Не введён пин код";
			}
			if (m <= 0) {
				return "Ошибка: сумма должна быть положительной.";
			}
			if (m % 100 != 0) {
				return "Ошибка: банкомат выдаёт только купюрами 100, 200, 500, 1000, 2000, 5000.";
			}
			int balance = pc.balance(card);
			if (balance < m) {
				return "Ошибка: недостаточно средств на счёте.";
			}
			auto [canDisp, plan] = canDispense(m);
			if (!canDisp) {
				return "Ошибка: банкомат не может выдать запрошенную сумму (недостаточно купюр или превышен лимит 40 купюр).";
			}
			dispense(plan);
			return "Выдано " + std::to_string(m) + " руб. Возьмите деньги.";
		}
		string set_money(const vector <int>& banknotes) {
			if (pc.is_blocked(card)) {
				return "Карта заблокирована";
			}
			if (!authentication) {
				return "Не введён пин код";
			}
			if (banknotes.empty()) {
				return "Ошибка: не передано ни одной купюры.";
			}
			if (banknotes.size() > MAX_NOTES_PER_OPERATION) {
				return "Ошибка: превышено максимальное количество купюр за операцию (максимум 40).";
			}
			auto [can_accept, totalSum, required] = canAccept(banknotes);
			if (!can_accept) {
				return "Ошибка: банкомат не может принять эти купюры (неверный номинал или переполнение кассеты).";
			}
			pc.set_balance(card, totalSum);
			accept(required);
			return "Принято " + std::to_string(totalSum) + " руб. Баланс обновлён.";
		}
		string ejectCard() {
			card.clear();
			authentication = false;
			err = 0;
			return "Приходите ещё";
		}
};

bool is_number(const string& s){
	return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}
