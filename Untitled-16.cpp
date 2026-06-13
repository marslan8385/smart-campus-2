#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Reportable {
public:
    virtual string generateReport() const = 0;
    virtual ~Reportable() = default;
};

class Accommodation {
protected:
    string name;
    string location;
    int totalRooms;
    double pricePerNight;

public:
    Accommodation(const string& name, const string& location,
                  int totalRooms, double pricePerNight)
        : name(name), location(location),
          totalRooms(totalRooms), pricePerNight(pricePerNight) {}

    virtual void checkIn(const string& guestName, int roomNumber) = 0;
    virtual void checkOut(int roomNumber) = 0;
    virtual int getAvailableRooms() const = 0;

    string getName()     const { return name; }
    string getLocation() const { return location; }
    int    getTotalRooms()    const { return totalRooms; }
    double getPricePerNight() const { return pricePerNight; }

    virtual ~Accommodation() = default;
};


class HostelManager : public Accommodation, public Reportable {
private:
    struct Room {
        int    number;
        bool   occupied;
        string guestName;
        int    bedsTotal;
        int    bedsOccupied;

        Room(int num, int beds)
            : number(num), occupied(false),
              guestName(""), bedsTotal(beds), bedsOccupied(0) {}
    };

    vector<Room> rooms;
    int totalCheckIns;

    Room* findRoom(int roomNumber) {
        for (auto& r : rooms)
            if (r.number == roomNumber) return &r;
        return nullptr;
    }

    const Room* findRoom(int roomNumber) const {
        for (const auto& r : rooms)
            if (r.number == roomNumber) return &r;
        return nullptr;
    }

public:
    HostelManager(const string& name, const string& location,
                  int numRooms, int bedsPerRoom, double pricePerNight)
        : Accommodation(name, location, numRooms, pricePerNight),
          totalCheckIns(0)
    {
        for (int i = 1; i <= numRooms; ++i)
            rooms.emplace_back(i, bedsPerRoom);
    }


    void checkIn(const string& guestName, int roomNumber) override {
        Room* room = findRoom(roomNumber);
        if (!room) {
            cout << "  [!] Room " << roomNumber << " does not exist.\n";
            return;
        }
        if (room->bedsOccupied >= room->bedsTotal) {
            cout << "  [!] Room " << roomNumber << " is fully occupied.\n";
            return;
        }
        room->occupied   = true;
        room->guestName  = guestName;   
        room->bedsOccupied++;
        totalCheckIns++;
        cout << "  [✓] " << guestName << " checked into Room "
             << roomNumber << " (bed " << room->bedsOccupied
             << "/" << room->bedsTotal << ").\n";
    }

    void checkOut(int roomNumber) override {
        Room* room = findRoom(roomNumber);
        if (!room) {
            cout << "  [!] Room " << roomNumber << " does not exist.\n";
            return;
        }
        if (room->bedsOccupied == 0) {
            cout << "  [!] Room " << roomNumber << " is already empty.\n";
            return;
        }
        room->bedsOccupied--;
        if (room->bedsOccupied == 0) {
            room->occupied  = false;
            room->guestName = "";
        }
        cout << "  [✓] One guest checked out of Room " << roomNumber
             << " (" << room->bedsOccupied << "/" << room->bedsTotal
             << " beds remaining).\n";
    }

    int getAvailableRooms() const override {
        int count = 0;
        for (const auto& r : rooms)
            if (r.bedsOccupied < r.bedsTotal) ++count;
        return count;
    }

    
    string generateReport() const override {
        ostringstream oss;
        int occupiedBeds = 0, totalBeds = 0;

        oss << "\n╔══════════════════════════════════════════════╗\n";
        oss << "║         OCCUPANCY REPORT                     ║\n";
        oss << "╠══════════════════════════════════════════════╣\n";
        oss << "║ Hostel  : " << left << setw(34) << name       << "║\n";
        oss << "║ Location: " << left << setw(34) << location   << "║\n";
        oss << "╠══════════════════════════════════════════════╣\n";
        oss << "║  Room  │ Beds Used │ Beds Total │  Status    ║\n";
        oss << "║────────┼───────────┼────────────┼────────────║\n";

        for (const auto& r : rooms) {
            totalBeds    += r.bedsTotal;
            occupiedBeds += r.bedsOccupied;

            string status = r.bedsOccupied == 0          ? "  Empty  "
                          : r.bedsOccupied == r.bedsTotal ? "  Full   "
                                                           : " Partial ";
            oss << "║  " << setw(5) << r.number << " │    "
                << setw(5) << r.bedsOccupied << "    │     "
                << setw(5) << r.bedsTotal    << "    │ "
                << status << "  ║\n";
        }

        double occupancyRate = totalBeds > 0
            ? (100.0 * occupiedBeds / totalBeds) : 0.0;

        oss << "╠══════════════════════════════════════════════╣\n";
        oss << "║ Total Beds    : " << setw(28) << totalBeds    << " ║\n";
        oss << "║ Occupied Beds : " << setw(28) << occupiedBeds << " ║\n";
        oss << "║ Occupancy Rate: " << setw(25) << fixed
            << setprecision(1) << occupancyRate << " %" << " ║\n";
        oss << "║ Total Check-ins (session): "
            << setw(17) << totalCheckIns << " ║\n";
        oss << "║ Price / Night : PKR "
            << setw(24) << fixed << setprecision(2) << pricePerNight << " ║\n";
        oss << "╚══════════════════════════════════════════════╝\n";

        return oss.str();
    }

    void displayRooms() const {
        cout << "\n  Available rooms with free beds:\n";
        for (const auto& r : rooms)
            if (r.bedsOccupied < r.bedsTotal)
                cout << "    Room " << r.number
                     << " — " << (r.bedsTotal - r.bedsOccupied)
                     << " bed(s) free\n";
    }
};

int main() {
    cout << "=== HostelManager Demo ===\n\n";

    HostelManager hostel("Lahore Youth Hostel", "Lahore, Punjab",
                         /*rooms=*/4, /*bedsPerRoom=*/3, /*price=*/1500.0);

    hostel.displayRooms();

    cout << "\n--- Check-ins ---\n";
    hostel.checkIn("Ali Raza",    1);
    hostel.checkIn("Sara Khan",   1);
    hostel.checkIn("Umar Farooq", 2);
    hostel.checkIn("Hina Baig",   2);
    hostel.checkIn("Zaid Malik",  2);
    hostel.checkIn("Nadia Shah",  2);   
    hostel.checkIn("Bilal Ahmed", 3);

    cout << "\n--- Check-outs ---\n";
    hostel.checkOut(1);
    hostel.checkOut(5); 

    cout << "\n--- Available Rooms: "
         << hostel.getAvailableRooms() << " ---\n";

    
    cout << hostel.generateReport();

    return 0;
}