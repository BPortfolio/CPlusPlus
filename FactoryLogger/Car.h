//
//  Car.h
//  FactoryLogger
//
//  Created by Blake Collins on 2/12/20.
//  Copyright © 2020 Blake Collins. All rights reserved.
//

#ifndef Car_h
#define Car_h

#pragma once

#include <string_view>

class Car
{
public:
    virtual ~Car() = default;  // Always a virtual destructor!
    virtual std::string_view info() const = 0;
};

class Ford : public Car
{
public:
    virtual std::string_view info() const override { return "Ford"; }
};

class Toyota : public Car
{
public:
    virtual std::string_view info() const override { return "Toyota"; }
};



#endif /* Car_h */
