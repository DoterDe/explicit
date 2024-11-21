#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

class Reservoir {
private:
    string name;
    double width;
    double length;
    double max_depth;
    string type;

public:
    explicit Reservoir() : name("Undefined"), width(0), length(0), max_depth(0), type("Unknown") {}

    explicit Reservoir(const string& name, double width, double length, double max_depth, const string& type)
        : name(name), width(width), length(length), max_depth(max_depth), type(type) {}

    Reservoir(const Reservoir& other)
        : name(other.name), width(other.width), length(other.length), max_depth(other.max_depth), type(other.type) {}

    ~Reservoir() {}

    void setName(const string& name) { this->name = name; }
    string getName() const { return name; }

    void setDimensions(double width, double length, double max_depth) {
        this->width = width;
        this->length = length;
        this->max_depth = max_depth;
    }

    void getDimensions(double& width, double& length, double& max_depth) const {
        width = this->width;
        length = this->length;
        max_depth = this->max_depth;
    }

    void setType(const string& type) { this->type = type; }
    string getType() const { return type; }

    double calculateVolume() const {
        return width * length * max_depth;
    }

    double calculateSurfaceArea() const {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const {
        return type == other.type;
    }

    bool hasLargerSurfaceAreaThan(const Reservoir& other) const {
        return calculateSurfaceArea() > other.calculateSurfaceArea();
    }

    void display() const {
        cout << "Name: " << name
            << ", Type: " << type
            << ", Width: " << width
            << "m, Length: " << length
            << "m, Max Depth: " << max_depth
            << "m, Volume: " << calculateVolume()
            << "m³, Surface Area: " << calculateSurfaceArea() << "m²\n";
    }
};

class ReservoirManager {
private:
    vector<shared_ptr<Reservoir>> reservoirs;

public:
    void addReservoir(const Reservoir& reservoir) {
        reservoirs.push_back(make_shared<Reservoir>(reservoir));
    }

    void removeReservoir(size_t index) {
        if (index < reservoirs.size()) {
            reservoirs.erase(reservoirs.begin() + index);
        }
        else {
            cerr << "Invalid index\n";
        }
    }

    void saveToTextFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& reservoir : reservoirs) {
                file << reservoir->getName() << ","
                    << reservoir->getType() << ","
                    << reservoir->calculateVolume() << ","
                    << reservoir->calculateSurfaceArea() << "\n";
            }
            file.close();
        }
        else {
            cerr << "Unable to open file\n";
        }
    }

    void displayAll() const {
        for (size_t i = 0; i < reservoirs.size(); ++i) {
            cout << "Reservoir " << i + 1 << ":\n";
            reservoirs[i]->display();
        }
    }
};

int main() {
    ReservoirManager manager;

    Reservoir lake("Lake Baikal", 80.0, 636.0, 1642.0, "Lake");
    Reservoir sea("Black Sea", 1170.0, 580.0, 2210.0, "Sea");

    manager.addReservoir(lake);
    manager.addReservoir(sea);

    manager.displayAll();

    manager.saveToTextFile("reservoirs.txt");

    return 0;
}
