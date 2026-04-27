#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Date {
    int day, month, year;

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    void print() const {
        cout << setfill('0') << setw(2) << day << "."
            << setfill('0') << setw(2) << month << "." << year;
    }
};

struct Time {
    int hour, minute;

    bool operator<(const Time& other) const {
        if (hour != other.hour) return hour < other.hour;
        return minute < other.minute;
    }

    void print() const {
        cout << setfill('0') << setw(2) << hour << ":"
            << setfill('0') << setw(2) << minute;
    }

    Time addMinutes(int mins) const {
        Time result = *this;
        result.minute += mins;
        while (result.minute >= 60) {
            result.minute -= 60;
            result.hour++;
        }
        return result;
    }
};

class Cinema {
private:
    struct Session {
        Date date;
        Time time;
        string filmName;
        int hallNumber;
        int basePrice;
        int rows;
        int seatsPerRow;
        vector<vector<bool>> seats;

        Session(Date d, Time t, string name, int hall, int price, int r, int spr)
            : date(d), time(t), filmName(name), hallNumber(hall),
            basePrice(price), rows(r), seatsPerRow(spr) {
            seats.resize(rows, vector<bool>(seatsPerRow, true));
        }
    };

    vector<Session> sessions;
    Date currentDate;

    Date getSystemDate() {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        Date d;
        d.day = now->tm_mday;
        d.month = now->tm_mon + 1;
        d.year = now->tm_year + 1900;
        return d;
    }

    Time getSystemTime() {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        Time result;
        result.hour = now->tm_hour;
        result.minute = now->tm_min;
        return result;
    }

    int calculateTicketPrice(const Session& session, const string& zone) {
        double price = session.basePrice;

        if (session.time.hour < 12) {
            price = session.basePrice * 0.75;
        }
        else if (session.time.hour > 18) {
            price = session.basePrice * 1.5;
        }
        else {
            price = session.basePrice;
        }

        if (zone == "VIP") {
            price *= 2;
        }

        return (int)price;
    }

    int findSession(Date date, Time time, string filmName, int hall) {
        for (size_t i = 0; i < sessions.size(); i++) {
            if (sessions[i].date == date &&
                sessions[i].time.hour == time.hour &&
                sessions[i].time.minute == time.minute &&
                sessions[i].filmName == filmName &&
                sessions[i].hallNumber == hall) {
                return i;
            }
        }
        return -1;
    }

public:
    Cinema() {
        currentDate = getSystemDate();
        initializeSessions();
    }

    void initializeSessions() {
        struct HallInfo {
            int hallNumber;
            int basePrice;
            int rows;
            int seatsPerRow;
        };

        vector<HallInfo> halls = {
            {1, 300, 10, 15},
            {2, 350, 12, 18},
            {3, 400, 8, 20}
        };

        vector<string> films = { "Avatar", "Barbie", "Oppenheimer", "Dune", "Matrix" };
        vector<Time> times = { {10, 0}, {13, 0}, {16, 0}, {19, 0}, {22, 0} };

        for (int dayOffset = 0; dayOffset < 30; dayOffset++) {
            Date sessionDate = currentDate;
            sessionDate.day += dayOffset;

            while (sessionDate.day > 30) {
                sessionDate.day -= 30;
                sessionDate.month++;
                if (sessionDate.month > 12) {
                    sessionDate.month = 1;
                    sessionDate.year++;
                }
            }

            for (const auto& hall : halls) {
                for (const auto& film : films) {
                    for (const auto& time : times) {
                        sessions.push_back(Session(sessionDate, time, film,
                            hall.hallNumber, hall.basePrice,
                            hall.rows, hall.seatsPerRow));
                    }
                }
            }
        }
    }

    bool checkAvailability(Date date, Time time, string filmName, int hall,
        string zone, int ticketCount) {
        int sessionIndex = findSession(date, time, filmName, hall);
        if (sessionIndex == -1) return false;

        Session& session = sessions[sessionIndex];

        int startRow, endRow;
        if (zone == "VIP") {
            startRow = 0;
            endRow = session.rows / 3;
            if (endRow == 0) endRow = 1;
        }
        else {
            startRow = session.rows / 3;
            endRow = session.rows;
        }

        int freeSeats = 0;
        for (int r = startRow; r < endRow; r++) {
            for (int s = 0; s < session.seatsPerRow; s++) {
                if (session.seats[r][s]) freeSeats++;
            }
        }

        return freeSeats >= ticketCount;
    }

    vector<pair<int, int>> reserveSeats(Date date, Time time, string filmName,
        int hall, string zone, int ticketCount) {
        int sessionIndex = findSession(date, time, filmName, hall);
        if (sessionIndex == -1) return {};

        Session& session = sessions[sessionIndex];

        int startRow, endRow;
        if (zone == "VIP") {
            startRow = 0;
            endRow = session.rows / 3;
            if (endRow == 0) endRow = 1;
        }
        else {
            startRow = session.rows / 3;
            endRow = session.rows;
        }

        vector<pair<int, int>> reservedSeats;

        for (int r = startRow; r < endRow && (int)reservedSeats.size() < ticketCount; r++) {
            for (int s = 0; s < session.seatsPerRow && (int)reservedSeats.size() < ticketCount; s++) {
                if (session.seats[r][s]) {
                    session.seats[r][s] = false;
                    reservedSeats.push_back({ r + 1, s + 1 });
                }
            }
        }

        return reservedSeats;
    }

    void cancelReservation(Date date, Time time, string filmName, int hall,
        vector<pair<int, int>> seats) {
        int sessionIndex = findSession(date, time, filmName, hall);
        if (sessionIndex == -1) return;

        Session& session = sessions[sessionIndex];

        for (const auto& seat : seats) {
            int row = seat.first - 1;
            int col = seat.second - 1;
            if (row >= 0 && row < session.rows && col >= 0 && col < session.seatsPerRow) {
                session.seats[row][col] = true;
            }
        }
    }

    int getTicketPrice(Date date, Time time, string filmName, int hall, string zone) {
        int sessionIndex = findSession(date, time, filmName, hall);
        if (sessionIndex == -1) return 0;

        return calculateTicketPrice(sessions[sessionIndex], zone);
    }

    bool isSaleAllowed(Date date, Time time) {
        Date currentDateSys = getSystemDate();

        if (date < currentDateSys) {
            return false;
        }

        if (date == currentDateSys) {
            Time currentTime = getSystemTime();
            Time limitTime = time.addMinutes(10);
            if (currentTime < limitTime) {
                return true;
            }
            return false;
        }

        return true;
    }
};

class TicketOffice {
private:
    Cinema* cinema;

    struct Order {
        Date date;
        Time time;
        string filmName;
        int hallNumber;
        string zone;
        int ticketCount;
        vector<pair<int, int>> seats;
        int totalPrice;
        bool isActive;

        Order() : hallNumber(0), ticketCount(0), totalPrice(0), isActive(false) {}
    };

    Order currentOrder;

public:
    TicketOffice(Cinema* c) : cinema(c) {}

    void acceptCustomerData() {
        cin >> currentOrder.date.day >> currentOrder.date.month >> currentOrder.date.year;

        cin >> currentOrder.time.hour >> currentOrder.time.minute;

        cin.ignore();
        getline(cin, currentOrder.filmName);

        cin >> currentOrder.hallNumber;

        cin >> currentOrder.zone;

        cin >> currentOrder.ticketCount;

        currentOrder.isActive = true;
        currentOrder.seats.clear();
        currentOrder.totalPrice = 0;
    }

    bool checkAvailability() {
        if (!currentOrder.isActive) {
            return false;
        }

        if (!cinema->isSaleAllowed(currentOrder.date, currentOrder.time)) {
            return false;
        }

        bool available = cinema->checkAvailability(currentOrder.date, currentOrder.time,
            currentOrder.filmName, currentOrder.hallNumber,
            currentOrder.zone, currentOrder.ticketCount);

        if (available) {
        }
        else {
        }

        return available;
    }

    void reserveSeats() {
        if (!currentOrder.isActive) {
            return;
        }

        currentOrder.seats = cinema->reserveSeats(currentOrder.date, currentOrder.time,
            currentOrder.filmName, currentOrder.hallNumber,
            currentOrder.zone, currentOrder.ticketCount);

        if (currentOrder.seats.empty()) {
        }
        else {
        }
    }

    void calculateTotalPrice() {
        if (!currentOrder.isActive) {
            return;
        }

        if (currentOrder.seats.empty()) {
            return;
        }

        int pricePerTicket = cinema->getTicketPrice(currentOrder.date, currentOrder.time,
            currentOrder.filmName, currentOrder.hallNumber,
            currentOrder.zone);

        currentOrder.totalPrice = pricePerTicket * currentOrder.ticketCount;

    }

    void cancelOrder() {
        if (!currentOrder.isActive) {
            return;
        }

        if (!currentOrder.seats.empty()) {
            cinema->cancelReservation(currentOrder.date, currentOrder.time,
                currentOrder.filmName, currentOrder.hallNumber,
                currentOrder.seats);
        }

        currentOrder.isActive = false;
        currentOrder.seats.clear();
    }

    void printTickets() {
        if (!currentOrder.isActive) {
            cout << "No active order!\n";
            return;
        }

        if (currentOrder.seats.empty()) {
            cout << "No reserved seats!\n";
            return;
        }

        cout << "\n" << string(60, '=') << endl;
        cout << "                    TICKETS" << endl;
        cout << string(60, '=') << endl;

        int pricePerTicket = cinema->getTicketPrice(currentOrder.date, currentOrder.time,
            currentOrder.filmName, currentOrder.hallNumber,
            currentOrder.zone);

        for (size_t i = 0; i < currentOrder.seats.size(); i++) {
            cout << "\n--- TICKET #" << i + 1 << " ---\n";
            cout << "Film: " << currentOrder.filmName << endl;
            cout << "Date: ";
            currentOrder.date.print();
            cout << "\nTime: ";
            currentOrder.time.print();
            cout << "\nHall: " << currentOrder.hallNumber << endl;
            cout << "Row: " << currentOrder.seats[i].first << endl;
            cout << "Seat: " << currentOrder.seats[i].second << endl;
            cout << "Zone: " << currentOrder.zone << endl;
            cout << "Price: " << pricePerTicket << " rub." << endl;
            cout << string(40, '-') << endl;
        }

        cout << "\nTOTAL TO PAY: " << currentOrder.totalPrice << " rub.\n";
        cout << string(60, '=') << "\n";
        cout << "Thank you for your purchase! Enjoy the show!\n";
    }

    void buyTicket() {
        acceptCustomerData();

        if (!checkAvailability()) {
            cancelOrder();
            return;
        }

        reserveSeats();
        calculateTotalPrice();

        int confirm;
        cin >> confirm;

        if (confirm == 1) {
            printTickets();
        }
        else {
            cancelOrder();
        }
    }
};

int main() {
    cout << "=== WELCOME TO THE CINEMA ===\n";
    cout << "Halls 1, 2, 3 available\n";
    cout << "Films: Avatar, Barbie, Oppenheimer, Dune, Matrix\n";
    cout << "Sessions: 10:00, 13:00, 16:00, 19:00, 22:00\n\n";

    Cinema cinema;
    TicketOffice ticketOffice(&cinema);

    int choice;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1 - Buy ticket\n";
        cout << "2 - Check seat availability\n";
        cout << "3 - Cancel current order\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ticketOffice.buyTicket();
            break;
        case 2:
            ticketOffice.checkAvailability();
            break;
        case 3:
            ticketOffice.cancelOrder();
            break;
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);  
    return 0;
}