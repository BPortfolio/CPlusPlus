//
//  CarFactory.h
//  FactoryLogger
//
//  Created by Blake Collins on 2/12/20.
//  Copyright © 2020 Blake Collins. All rights reserved.
//

#ifndef CarFactory_h
#define CarFactory_h

#include "Car.h"
#include <cstddef>
#include <memory>

class CarFactory
{
public:
    virtual ~CarFactory() = default;  
    std::unique_ptr<Car> requestCar();
    size_t getNumberOfCarsProduced() const;
    
protected:
    virtual std::unique_ptr<Car> createCar() = 0;
    
private:
    size_t mNumberOfCarsProduced = 0;
};

class FordFactory : public CarFactory
{
protected:
    virtual std::unique_ptr<Car> createCar() override;
};

class ToyotaFactory : public CarFactory
{
protected:
    virtual std::unique_ptr<Car> createCar() override;
};



#endif /* CarFactory_h */
