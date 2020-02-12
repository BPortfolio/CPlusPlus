//
//  CarFactory.cpp
//  FactoryLogger
//
//  Created by Blake Collins on 2/12/20.
//  Copyright © 2020 Blake Collins. All rights reserved.
//

#include <stdio.h>
#include "Logger.h"

#include "CarFactory.h"

// Increment the number of cars produced and return the new car.
std::unique_ptr<Car> CarFactory::requestCar()
{
    ++mNumberOfCarsProduced;
    return createCar();
}

size_t CarFactory::getNumberOfCarsProduced() const
{
    return mNumberOfCarsProduced;
}

std::unique_ptr<Car> FordFactory::createCar()
{
    Logger::instance().log("Ford Created", Logger::LogLevel::Info);
    return std::make_unique<Ford>();
}

std::unique_ptr<Car> ToyotaFactory::createCar()
{
    Logger::instance().log("Toyota Created", Logger::LogLevel::Info);
    return std::make_unique<Toyota>();
}

