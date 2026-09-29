#include <iostream>
#include <iomanip>
using namespace std;

class EconomicLoadDispatch {
private:
    double P1, P2;
    double loadDemand;

public:
    EconomicLoadDispatch(double demand) {
        loadDemand = demand;
        P1 = 0;
        P2 = 0;
    }

    void calculateDispatch() {
        /*
           Cost functions:

           C1 = 0.02P1^2 + 2P1 + 100
           C2 = 0.04P2^2 + 1.5P2 + 120

           Incremental costs:

           dC1/dP1 = 0.04P1 + 2
           dC2/dP2 = 0.08P2 + 1.5

           For economic dispatch:

           0.04P1 + 2 = 0.08P2 + 1.5

           Also:
           P1 + P2 = Load Demand
        */

        // From the above equations:
        // P2 = (0.04 * P1 + 0.5) / 0.08

        P1 = (loadDemand - 6.25) / 1.5;
        P2 = loadDemand - P1;

        if (P1 < 0)
            P1 = 0;

        if (P2 < 0)
            P2 = 0;
    }

    double costGenerator1() {
        return 0.02 * P1 * P1 + 2 * P1 + 100;
    }

    double costGenerator2() {
        return 0.04 * P2 * P2 + 1.5 * P2 + 120;
    }

    void displayResults() {
        double C1 = costGenerator1();
        double C2 = costGenerator2();
        double totalCost = C1 + C2;

        cout << "\n====================================\n";
        cout << "       ECONOMIC LOAD DISPATCH\n";
        cout << "====================================\n";

        cout << fixed << setprecision(2);

        cout << "Load Demand       : " << loadDemand << " MW\n";
        cout << "Generator 1 Output: " << P1 << " MW\n";
        cout << "Generator 2 Output: " << P2 << " MW\n";

        cout << "\nGeneration Cost:\n";
        cout << "Generator 1 Cost  : " << C1 << " Rs/hour\n";
        cout << "Generator 2 Cost  : " << C2 << " Rs/hour\n";

        cout << "------------------------------------\n";
        cout << "Total Generation  : "
             << P1 + P2 << " MW\n";

        cout << "Total Cost        : "
             << totalCost << " Rs/hour\n";

        cout << "\nEconomic Dispatch Status: SUCCESS\n";
    }
};

int main() {

    double demand;

    cout << "===== Economic Load Dispatch =====\n";

    cout << "Enter total load demand (MW): ";
    cin >> demand;

    if (demand <= 0) {
        cout << "Invalid load demand!\n";
        return 0;
    }

    EconomicLoadDispatch eld(demand);

    eld.calculateDispatch();
    eld.displayResults();

    return 0;
}
