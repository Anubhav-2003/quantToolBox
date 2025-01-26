#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <vector>
#include <string>

class DataHandler {
private:
    std::vector<double> prices;

public:
    void loadData(const std::string& filename);
    const std::vector<double>& getPrices() const;
};

#endif
