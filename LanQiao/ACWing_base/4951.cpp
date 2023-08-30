#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, s;
    cin >> n >> s;

    unordered_map<int, pair<int, char>> records;
    for (int i = 0; i < n; i++) {
        char type;
        int price, quantity;
        cin >> type >> price >> quantity;
        if (type == 'B') {
            records[price].first += quantity;
            records[price].second = 'B';
        } else {
            records[price].first += quantity;
            records[price].second = 'S';
        }
    }

    unordered_map<int, pair<int, char>> merged_records;
    for (auto& record : records) {
        int price = record.first;
        int quantity = record.second.first;
        char type = record.second.second;
        if (quantity == 0) {
            continue;
        }
        while (merged_records.count(price)) {
            int merged_quantity = merged_records[price].first;
            char merged_type = merged_records[price].second;
            if (type == merged_type) {
                merged_records[price].first += quantity;
                quantity = 0;
                break;
            } else if (quantity > merged_quantity) {
                quantity -= merged_quantity;
                merged_records[price].first = 0;
            } else {
                merged_records[price].first -= quantity;
                quantity = 0;
                break;
            }
        }
        if (quantity > 0) {
            merged_records[price] = {quantity, type};
        }
    }

    vector<pair<int, char>> sorted_records;
    for (auto& record : merged_records) {
        int price = record.first;
        int quantity = record.second.first;
        char type = record.second.second;
        if (quantity > 0) {
            sorted_records.push_back({price, type});
        }
    }
    sort(sorted_records.begin(), sorted_records.end(), greater<pair<int, char>>());

    int sell_count = 0;
    for (auto& record : sorted_records) {
        if (record.second == 'S') {
            cout << "S " << record.first << " " << merged_records[record.first].first << endl;
            sell_count++;
            if (sell_count == s) {
                break;
            }
        }
    }

    int buy_count = 0;
    for (auto& record : sorted_records) {
        if (record.second == 'B') {
            cout << "B " << record.first << " " << merged_records[record.first].first << endl;
            buy_count++;
            if (buy_count == s) {
                break;
            }
        }
    }

    return 0;
}
