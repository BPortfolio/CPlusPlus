//
//  main.cpp
//  FactoryLogger
//
//  Created by Blake Collins on 2/12/20.
//  Copyright © 2020 Blake Collins. All rights reserved.
//

#include "Logger.h"
#include <vector>
#include <string>
#include "CarFactory.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

class LeastBusyFactory : public CarFactory
{
public:
    // Constructs a LeastBusyFactory instance, taking ownership of
    // the given factories.
    explicit LeastBusyFactory(vector<unique_ptr<CarFactory>>&& factories);
    
protected:
    virtual unique_ptr<Car> createCar() override;
    
private:
    vector<unique_ptr<CarFactory>> mFactories;
};

LeastBusyFactory::LeastBusyFactory(vector<unique_ptr<CarFactory>>&& factories)
: mFactories(std::move(factories))
{
    if (mFactories.empty()){
        string mes = "No factories provided.";
        Logger::instance().log(mes, Logger::LogLevel::Error);
        throw runtime_error(mes);
    }
    
}

unique_ptr<Car> LeastBusyFactory::createCar()
{
    CarFactory* bestSoFar = mFactories[0].get();
    
    for (auto& factory : mFactories) {
        if (factory->getNumberOfCarsProduced() <
            bestSoFar->getNumberOfCarsProduced()) {
            bestSoFar = factory.get();
        }
    }
    
    return bestSoFar->requestCar();
}


int main(int argc, const char * argv[]) {
     
    ToyotaFactory myFactory;
    auto myCar = myFactory.requestCar();
    Logger::instance().log("------------------------------------", Logger::LogLevel::Info);
    
    vector<unique_ptr<CarFactory>> factories;
    
    // Create 3 Ford factories and 1 Toyota factory.
    Logger::instance().log("Create 3 Ford factories and 1 Toyota factory. ", Logger::LogLevel::Info);
    
    factories.push_back(make_unique<FordFactory>());
    factories.push_back(make_unique<FordFactory>());
    factories.push_back(make_unique<FordFactory>());
    factories.push_back(make_unique<ToyotaFactory>());
    
  
 
    
    // To get more interesting results, preorder some cars.
    factories[0]->requestCar();
    factories[0]->requestCar();
    factories[1]->requestCar();
    factories[3]->requestCar();
    
     Logger::instance().log("------------------------------------", Logger::LogLevel::Info);
    
    
    // Create a factory that automatically selects the least busy
    // factory from a list of given factories.
    LeastBusyFactory leastBusyFactory(std::move(factories));
    
    Logger::instance().log("Build 10 cars from the least busy factory.", Logger::LogLevel::Info);
    
    // Build 10 cars from the least busy factory.
    for (size_t i = 0; i < 10; i++) {
        auto theCar = leastBusyFactory.requestCar();
    }
    
    Logger::instance().log("------------------------------------", Logger::LogLevel::Info);
    
    return 0;
}
