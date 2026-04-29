#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Warehouse {
private:
    struct Product {
        string code;
        string name;
        int price;
        int discount;
    };
    vector<Product> products;

public:
    void add(string code, string name, int price, int discount) {
        products.push_back({ code, name, price, discount });
    }

    int find(string code) const {
        for (int i = 0; i < products.size(); i++)
            if (products[i].code == code) return i;
        return -1;
    }

    string getName(int idx) const { return products[idx].name; }
    int getPrice(int idx) const { return products[idx].price; }
    int getDiscount(int idx) const { return products[idx].discount; }
};

class CashRegister {
private:
    const Warehouse& sklad;
    struct ReceiptItem {
        int prodIndex;
        int quantity;
    };
    vector<ReceiptItem> items;

    int findInReceipt(int prodIdx) const {
        for (int i = 0; i < items.size(); i++)
            if (items[i].prodIndex == prodIdx) return i;
        return -1;
    }

public:
    CashRegister(const Warehouse& w) : sklad(w) {}

    string scan(string code) {
        int idx = sklad.find(code);
        if (idx == -1)
            return "Товар " + code + " не найден.";
        return "Товар: " + sklad.getName(idx) + ", цена: " + to_string(sklad.getPrice(idx)) +
            " руб., скидка: " + to_string(sklad.getDiscount(idx)) + "%";
    }

    string getDescription(string code) {
        int idx = sklad.find(code);
        if (idx == -1) return "Товар не найден";
        return sklad.getName(idx) + " | " + to_string(sklad.getPrice(idx)) + " руб. | скидка " + to_string(sklad.getDiscount(idx)) + "%";
    }

    string addToReceipt(string code) {
        int idx = sklad.find(code);
        if (idx == -1) return "Товара нет на складе";

        int pos = findInReceipt(idx);
        if (pos == -1)
            items.push_back({ idx, 1 });
        else
            items[pos].quantity++;
        return "Товар добавлен. Количество: " + to_string(items[pos == -1 ? items.size() - 1 : pos].quantity);
    }

    void printReceipt() {
        if (items.empty()) {
            cout << "Чек пуст.\n";
            return;
        }
        int totalBefore = 0, totalDiscount = 0;
        cout << "\n===== ЧЕК =====\n";
        for (auto& it : items) {
            int idx = it.prodIndex;
            int price = sklad.getPrice(idx);
            int discount = sklad.getDiscount(idx);
            int sumBefore = price * it.quantity;
            int sumAfter = sumBefore * (100 - discount) / 100;
            totalBefore += sumBefore;
            totalDiscount += sumBefore - sumAfter;
            cout << sklad.getName(idx) << "  x" << it.quantity
                << "  = " << sumAfter << " руб.\n";
        }
        cout << "--------------------\n";
        cout << "Стоимость без скидок: " << totalBefore << " руб.\n";
        cout << "Скидка: " << totalDiscount << " руб.\n";
        cout << "ИТОГО: " << totalBefore - totalDiscount << " руб.\n";
    }


    int calcTotal() {
        int total = 0;
        for (auto& it : items) {
            int price = sklad.getPrice(it.prodIndex);
            int discount = sklad.getDiscount(it.prodIndex);
            total += price * it.quantity * (100 - discount) / 100;
        }
        return total;
    }


    string removeProduct(string code) {
        int idx = sklad.find(code);
        if (idx == -1) return "Товара нет на складе";
        int pos = findInReceipt(idx);
        if (pos == -1) return "Товара нет в чеке";
        items.erase(items.begin() + pos);
        return "Товар удалён из чека";
    }

    void showReceipt() {
        if (items.empty()) cout << "Корзина пуста.\n";
        else for (auto& it : items) {
            cout << sklad.getName(it.prodIndex) << " x" << it.quantity << "\n";
        }
    }
};
int main(){}