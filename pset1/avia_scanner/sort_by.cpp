#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <iomanip>

using namespace std;

// TODO: write macro SORT_BY and overload operators for Date and Time.
#define SORT_BY(field)                                     \
  [](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
    return lhs.field < rhs.field;                          \
  }

tuple<int, int, int> GetDate(const Date& date) {
    return make_tuple(date.year, date.month, date.day);
}

tuple<int, int> GetTime(const Time& time) {
    return make_tuple(time.hours, time.minutes);
}

bool operator < (const Date& lhs, const Date& rhs) {
    return GetDate(lhs) < GetDate(rhs);
}

bool operator == (const Date& lhs, const Date& rhs) {
    return GetDate(lhs) == GetDate(rhs);
}

ostream& operator<<(ostream& os, const Date& date) {
    os << setw(4) << setfill('0') << date.year << '-'
       << setw(2) << setfill('0') << date.month << '-'
       << setw(2) << setfill('0') << date.day;
    return os;
}

bool operator < (const Time& lhs, const Time& rhs) {
    return GetTime(lhs) < GetTime(rhs);
}

bool operator == (const Time& lhs, const Time& rhs) {
    return GetTime(lhs) == GetTime(rhs);
}

ostream& operator<<(ostream& os, const Time& time) {
    os << setw(2) << setfill('0') << time.hours << ':'
       << setw(2) << setfill('0') << time.minutes;
    return os;
}

/*
***************
Situations when you might need to use macro:

// without macro
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.to < rhs.to;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.departure_time < rhs.departure_time;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.price < rhs.price;
  });
}

// with macro
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), SORT_BY(to));
  stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
  stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}
***************
*/

void TestSortBy() {
  vector<AirlineTicket> tixs = {
    {"VKO", "CDG", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "DME", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(to));
  ASSERT_EQUAL(tixs.front().to, "CDG");
  ASSERT_EQUAL(tixs.back().to, "SVO");

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(airline));
  ASSERT_EQUAL(tixs.front().airline, "Aeroflot");
  ASSERT_EQUAL(tixs.back().airline, "Utair");

  sort(begin(tixs), end(tixs), SORT_BY(departure_date));
  ASSERT_EQUAL(tixs.front().departure_date, (Date{2018, 2,  8}));
  ASSERT_EQUAL(tixs.back().departure_date, (Date{2018, 3,  5}));

  sort(begin(tixs), end(tixs), SORT_BY(departure_time));
  ASSERT_EQUAL(tixs.front().departure_time, (Time{13, 00}));
  ASSERT_EQUAL(tixs.back().departure_time, (Time{23, 00}));

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));

  sort(begin(tixs), end(tixs), SORT_BY(arrival_time));
  ASSERT_EQUAL(tixs.front().arrival_time, (Time{3, 30}));
  ASSERT_EQUAL(tixs.back().arrival_time, (Time{20, 30}));

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
}
