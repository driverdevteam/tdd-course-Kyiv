/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

/*
 * 1) Americano/little cup test
 * 2) Americano/big cup test
 * 3) cappuccino/little cup test
 * 4) cappuccino/big cup test
 * 5) latte/little cup test
 * 6) latte/big cup test
 * 7) marochino/little cup test
 * 8) marochino/big cup test
 * 9) marochino ingredients order test
 *
 * Arch:
 * 1) CoffeeMachine class
 * 2) enum CoffeeCup
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram, int temperature) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

class MockSourceOfIngridients : public ISourceOfIngredients
{
public:
    MOCK_METHOD1(SetCupSize, void(int));
    MOCK_METHOD2(AddWater, void(int, int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

enum CoffeeCupSize
{
    LittleCup = 100,
    BigCup = 140,
};

enum CoffeeType
{
    Americano,
    Cappuccino,
};

class CoffeeMachine
{
public:
    CoffeeMachine(ISourceOfIngredients *source) : m_source(source)
    {
    }

    void MakeCoffee(CoffeeType type, CoffeeCupSize size)
    {
        switch (type)
        {
        case Americano:
            m_source->SetCupSize(size);
            m_source->AddWater(size / 2, 60);
            m_source->AddCoffee(size / 2);
            break;

        case Cappuccino:
            m_source->SetCupSize(LittleCup);
            m_source->AddMilk(LittleCup / 3);
            m_source->AddCoffee(LittleCup / 3);
            m_source->AddMilkFoam(LittleCup / 3);
            break;

        default:
            break;
        }
    }

private:
    ISourceOfIngredients *m_source;
};

void CheckAmericano(CoffeeCupSize size)
{
    MockSourceOfIngridients mock;
    CoffeeMachine machine(&mock);

    EXPECT_CALL(mock, SetCupSize(size)).Times(1);
    EXPECT_CALL(mock, AddWater(size / 2, 60)).Times(1);
    EXPECT_CALL(mock, AddCoffee(size / 2)).Times(1);

    machine.MakeCoffee(Americano, size);
}

TEST(Coffee, AmericanoLittleCup)
{
    CheckAmericano(LittleCup);
}

TEST(Coffee, AmericanoBigCup)
{
    CheckAmericano(BigCup);
}

TEST(Coffee, CappuccinoLittleCup)
{
    MockSourceOfIngridients mock;
    CoffeeMachine machine(&mock);

    EXPECT_CALL(mock, SetCupSize(LittleCup)).Times(1);
    EXPECT_CALL(mock, AddMilk(LittleCup / 3)).Times(1);
    EXPECT_CALL(mock, AddCoffee(LittleCup / 3)).Times(1);
    EXPECT_CALL(mock, AddMilkFoam(LittleCup / 3)).Times(1);

    machine.MakeCoffee(Cappuccino, LittleCup);
}
